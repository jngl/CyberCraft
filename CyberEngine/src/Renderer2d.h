//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_RENDERER2D_H
#define CYBERCRAFT_RENDERER2D_H

#include <Core/Bases.h>
#include <Core/Math.h>
#include <Core/Color.h>
#include <Core/Engine2D.h>

#include <bgfx/bgfx.h>

class Renderer2d : public cc::NonCopyable, public cc::ColoredRectangleDrawer {
public:
    Renderer2d();
    ~Renderer2d() override;

    void setShader(bgfx::ProgramHandle shader);

    void updateSize(cc::Vector2ui size);

    void drawRectangle(const cc::Vector2f& pos, const cc::Vector2f& size, const cc::Color& color) override;

private:
    bgfx::VertexBufferHandle m_rectangleVertices{};
    bgfx::IndexBufferHandle m_rectangleIndices{};
    bgfx::ProgramHandle m_program{};

    void setViewTransform(const cc::Matrix4f& proj, const cc::Matrix4f& view);
};


#endif //CYBERCRAFT_RENDERER2D_H
