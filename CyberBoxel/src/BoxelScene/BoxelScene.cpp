#include "BoxelScene/BoxelScene.hpp"

#include "stb_perlin.h"

#include <Core/Debug.h>

#include <vector>

void BoxelMap::generate() {
    //gen height
    std::array<std::array<float, mSizeZ>, mSizeX> height = {0};

    for (size_t x(0); x < mSizeX; ++x) {
        for (size_t z(0); z < mSizeZ; ++z) {
            constexpr float lacunarity = 2.f;
            constexpr int octaves = 6;
            constexpr float gain = 0.5;
            constexpr int wrap_x = 256;
            constexpr int wrap_y = 256;
            constexpr int wrap_z = 256;
            constexpr float freq = 1.f / 128.f;
            constexpr float size = 15.f;
            height.at(x).at(z) = stb_perlin_fbm_noise3(static_cast<float>(x) * freq, static_cast<float>(z) * freq, 0,
                                                 lacunarity,
                                                 gain,
                                                 octaves,
                                                 wrap_x, wrap_y, wrap_z) * size + size;
        }
    }

    //basic Generator
    for (unsigned int z(0); z < mSizeZ; ++z) {
        for (unsigned int y(0); y < mSizeY; ++y) {
            for (unsigned int x(0); x < mSizeX; ++x) {
                auto y2 = static_cast<float>(y);
                float h = height.at(x).at(z);
                auto& block = mBlock.at(z).at(y).at(x);

                block = mNothingId;

                if (y2 < h - 4) {
                    block = mStoneId;
                } else if (y2 < h - 1) {
                    block = mDirtId;
                } else {
                    if (h < static_cast<float>(mSizeY) / 3) {
                        if (y2 < h) {
                            block = mSandId;
                        } else if (y2 < static_cast<float>(mSizeY) / 3) {
                            block = mWaterId;
                        }
                    } else {
                        if (y2 < h) {
                            block = mGrassId;
                        } else if (y2 < static_cast<float>(mSizeY) / 3) {
                            block = mWaterId;
                        }
                    }
                }
            }
        }
    }
}

BoxelMap::BlockId BoxelMap::getBlock(std::size_t x, std::size_t y, std::size_t z) const {
    return mBlock.at(z).at(y).at(x);
}

const BoxelMap::BlockType &BoxelMap::getBlockType(BlockId id) {
    return mBlockType.at(id);
}

struct BoxelMesh {
    std::vector<float> vertices;
    std::vector<float> texCoord;
    std::vector<float> normals;
    std::vector<uint> faces;
    BoxelMap &boxelMap;

    explicit BoxelMesh(BoxelMap &m) : boxelMap(m) {}

    void addVertex(float posX,
                   float posY,
                   float posZ,
                   float texU,
                   float texV,
                   float normX,
                   float normY,
                   float normZ) {
        vertices.push_back(posX);
        vertices.push_back(posY);
        vertices.push_back(posZ);

        texCoord.push_back(texU);
        texCoord.push_back(texV);

        normals.push_back(normX);
        normals.push_back(normY);
        normals.push_back(normZ);
    }

    void addQuad(float posX1,
                 float posY1,
                 float posZ1,
                 float texU1,
                 float texV1,
                 float posX2,
                 float posY2,
                 float posZ2,
                 float texU2,
                 float texV2,
                 float posX3,
                 float posY3,
                 float posZ3,
                 float texU3,
                 float texV3,
                 float posX4,
                 float posY4,
                 float posZ4,
                 float texU4,
                 float texV4,
                 float normX,
                 float normY,
                 float normZ) {
        addVertex(posX1, posY1, posZ1, texU1, texV1, normX, normY, normZ);
        addVertex(posX2, posY2, posZ2, texU2, texV2, normX, normY, normZ);
        addVertex(posX3, posY3, posZ3, texU3, texV3, normX, normY, normZ);
        addVertex(posX4, posY4, posZ4, texU4, texV4, normX, normY, normZ);
        std::size_t size = vertices.size() / 3;

        faces.push_back(static_cast<uint>(size - 4));
        faces.push_back(static_cast<uint>(size - 3));
        faces.push_back(static_cast<uint>(size - 2));

        faces.push_back(static_cast<uint>(size - 4));
        faces.push_back(static_cast<uint>(size - 2));
        faces.push_back(static_cast<uint>(size - 1));
    }


