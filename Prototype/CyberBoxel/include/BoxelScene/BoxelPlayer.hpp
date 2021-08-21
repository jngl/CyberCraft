#pragma once

#include "Renderer.hpp"
#include <System/Window.h>

class BoxelPlayer {
public:
    BoxelPlayer();

    void addAction(cs::Window &window);

private:
    Renderer::Object mObject;
};
