//
// Created by jngl on 29/08/2020.
//

#ifndef CYBERCRAFT_WINDOWSFML_H
#define CYBERCRAFT_WINDOWSFML_H

#include <Core/Window.h>

#include <memory>

class WindowSfmlImpl;

class WindowSFML : public Window {
public:
    WindowSFML();
    ~WindowSFML() override;

    GraphicsContext& getGraphicsContext() override;

    [[nodiscard]] bool isOpen() const override;

    void beginFrame() override;
    void endFrame() override;

private:
    std::unique_ptr<WindowSfmlImpl> m_impl;
};



#endif //CYBERCRAFT_WINDOWSFML_H
