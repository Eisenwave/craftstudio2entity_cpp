//
// Created by user on 4/13/19.
//

#ifndef CRAFTSTUDIO2ENTITY_CPP_BEDROCK_MODEL_HPP
#define CRAFTSTUDIO2ENTITY_CPP_BEDROCK_MODEL_HPP

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <optional>
#include "math_util.hpp"

class BedrockEntityModel;

class BedrockEntityGeometry;

class BedrockEntityBone;

class BedrockEntityCube;

struct BedrockEntityCube {
    Vec3<double> origin;
    Vec3<int> size;
    Vec2i uv;
};

class BedrockEntityBone {

private:
    std::vector<BedrockEntityCube> cubes{2};

public:
    const std::string *name;
    const std::string *parent;
    const Vec3<double> *pivot;
    const Vec3<double> *rotation;

    BedrockEntityBone(const std::string *name,
                      const std::string *parent,
                      Vec3<double> *pivot,
                      Vec3<double> *rotation) : name{name}, parent{parent}, pivot{pivot}, rotation{rotation} {}

    bool has_parent() const {
        return parent != nullptr;
    }

    bool has_pivot() const {
        return pivot != nullptr;
    }

    bool has_rotation() const {
        return rotation != nullptr;
    }

    void push_cube(const BedrockEntityCube &cube) {
        cubes.push_back(cube);
    }

    const std::vector<BedrockEntityCube> &get_cubes() const {
        return cubes;
    }

    int size() const {
        return cubes.size();
    }

};

class BedrockEntityGeometry {

private:
    std::vector<BedrockEntityBone> bones{};

public:
    const Vec2i visible_bounds;
    const Vec3<double> visible_bounds_offset;
    const Vec2i texture_size;

    BedrockEntityGeometry(const Vec2i &visible_bounds,
                          const Vec3<double> &visibleBoundsOffset,
                          const Vec2i &textureSize) : visible_bounds{visible_bounds},
                                                      visible_bounds_offset{visibleBoundsOffset},
                                                      texture_size{textureSize} {}

    const std::vector<BedrockEntityBone> &get_bones() const {
        return bones;
    }

    void push_bone(BedrockEntityBone &bone) {
        bones.push_back(bone);
    }

    int size() const {
        return bones.size();
    }

};

class BedrockEntityModel {

private:
    std::map<std::string, BedrockEntityGeometry *> geometries;

public:
    BedrockEntityGeometry *get_geometry(const std::string &name) {
        return geometries[name];
    }

    const std::map<std::string, BedrockEntityGeometry *> get_geometries() const {
        return geometries;
    }

    void insert(const std::string &name, BedrockEntityGeometry *geometry) {
        geometries.insert({name, geometry});
    }

    void clear() {
        geometries.clear();
    }

};

#endif //CRAFTSTUDIO2ENTITY_CPP_BEDROCK_MODEL_HPP
