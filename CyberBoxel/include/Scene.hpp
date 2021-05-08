#pragma once

#include <System/Window.h>

class Scene {
public:
    virtual ~Scene() = default;

    virtual void addAction(cs::Window &window) {};

    virtual void update(float frameTime) = 0;
};
