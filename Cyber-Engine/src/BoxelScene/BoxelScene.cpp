#include "BoxelScene/BoxelScene.hpp"

#include "stb_perlin.h"

#include "debugAssert.hpp"

#include <vector>

const BoxelMap::BlockType BoxelMap::mBlockType[BoxelMap::mNbBlock] =
  { {"grass", true, false},
    {"stone", true, false},
    {"dirt", true, false},
    {"nothing", false, false},
    {"water", true, true},
    {"sand", true, false},
    {"wood", true, false}
  };
 
BoxelMap::BoxelMap(){
}

BoxelMap::~BoxelMap(){
}

void BoxelMap::generate(){
  //gen height
  float height[mSizeX][mSizeZ];

  for(int x(0); x<mSizeX; ++x){
    for(int z(0); z<mSizeZ; ++z){
      float lacunarity = 2.f;
      int octaves = 6;
      float gain = 0.5;
      int wrap_x = 256;
      int wrap_y = 256;
      int wrap_z = 256;
      float freq = 1.f/128.f;
      height[x][z] = stb_perlin_fbm_noise3(x*freq, z*freq, 0,
					   lacunarity,
					   gain,
					   octaves,
				       wrap_x, wrap_y, wrap_z)*15.f+15.f;
    }
  }
  
  //basic Generator
  for(unsigned int z(0); z<mSizeZ; ++z){
    for(unsigned int y(0); y<mSizeY; ++y){
      for(unsigned int x(0); x<mSizeX; ++x){
	float y2 = static_cast<float>(y);
	float h = height[x][z];

	mBlock[z][y][x] = mNothingId;
	
	if(y2<h-4){
	  mBlock[z][y][x] = mStoneId;
	}else if(y2<h-1){
	  mBlock[z][y][x] = mDirtId;
	}else{
	  if(h<mSizeY/3){
	    if(y2<h){
	      mBlock[z][y][x] = mSandId;
	    }else if(y2<mSizeY/3){
	      mBlock[z][y][x] = mWaterId;
	    }
	  }else{
	    if(y2<h){
	      mBlock[z][y][x] = mGrassId;
	    }else if(y2<mSizeY/3){
	      mBlock[z][y][x] = mWaterId;
	  }
	  }
	  
	}
      }
    }
  }
}

BoxelMap::BlockId BoxelMap::getBlock(std::size_t x, std::size_t y, std::size_t z) const{
  return mBlock[z][y][x];
}

const BoxelMap::BlockType& BoxelMap::getBlockType(BlockId id) const{
  return mBlockType[id];
}

struct BoxelMesh{
  std::vector<float> vertices;
  std::vector<float> texCoord;
  std::vector<float> normals;
  std::vector<unsigned int> faces;
  BoxelMap& boxelMap;

  BoxelMesh(BoxelMap& m) :boxelMap(m) { }

