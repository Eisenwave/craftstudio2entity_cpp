#include <iostream>
#include <ctime>
#include <fstream>
#include <set>
#include <chrono>

#include "math_util.hpp"
#include "bedrock_model.hpp"
#include "craftstudio_model.hpp"
#include "model_io.hpp"

static constexpr Vec2i VISIBLE_BOUNDS{1, 2};
static const Vec3<double> VISIBLE_BOUNDS_OFFSET{0, 0, 0};
static constexpr Vec2i TEXTURE_SIZE{128, 128};

BedrockEntityCube blockToCube(const CraftStudioBlock &block, const CraftStudioBlock *parent) {
    const Vec3<int> &size = block.size;
    Vec3<double> position = block.position + block.offsetFromPivot;

    if (parent != nullptr)
        position = position + parent->position + parent->offsetFromPivot;

    position = {
            position.x - size.x / 2.0,
            position.y - size.y / 2.0,
            -(position.z - size.z / 2.0) - size.z
    };

    return BedrockEntityCube{Vec3<double>(position), size, block.texOffset};
}

/**
 * Converts a {@link CraftStudioBlock} to a {@link BedrockEntityBone} and adds the bone to the given
 * {@link BedrockEntityGeometry}.
 * <p>
 * If the given block has a parent, the parent will be referenced by the block in the geometry.
 * <p>
 * If the given block has children, these children will be appended, referencing the given block as a parent.
 *
 * @param geometry the entity geometry
 * @param block the block to be converted
 * @param parent the parent of the block, can be {@code null}
 */
void blockToBone(BedrockEntityGeometry *geometry,
                 const CraftStudioBlock &block,
                 const CraftStudioBlock *parent) {
    const std::string *parentName = parent == nullptr ? nullptr : &parent->name;

    Vec3<double> pivot = block.position;
    if (parent != nullptr)
        pivot = pivot + parent->position;
    pivot = {
            pivot.x,
            pivot.y,
            -pivot.z
    };

    Vec3<double> rotation = craftStudioRotationToEntityRotation(block.rotation);

    //System.err.println(name);
    BedrockEntityBone bone{&(block.name), parentName, &pivot, &rotation};
    bone.push_cube(blockToCube(block, parent));
    geometry->push_bone(bone);

    for (const CraftStudioBlock &child : block.get_children()) {
        if (isZeroRotation(child.rotation))
            bone.push_cube(blockToCube(child, &block));
        else
            blockToBone(geometry, child, &block);
    }
}


BedrockEntityModel convert(const CraftStudioModel &csModel) {
    BedrockEntityModel result{};
    auto *geometry = new BedrockEntityGeometry{
            VISIBLE_BOUNDS,
            VISIBLE_BOUNDS_OFFSET,
            TEXTURE_SIZE
    };

    for (const CraftStudioBlock &block : csModel.get_blocks())
        blockToBone(geometry, block, nullptr);

    result.insert(csModel.title, geometry);
    return result;
}

int exit_with_err(const std::string &error) {
    std::cerr << error << std::endl;
    exit(1);
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 1;
#pragma clang diagnostic pop
}

bool file_exists(const char *path) {
    if (FILE *file = fopen(path, "r")) {
        fclose(file);
        return true;
    } else return false;
}

long current_time_millis() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

int main(int argc, const char **argv) {
    if (argc < 3)
        exit_with_err(std::string("Usage: ") + argv[0] + " <csjsmodel_path> <entity_path> [flags (r=replace)]");

    /* std::cout << std::endl << "00:" << argv[0] << std::endl << "01:" << argv[1] << std::endl << "02:" << argv[2]
              << std::endl; */
    //exit(0);

    std::string csPath{argv[1]};
    std::string entityPath{argv[2]};

    std::ifstream csFile{csPath};
    std::ofstream entityFile{entityPath};

    std::set<char> flags{};
    if (argc > 2)
        for (char c : std::string{argv[2]})
            flags.insert(c);

    if (!csFile.good())
        exit_with_err(csPath + " must be a file!");
    if (file_exists(entityPath.c_str()) && !flags.count('r'))
        exit_with_err(entityPath + " already exists!");


    long time = current_time_millis();
    {
        CraftStudioModel csModel = read_model(csFile);
        csFile.close();
        std::cerr << "CraftStudio model loaded." << std::endl;

        BedrockEntityModel entityModel = convert(csModel);
        std::cerr << "Model converted to Bedrock entity." << std::endl;

        write_model(entityModel, entityFile);
        entityFile.close();
        std::cerr << "Bedrock entity model written." << std::endl;
    }
    time = current_time_millis() - time;

    std::cerr << "Done! (" << time << " ms)" << std::endl;
    return 0;
}

/*int main() {
    json json = {{"Hello", "World"}};

    Vec3<int> x{0, 1, 2};
//    Vec3<double> y;

    std::cout << "Hello, World!" << json << std::endl << x.to_string() << std::endl;
    return 0;
}*/