    void generateCube(unsigned int x,
                      unsigned int y,
                      unsigned int z) {
        auto fx = static_cast<float>(x);
        auto fy = static_cast<float>(y);
        auto fz = static_cast<float>(z);

        if (boxelMap.getBlock(x, y, z) == BoxelMap::mWaterId) {
            //up
            if (y + 1 == BoxelMap::mSizeY ||
                boxelMap.getBlock(x, y + 1, z) == BoxelMap::mNothingId) {
                constexpr float a = 0.9f;
                addQuad(fx, fy + a, fz, 0, 0,
                        fx + 1.f, fy + a, fz, 1, 0,
                        fx + 1.f, fy + a, fz + 1.f, 1, 1,
                        fx, fy + a, fz + 1.f, 0, 1,
                        0, 1, 0);
            }
            return;
        }

        //up
        /*if(y+1==sizeY || boxels[z][y][x]==mNothingId){

              }*/

        //up
        if (y + 1 == BoxelMap::mSizeY ||
            boxelMap.getBlock(x, y + 1, z) == BoxelMap::mNothingId ||
            boxelMap.getBlock(x, y + 1, z) == BoxelMap::mWaterId) {
            addQuad(fx, fy + 1.f, fz, 0, 0,
                    fx + 1.f, fy + 1.f, fz, 1, 0,
                    fx + 1.f, fy + 1.f, fz + 1.f, 1, 1,
                    fx, fy + 1.f, fz + 1.f, 0, 1,
                    0, 1, 0);
        }

        //down
        if (y == 0 ||
            boxelMap.getBlock(x, y - 1, z) == BoxelMap::mNothingId ||
            boxelMap.getBlock(x, y - 1, z) == BoxelMap::mWaterId) {
            addQuad(fx, fy, fz, 0, 0,
                    fx + 1.f, fy, fz, 1, 0,
                    fx + 1.f, fy, fz + 1.f, 1, 1,
                    fx, fy, fz + 1.f, 0, 1,
                    0, -1, 0);
        }

        //left
        if (x + 1 == BoxelMap::mSizeX ||
            boxelMap.getBlock(x + 1, y, z) == BoxelMap::mNothingId ||
            boxelMap.getBlock(x + 1, y, z) == BoxelMap::mWaterId) {
            addQuad(fx + 1.f, fy, fz, 0, 0,
                    fx + 1.f, fy + 1.f, fz, 1, 0,
                    fx + 1.f, fy + 1.f, fz + 1.f, 1, 1,
                    fx + 1.f, fy, fz + 1.f, 0, 1,
                    1, 0, 0);
        }

        //right
        if (x == 0 ||
            boxelMap.getBlock(x - 1, y, z) == BoxelMap::mNothingId ||
            boxelMap.getBlock(x - 1, y, z) == BoxelMap::mWaterId) {
            addQuad(fx, fy, fz, 0, 0,
                    fx, fy + 1.f, fz, 1, 0,
                    fx, fy + 1.f, fz + 1.f, 1, 1,
                    fx, fy, fz + 1.f, 0, 1,
                    -1, 0, 0);
        }

        //front
        if (z + 1 == BoxelMap::mSizeZ ||
            boxelMap.getBlock(x, y, z + 1) == BoxelMap::mNothingId ||
            boxelMap.getBlock(x, y, z + 1) == BoxelMap::mWaterId) {
            addQuad(fx, fy, fz + 1.f, 0, 0,
                    fx + 1.f, fy, fz + 1.f, 1, 0,
                    fx + 1.f, fy + 1.f, fz + 1.f, 1, 1,
                    fx, fy + 1.f, fz + 1.f, 0, 1,
                    0, 0, 1);
        }

        //back
        if (z == 0 ||
            boxelMap.getBlock(x, y, z - 1) == BoxelMap::mNothingId ||
            boxelMap.getBlock(x, y, z - 1) == BoxelMap::mWaterId) {
            addQuad(fx, fy, fz, 0, 0,
                    fx + 1.f, fy, fz, 1, 0,
                    fx + 1.f, fy + 1.f, fz, 1, 1,
                    fx, fy + 1.f, fz, 0, 1,
                    0, 0, -1);
        }
    }

    void generate(BoxelMap::BlockId type) {
        for (unsigned int y(0); y < BoxelMap::mSizeY; ++y) {
            for (unsigned int z(0); z < BoxelMap::mSizeZ; ++z) {
                for (unsigned int x(0); x < BoxelMap::mSizeX; ++x) {
                    if (boxelMap.getBlock(x, y, z) == type) {
                        generateCube(x, y, z);
                    }

                }
            }
        }
    }

};

BoxelScene::BoxelScene() :
        mBlockObject("BoxelObject") {
    mBoxelMap.generate();

    //Meshing
    mBlockObject.model = Renderer::createModel("BoxelModel");

    constexpr float mapOrigin = 0.5f;

    mBlockObject.matrix.addTranslation(-static_cast<float>(BoxelMap::mSizeX) * mapOrigin,
                                       -static_cast<float>(BoxelMap::mSizeY) * mapOrigin,
                                       -static_cast<float>(BoxelMap::mSizeZ) * mapOrigin);

    for (std::size_t i(0); i < BoxelMap::mNbBlock; ++i) {
        const BoxelMap::BlockType &type = mBoxelMap.getBlockType(i);
        if (type.visible) {
            std::string filename = std::string(type.name) + ".dds";
            cc::TextureHandle tex = Renderer::getHandleFromFile(filename);
            Renderer::loadTexture(tex);
            mBlockMaterial.at(i) = Renderer::createMaterial(tex, std::string(type.name) + "Material");

            if (type.withAlpha) {
                Renderer::setWithAlpha(mBlockMaterial.at(i), true);
            }

            BoxelMesh mesh(mBoxelMap);
            mesh.generate(i);

            if (!mesh.vertices.empty()) {
                Renderer::addSubMesh(mBlockObject.model,
                                     static_cast<uint>(mesh.vertices.size() / 3),
                                     &mesh.vertices[0],
                                     &mesh.texCoord[0],
                                     &mesh.normals[0],
                                     static_cast<uint>(mesh.faces.size() / 3),
                                     &mesh.faces[0],
                                     mBlockMaterial.at(i));
            }
        }
    }

    //chunk.loadTexture();
    //chunk.mGrid.generateGrid();
    //chunk.generateMesh();
    cc::log("BoxelScene", "construct end");
}

BoxelScene::~BoxelScene() {
    cc::log("BoxelScene", "destruct");
}

void BoxelScene::addAction(cs::Window &win) {
    mCamera.addAction(win);
    mPlayer.addAction(win);
}

void BoxelScene::update(float frameTime) {
    mCamera.update(frameTime);
}
