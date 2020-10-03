#pragma once

#include "Math.hpp"

#include <string>
#include <vector>

class WorldChunk;
class World;

class WorldMeshGenerator
{
public:
  void addQuad(math::Vector3f p1, math::Vector3f p2, math::Vector3f p3, math::Vector3f p4);
};

class BlockShape
{
public:
  virtual std::string getName();
  virtual void generateMesh(WorldMeshGenerator& gen, math::Vector3i pos) = 0;
};

class Block
{
public:
  virtual std::string getName() = 0;
  virtual bool hasTag(std::string tagName) = 0;
  virtual BlockShape& getShape() = 0;
};

class WorldGenerator
{
public:
  WorldGenerator(World* world);
  virtual ~WorldGenerator();
  virtual void generate(WorldChunk* chunk) = 0;

  World* getWorld();

private:
  World* mWorld;
};

class WorldChunk
{
public:
  WorldChunk(math::Vector3i pos, math::Vector3i size);
  ~WorldChunk();
  Block* at(math::Vector3i pos);
  void set(math::Vector3i pos, Block* block);
  void updateMesh();

  math::Vector3i getPos();

private:
  math::Vector3i mPos;
  math::Vector3i mSize;
};

class World
{
public:
  World(math::Vector3i nbChunk, math::Vector3i chunkSize);
  ~World();
  
  Block* at(math::Vector3i pos);
  void set(math::Vector3i pos, Block* block);

  void loadChunk(math::Vector3i pos);
  void unloadChunk(math::Vector3i pos);

  math::Vector3i getNbChunk();
  math::Vector3i getChunkSize();

private:
  std::vector<WorldChunk*> mChunks;
  WorldGenerator* mGenerator;
  math::Vector3i mNbChunk;
  math::Vector3i mChunkSize;
};
