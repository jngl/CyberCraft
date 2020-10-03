#include "World.hpp"

#include <Core/Debug.h>

/**************************************************************************
 * WorldMeshGenerator
 *************************************************************************/

/**************************************************************************
 * BlockShape
 *************************************************************************/

/**************************************************************************
 * Block
 *************************************************************************/

/**************************************************************************
 * WorldGenerator
 *************************************************************************/

WorldGenerator::WorldGenerator(World* world):
  mWorld(world)
{
}

WorldGenerator::~WorldGenerator(){
}
	   
World* WorldGenerator::getWorld(){
  return mWorld;
}

class DefaultWorldGenerator : public WorldGenerator
{
public:
  DefaultWorldGenerator(World* world):
    WorldGenerator(world)
  {
    ccCore::log("World", "construct default generator");
  }

  ~DefaultWorldGenerator(){
      ccCore::log("World", "destruct default generator");
  }

  void generate(WorldChunk* chunk) override
  {
      ccCore::log("World", "generate chunk with default (todo)");
  }

private:
  
};

/**************************************************************************
 * WorldChunk
 *************************************************************************/

WorldChunk::WorldChunk(ccCore::Vector3i pos, ccCore::Vector3i size):
  mPos(pos),
  mSize(size)
{
    ccCore::log("World", "load chunck (", pos.x, ", ", pos.y, ", ", pos.z, ")");
}

WorldChunk::~WorldChunk(){
    ccCore::log("World", "unload chunck (", mPos.x, ", ", mPos.y, ", ", mPos.z, ")");
}

Block* WorldChunk::at(ccCore::Vector3i pos){
    ccCore::log("World", "Warning WorldChunk::at(pos) todo");
    return nullptr;
}

void WorldChunk::set(ccCore::Vector3i pos, Block* block){
    ccCore::log("World", "Warning WorldChunk::set(pos, block) todo");
}

void WorldChunk::updateMesh(){
    ccCore::log("World", "Warning WorldChunk::updateMesh() todo");
}

ccCore::Vector3i WorldChunk::getPos(){
    return mPos;
}

/**************************************************************************
 * World
 *************************************************************************/

World::World(ccCore::Vector3i nbChunk, ccCore::Vector3i chunkSize):
  mGenerator(new DefaultWorldGenerator(this)),
  mNbChunk(nbChunk),
  mChunkSize(chunkSize)
{
  loadChunk(ccCore::Vector3i{0,0,0});

    ccCore::log("World", "Construct");
}

World::~World(){
  for(WorldChunk* c : mChunks){
    delete c;
  }
  delete mGenerator;
    ccCore::log("World", "destruct");
}
  
Block* World::at(ccCore::Vector3i pos){
    ccCore::log("World", "Warning World::at(pos) work in progesss");
  //math::Vector3i chunkPos;
    ccCore::Vector3i blockPos = pos;
  return mChunks[0]->at(blockPos);
}
void World::set(ccCore::Vector3i pos, Block* block){
    ccCore::log("World", "Warning World::set(pos, block) work in progesss");
  mChunks[0]->set(pos, block);
  mChunks[0]->updateMesh();
}

void World::loadChunk(ccCore::Vector3i pos){
  mChunks.push_back(new WorldChunk(pos, mChunkSize));
  mGenerator->generate(mChunks[0]);
  mChunks[0]->updateMesh();
}

void World::unloadChunk(ccCore::Vector3i pos){
    ccCore::log("World", "Warning World::unloadChunk(pos) not tested");
  for(int i(0); i<mChunks.size(); ++i){
    if(mChunks[i]->getPos()==pos){
      delete mChunks[i];
      mChunks.erase(mChunks.begin()+i);
      return;
    }
  }
}

ccCore::Vector3i World::getNbChunk(){
  return mNbChunk;
}

ccCore::Vector3i World::getChunkSize(){
  return mChunkSize;
}
