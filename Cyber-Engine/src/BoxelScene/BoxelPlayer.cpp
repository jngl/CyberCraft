#include "BoxelScene/BoxelPlayer.hpp"
#include "CubeData.hpp"

BoxelPlayer::BoxelPlayer():
  mObject("PlayerObject")
{
  mObject.model = Renderer::createModel("playerModel");

   Renderer::Texture_handle tex = Renderer::createTexture("test.dds");
   
   Renderer::Material_handle mat = Renderer::createMaterial(tex, "playerMaterial");
  
   Renderer::addSubMesh(mObject.model,
			   cubeVerticesSize      ,
			   cubePos                 ,
			   cubeTexCoord,
			   cubeNormal,
			   cubeIndexSize / 3,
			   cubeIndex,
			   mat);

   mObject.matrix.addTranslation(0.5f, -3.1f, 0.5f);
   mObject.matrix.addScale(0.4f, 1.8f, 0.2f);
}

void BoxelPlayer::addAction(Window& window){
  
}
