#pragma once

#include <System/Window.h>

class Scene {
public:
    virtual ~Scene() = default;

    virtual void addAction(Window &window) {};

    virtual void update(float frameTime) = 0;
};
