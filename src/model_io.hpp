//
// Created by user on 4/14/19.
//

#ifndef CRAFTSTUDIO2ENTITY_CPP_MODEL_IO_HPP
#define CRAFTSTUDIO2ENTITY_CPP_MODEL_IO_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <ios>

#include "nlohmann/json.hpp"
#include "io_util.hpp"
#include "bedrock_model.hpp"
#include "craftstudio_model.hpp"


using nlohmann::json;

#define FORMAT_VERSION "1.8.0"

// IN

template<class T>
Vec3<T> vec3_from_json(const json &json) noexcept(false) {
    if (!json.is_array())
        throw std::ios_base::failure("vec2i must be read from an array");
    if (json.size() != 3)
        throw std::ios_base::failure("vec3 must be 3 elements long");
    return Vec3<T>{json[0], json[1], json[2]};
}

Vec2i vec2i_from_json(const json &json) noexcept(false) {
    if (!json.is_array())
        throw std::ios_base::failure("vec2i must be read from an array");
    if (json.size() != 2)
        throw std::ios_base::failure("vec2i must be 2 elements long");
    return Vec2i{json[0], json[1]};
}

CraftStudioBlock block_from_json(const json &root) {
    const std::string &name = root["name"];
    Vec3<double> position = vec3_from_json<double>(root["position"]);
    Vec3<double> offsetFromPivot = vec3_from_json<double>(root["offsetFromPivot"]);
    Vec3<int> size = vec3_from_json<int>(root["size"]);
    Vec3<double> rotation = vec3_from_json<double>(root["rotation"]);
    Vec2i texOffset = vec2i_from_json(root["texOffset"]);

    json json_children = root["children"];
    CraftStudioBlock block{name, position, offsetFromPivot, size, rotation, texOffset};

    for (const json &json_child : json_children) {
        CraftStudioBlock child = block_from_json(json_child);
        block.push_child(child);
    }

    if (root.contains("vertexCoords"))
        std::cout << "WARNING: Cube \"" + name + "\" has stretch which must be ignored." << std::endl;

    return block;
}

CraftStudioModel model_from_json(const json &root) {
    const std::string &title = root["title"];
    const json &tree = root["tree"];

    CraftStudioModel model{title};
    for (const json& json_block : tree) {
        CraftStudioBlock block = block_from_json(json_block);
        model.push_block(block);
    }

    return model;
}

CraftStudioModel read_model(std::istream &stream) noexcept(false) {
    json root;
    stream >> root;
    return model_from_json(root);
}

// OUT

template<class T>
inline json vec3_to_json(const Vec3<T> &v) {
    return json::array({v.x, v.y, v.z});
}

inline json vec2i_to_json(const Vec2i &v) {
    return json::array({v.x, v.y});
}

inline json cube_to_json(const BedrockEntityCube &cube) {
    return json::object({{"origin", vec3_to_json(cube.origin)},
                         {"size",   vec3_to_json(cube.size)},
                         {"uv",     vec2i_to_json(cube.uv)}});
}

json bone_to_json(const BedrockEntityBone &bone) {
    json root = json::object();
    root["name"] = *bone.name;

    if (bone.has_parent())
        root["parent"] = *bone.parent;

    if (bone.has_pivot()) {
        root["pivot"] = vec3_to_json(*bone.pivot);
    }
    if (bone.has_rotation()) {
        if (!bone.has_pivot())
            std::cerr << ("WARNING: Bone \"" + *bone.name + "\" has a rotation but no pivot");
        root["rotation"] = vec3_to_json(*bone.rotation);
    }

    json jsonCubes = json::array();

    for (const BedrockEntityCube &cube : bone.get_cubes())
        jsonCubes.push_back(cube_to_json(cube));
    root["cubes"] = jsonCubes;

    return root;
}

json geometry_to_json(const BedrockEntityGeometry &geometry) {
    json root = json::object();

    const Vec2i &visible_bounds = geometry.visible_bounds;
    root["visible_bounds_width"] = visible_bounds.x;
    root["visible_bounds_height"] = visible_bounds.y;

    root["visible_bounds_offset"] = vec3_to_json(geometry.visible_bounds_offset);

    const Vec2i &texture_size = geometry.texture_size;
    root["texturewidth"] = texture_size.x;
    root["textureheight"] = texture_size.y;

    json json_bones = json::array();
    for (const BedrockEntityBone &bone : geometry.get_bones())
        json_bones.push_back(bone_to_json(bone));
    root["bones"] = json_bones;

    return root;
}

json model_to_json(const BedrockEntityModel &model) {
    json root = json::object();
    root["format_version"] = FORMAT_VERSION;

    for (const auto &entry : model.get_geometries()) {
        root[entry.first] = geometry_to_json(*entry.second);
    }

    return root;
}

void write_model(const BedrockEntityModel &model, std::ostream &stream) {
    json json = model_to_json(model);

    stream << std::setw(4) << json;
}

#endif //CRAFTSTUDIO2ENTITY_CPP_MODEL_IO_HPP
