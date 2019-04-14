#include <utility>

#include <utility>

//
// Created by user on 4/13/19.
//

#ifndef CRAFTSTUDIO2ENTITY_CPP_CRAFTSTUDIO_MODEL_HPP
#define CRAFTSTUDIO2ENTITY_CPP_CRAFTSTUDIO_MODEL_HPP

#include <vector>
#include <string>

#include "math_util.hpp"

class CraftStudioModel;

class CraftStudioBlock;

class CraftStudioModel {

private:
    std::vector<CraftStudioBlock> blocks{};

public:
    const std::string title;

    explicit CraftStudioModel(std::string title) : title{std::move(title)} {}

    void push_block(const CraftStudioBlock &block) {
        blocks.push_back(block);
    }

    const std::vector<CraftStudioBlock> &get_blocks() const {
        return blocks;
    }

    int size() {
        return blocks.size();
    }

};

class CraftStudioBlock {

private:
    std::vector<CraftStudioBlock> children{};

public:
    const std::string name;
    const Vec3<double> position;
    const Vec3<double> offsetFromPivot;
    const Vec3<int> size;
    const Vec3<double> rotation;
    const Vec2i texOffset;

    CraftStudioBlock(std::string name,
                     const Vec3<double> &position,
                     const Vec3<double> &offsetFromPivot,
                     const Vec3<int> &size,
                     const Vec3<double> &rotation,
                     const Vec2i &texOffset) : name{std::move(name)},
                                               position{position},
                                               offsetFromPivot{offsetFromPivot},
                                               size{size},
                                               rotation{rotation},
                                               texOffset{texOffset} {
    }

    void push_child(const CraftStudioBlock &block) {
        children.push_back(block);
    }


    const std::vector<CraftStudioBlock> &get_children() const {
        return children;
    }

};

#endif //CRAFTSTUDIO2ENTITY_CPP_CRAFTSTUDIO_MODEL_HPP
