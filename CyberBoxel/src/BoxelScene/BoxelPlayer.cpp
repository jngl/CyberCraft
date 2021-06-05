#include "BoxelScene/BoxelPlayer.hpp"
#include "CubeData.hpp"

BoxelPlayer::BoxelPlayer() :
        mObject("PlayerObject") {
    mObject.model = Renderer::createModel("playerModel");

    cc::TextureHandle tex = Renderer::getHandleFromFile("test.dds");
    Renderer::loadTexture(tex);

    Renderer::Material_handle mat = Renderer::createMaterial(tex, "playerMaterial");
    //24
    Renderer::addSubMesh(mObject.model,
                         cubeNumberOfFace * cubeVertexByFace,
                         cubePos.data(),
                         cubeTexCoord.data(),
                         cubeNormal.data(),
                         cubeIndex.size() / 3,
                         cubeIndex.data(),
                         mat);

    constexpr cc::Vector3f defaultPos{0.5f, -3.1f, 0.5f};
    constexpr cc::Vector3f defaultScale{0.4f, 1.8f, 0.2f};

    mObject.matrix.addTranslation(defaultPos);
    mObject.matrix.addScale(defaultScale);
}

void BoxelPlayer::addAction(cs::Window&) {
}
