//
// Created by jngl on 05/06/2021.
//

#ifndef CYBERCRAFT_RENDERER2D_H
#define CYBERCRAFT_RENDERER2D_H

#include <Core/Bases.h>
#include <Core/Math.h>
#include <Core/Color.h>

#include <bgfx/bgfx.h>

class Renderer2d : public cc::NonCopyable {
public:
    Renderer2d();
    ~Renderer2d() override;

    void setViewTransform(const cc::Matrix4f& proj, const cc::Matrix4f& view);

    void drawRectangle(const cc::Vector2f& pos, const cc::Vector2f& size, const cc::Color& color);

private:
    bgfx::VertexBufferHandle m_rectangleVertices{};
    bgfx::IndexBufferHandle m_rectangleIndices{};
    bgfx::ProgramHandle m_program{};
};


#endif //CYBERCRAFT_RENDERER2D_H
