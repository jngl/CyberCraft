#include "World.hpp"

#include "debugAssert.hpp"

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
    debug::log("World", "construct default generator");
  }

  ~DefaultWorldGenerator(){
    debug::log("World", "destruct default generator");
  }

  void generate(WorldChunk* chunk) override
  {
    debug::log("World", "generate chunk with default (todo)");
  }

private:
  
};

/**************************************************************************
 * WorldChunk
 *************************************************************************/

WorldChunk::WorldChunk(math::Vector3i pos, math::Vector3i size):
  mPos(pos),
  mSize(size)
{
  debug::log("World", "load chunck (", pos.x, ", ", pos.y, ", ", pos.z, ")"); 
}

WorldChunk::~WorldChunk(){
  debug::log("World", "unload chunck (", mPos.x, ", ", mPos.y, ", ", mPos.z, ")"); 
}

Block* WorldChunk::at(math::Vector3i pos){
  debug::log("World", "Warning WorldChunk::at(pos) todo");
  return nullptr;
}

void WorldChunk::set(math::Vector3i pos, Block* block){
  debug::log("World", "Warning WorldChunk::set(pos, block) todo");
}

void WorldChunk::updateMesh(){
  debug::log("World", "Warning WorldChunk::updateMesh() todo");
}

math::Vector3i WorldChunk::getPos(){
  return mPos;
}

/**************************************************************************
 * World
 *************************************************************************/

World::World(math::Vector3i nbChunk, math::Vector3i chunkSize):
  mGenerator(new DefaultWorldGenerator(this)),
  mNbChunk(nbChunk),
  mChunkSize(chunkSize)
{
  loadChunk(math::Vector3i(0,0,0));
  
  debug::log("World", "Construct");
}

World::~World(){
  for(WorldChunk* c : mChunks){
    delete c;
  }
  delete mGenerator;
  debug::log("World", "destruct");
}
  
Block* World::at(math::Vector3i pos){
  debug::log("World", "Warning World::at(pos) work in progesss");
  //math::Vector3i chunkPos;
  math::Vector3i blockPos = pos;
  return mChunks[0]->at(blockPos);
}
void World::set(math::Vector3i pos, Block* block){
  debug::log("World", "Warning World::set(pos, block) work in progesss");
  mChunks[0]->set(pos, block);
  mChunks[0]->updateMesh();
}

void World::loadChunk(math::Vector3i pos){
  mChunks.push_back(new WorldChunk(pos, mChunkSize));
  mGenerator->generate(mChunks[0]);
  mChunks[0]->updateMesh();
}

void World::unloadChunk(math::Vector3i pos){
  debug::log("World", "Warning World::unloadChunk(pos) not tested");
  for(int i(0); i<mChunks.size(); ++i){
    if(mChunks[i]->getPos()==pos){
      delete mChunks[i];
      mChunks.erase(mChunks.begin()+i);
      return;
    }
  }
}

math::Vector3i World::getNbChunk(){
  return mNbChunk;
}

math::Vector3i World::getChunkSize(){
  return mChunkSize;
}
