#pragma once

#include <Core/Math.h>

#include "../Renderer.hpp"

#include <System/Window.h>

class BoxelCamera {
public:
    BoxelCamera();

    void addAction(cc::System::Window &window);

    void update(float frameTime);

private:
    static constexpr float defaultDist = 60.f;

    Renderer::Camera_handle mRendererCamera;

    float mDist;
    cc::Vector3f mPosition;
    cc::Vector2f mAngle;

    bool mActionRotateUp, mActionRotateDown, mActionRotateLeft, mActionRotateRight, mActionMoveForward, mActionMoveBackward;
};
