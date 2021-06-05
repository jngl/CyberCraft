#pragma once

#include "BoxelCamera.hpp"
#include "BoxelPlayer.hpp"

#include "../Scene.hpp"

class BoxelMap {
public:
    using BlockId = std::size_t;

    static constexpr std::size_t mNbBlock = 7;
    static constexpr std::size_t mSizeX = 200;
    static constexpr std::size_t mSizeY = 30;
    static constexpr std::size_t mSizeZ = 200;

    static constexpr BlockId mGrassId = 0;
    static constexpr BlockId mStoneId = 1;
    static constexpr BlockId mDirtId = 2;
    static constexpr BlockId mNothingId = 3;
    static constexpr BlockId mWaterId = 4;
    static constexpr BlockId mSandId = 5;
    static constexpr BlockId mWoodId = 6;

    struct BlockType {
        std::string_view name;
        bool visible;
        bool withAlpha;
    };

    BoxelMap();

    BoxelMap(const BoxelMap&) = delete;
    BoxelMap(BoxelMap&&) = delete;
    BoxelMap& operator=(const BoxelMap&) = delete;
    BoxelMap& operator=(BoxelMap&&) = delete;

    ~BoxelMap() = default;

    void generate();

    [[nodiscard]] BlockId getBlock(std::size_t x, std::size_t y, std::size_t z) const;

    [[nodiscard]] static const BlockType &getBlockType(BlockId id) ;

private:
    static constexpr std::array<BlockType, mNbBlock> mBlockType = {
            BlockType{"grass",   true,  false},
            BlockType{"stone",   true,  false},
            BlockType{"dirt",    true,  false},
            BlockType{"nothing", false, false},
            BlockType{"water",   true,  true},
            BlockType{"sand",    true,  false},
            BlockType{"wood",    true,  false}
    };

    std::array<std::array<std::array<unsigned int, mSizeX>,mSizeY>,mSizeZ> mBlock;
};

class BoxelScene : public Scene {
public:

    BoxelScene();

    BoxelScene(const BoxelScene&) = delete;
    BoxelScene(BoxelScene&&) = delete;
    BoxelScene& operator=(const BoxelScene&) = delete;
    BoxelScene& operator=(BoxelScene&&) = delete;

    ~BoxelScene() override;

    void addAction(cs::Window &win) override;

    void update(float frameTime) override;

private:
    BoxelMap mBoxelMap;
    std::array<Renderer::Material_handle, BoxelMap::mNbBlock> mBlockMaterial =  {0};
    Renderer::Object mBlockObject;

    BoxelCamera mCamera;
    BoxelPlayer mPlayer;
};
