#pragma once

#include "BoxelCamera.hpp"
#include "BoxelPlayer.hpp"

#include "../Scene.hpp"
#include "../World.hpp"

class BoxelMap
{
public:
  typedef std::size_t BlockId;
  
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
  
  struct BlockType{
    std::string name;
    bool visible;
    bool withAlpha;
  };
  
  BoxelMap();
  ~BoxelMap();

  void generate();

  BlockId getBlock(std::size_t x, std::size_t y, std::size_t z) const;
  const BlockType& getBlockType(BlockId id) const;

private:
  static const BlockType mBlockType[mNbBlock];

  unsigned int mBlock[mSizeZ][mSizeY][mSizeX];
  
};

class BoxelScene : public Scene {
public:
  
  BoxelScene();
  ~BoxelScene();

  void addAction(Window &win) override;
  void update(float frameTime) override;

private:
  World mWorld;
  BoxelMap mBoxelMap;
  Renderer::Material_handle mBlockMaterial[BoxelMap::mNbBlock];
  Renderer::Object mBlockObject;
  
  BoxelCamera mCamera;
  BoxelPlayer mPlayer;
  //BoxelChunk<50, 50, 50> chunk;
};
