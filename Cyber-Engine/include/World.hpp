#pragma once


#include <Core/Math.h>

#include <string>
#include <vector>

class WorldChunk;

class World;

class WorldMeshGenerator {
public:
    void addQuad(ccCore::Vector3f p1, ccCore::Vector3f p2, ccCore::Vector3f p3, ccCore::Vector3f p4);
};

class BlockShape {
public:
    virtual std::string getName();

    virtual void generateMesh(WorldMeshGenerator &gen, ccCore::Vector3i pos) = 0;
};

class Block {
public:
    virtual std::string getName() = 0;

    virtual bool hasTag(std::string tagName) = 0;

    virtual BlockShape &getShape() = 0;
};

class WorldGenerator {
public:
    explicit WorldGenerator(World *world);

    virtual ~WorldGenerator();

    virtual void generate(WorldChunk *chunk) = 0;

    World *getWorld();

private:
    World *mWorld;
};

class WorldChunk {
public:
    WorldChunk(ccCore::Vector3i pos, ccCore::Vector3i size);
    ~WorldChunk();

    Block *at(ccCore::Vector3i pos);

    void set(ccCore::Vector3i pos, Block *block);

    void updateMesh();

    ccCore::Vector3i getPos();

private:
    ccCore::Vector3i mPos;
    ccCore::Vector3i mSize;
};

class World {
public:
    World(ccCore::Vector3i nbChunk, ccCore::Vector3i chunkSize);

    ~World();

    Block *at(ccCore::Vector3i pos);

    void set(ccCore::Vector3i pos, Block *block);

    void loadChunk(ccCore::Vector3i pos);
    void unloadChunk(ccCore::Vector3i pos);

    ccCore::Vector3i getNbChunk();
    ccCore::Vector3i getChunkSize();

private:
    std::vector<WorldChunk *> mChunks;
    WorldGenerator *mGenerator;
    ccCore::Vector3i mNbChunk;
    ccCore::Vector3i mChunkSize;
};