  void addVertex(float posX,
		 float posY,
		 float posZ,
		 float texU,
		 float texV,
		 float normX,
		 float normY,
		 float normZ)
  {
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
	       float normZ)
  {
    addVertex(posX1, posY1, posZ1, texU1, texV1, normX, normY,  normZ);
    addVertex(posX2, posY2, posZ2, texU2, texV2, normX, normY,  normZ);
    addVertex(posX3, posY3, posZ3, texU3, texV3, normX, normY,  normZ);
    addVertex(posX4, posY4, posZ4, texU4, texV4, normX, normY,  normZ);
    std::size_t size = vertices.size()/3;

    faces.push_back(size-4);
    faces.push_back(size-3);
    faces.push_back(size-2);
        
    faces.push_back(size-4);
    faces.push_back(size-2);
    faces.push_back(size-1);
  }

  
  void generateCube(unsigned int x,
		    unsigned int y,
		    unsigned int z)
  {
    float fx = static_cast<float>(x);
    float fy = static_cast<float>(y);
    float fz = static_cast<float>(z);

    if(boxelMap.getBlock(x,y,z)==BoxelMap::mWaterId){
      //up
      if( y+1==BoxelMap::mSizeY ||
	  boxelMap.getBlock(x,y+1,z)==BoxelMap::mNothingId ){
	addQuad(fx,     fy+0.9f, fz,     0, 0,
		fx+1.f, fy+0.9f, fz,     1, 0,
		fx+1.f, fy+0.9f, fz+1.f, 1, 1,
		fx,     fy+0.9f, fz+1.f, 0, 1,
		0, 1, 0);
    } 
      return;
    }

    //up
    /*if(y+1==sizeY || boxels[z][y][x]==mNothingId){
      
	      }*/

    //up
    if( y+1==BoxelMap::mSizeY ||
	boxelMap.getBlock(x,y+1,z)==BoxelMap::mNothingId ||
	boxelMap.getBlock(x,y+1,z)==BoxelMap::mWaterId ){
      addQuad(fx,     fy+1.f, fz,     0, 0,
	      fx+1.f, fy+1.f, fz,     1, 0,
	      fx+1.f, fy+1.f, fz+1.f, 1, 1,
	      fx,     fy+1.f, fz+1.f, 0, 1,
	      0, 1, 0);
    }
    
    //down
    if( y==0 ||
	boxelMap.getBlock(x,y-1,z)==BoxelMap::mNothingId ||
	boxelMap.getBlock(x,y-1,z)==BoxelMap::mWaterId){
      addQuad(fx,     fy, fz,     0, 0,
	      fx+1.f, fy, fz,     1, 0,
	      fx+1.f, fy, fz+1.f, 1, 1,
	      fx,     fy, fz+1.f, 0, 1,
	      0, -1, 0);
    }
    
    //left
    if( x+1==BoxelMap::mSizeX ||
	boxelMap.getBlock(x+1,y,z)==BoxelMap::mNothingId ||
	boxelMap.getBlock(x+1,y,z)==BoxelMap::mWaterId ){
      addQuad(fx+1.f, fy,     fz,     0, 0,
	      fx+1.f, fy+1.f, fz,     1, 0,
	      fx+1.f, fy+1.f, fz+1.f, 1, 1,
	      fx+1.f, fy,     fz+1.f, 0, 1,
	      1, 0, 0);
    }
    
    //right
    if( x==0 ||
	boxelMap.getBlock(x-1,y,z)==BoxelMap::mNothingId ||
	boxelMap.getBlock(x-1,y,z)==BoxelMap::mWaterId ){
      addQuad(fx, fy,     fz,     0, 0,
	      fx, fy+1.f, fz,     1, 0,
	      fx, fy+1.f, fz+1.f, 1, 1,
	      fx, fy,     fz+1.f, 0, 1,
	      -1, 0, 0);
    }
    
    //front
    if( z+1==BoxelMap::mSizeZ ||
	boxelMap.getBlock(x,y,z+1)==BoxelMap::mNothingId ||
	boxelMap.getBlock(x,y,z+1)==BoxelMap::mWaterId ){
      addQuad(fx,     fy,     fz+1.f, 0, 0,
	      fx+1.f, fy,     fz+1.f, 1, 0,
	      fx+1.f, fy+1.f, fz+1.f, 1, 1,
	      fx,     fy+1.f, fz+1.f, 0, 1,
	      0, 0, 1);
    }
    
    //back
    if( z==0 ||
	boxelMap.getBlock(x,y,z-1)==BoxelMap::mNothingId ||
	boxelMap.getBlock(x,y,z-1)==BoxelMap::mWaterId){
      addQuad(fx,     fy,     fz, 0, 0,
	      fx+1.f, fy,     fz, 1, 0,
	      fx+1.f, fy+1.f, fz, 1, 1,
	      fx,     fy+1.f, fz, 0, 1,
	      0, 0, -1);
      }	    
  }

  void generate(BoxelMap::BlockId type){
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

BoxelScene::BoxelScene():
  mWorld(math::Vector3i(1,1,1), math::Vector3i(200, 30, 200)),
  mBlockObject("BoxelObject")
{
  mBoxelMap.generate();

  //Meshing
  mBlockObject.model = Renderer::createModel("BoxelModel");

  mBlockObject.matrix.addTranslation(-static_cast<float>(BoxelMap::mSizeX) / 2.f,
					    -static_cast<float>(BoxelMap::mSizeY) / 2.f,
					    -static_cast<float>(BoxelMap::mSizeZ) / 2.f);
  
  for(std::size_t i(0); i<BoxelMap::mNbBlock; ++i){
    const BoxelMap::BlockType& type = mBoxelMap.getBlockType(i);
    if(type.visible){
      std::string filename = type.name+".dds";
      Renderer::Texture_handle tex = Renderer::createTexture(filename.c_str());
      mBlockMaterial[i] = Renderer::createMaterial(tex, type.name+"Material");

      if(type.withAlpha){
	Renderer::setWithAlpha(mBlockMaterial[i], true);
      }

      BoxelMesh mesh(mBoxelMap);
      mesh.generate(i);

	  if (mesh.vertices.size() != 0) {
		  Renderer::addSubMesh(mBlockObject.model,
			  mesh.vertices.size() / 3,
			  &mesh.vertices[0],
			  &mesh.texCoord[0],
			  &mesh.normals[0],
			  mesh.faces.size() / 3,
			  &mesh.faces[0],
			  mBlockMaterial[i]);
	  }
    }
  }
  
  //chunk.loadTexture();
  //chunk.mGrid.generateGrid();
  //chunk.generateMesh();
  debug::log("BoxelScene", "construct end");
}

BoxelScene::~BoxelScene(){
  debug::log("BoxelScene", "destruct");
}

void BoxelScene::addAction(Window& win){
  mCamera.addAction(win);
  mPlayer.addAction(win);
}
  
void BoxelScene::update(float frameTime){
  mCamera.update(frameTime);
}
