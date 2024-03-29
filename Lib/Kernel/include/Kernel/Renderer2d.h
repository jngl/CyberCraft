//
// Created by jngl on 11/11/2021.
//

#ifndef CYBERCRAFT_RENDERER2D_H
#define CYBERCRAFT_RENDERER2D_H

#include <CyberBase/Bases.h>

#include <Kernel/Engine2D.h>
#include <Ports/GpuAdapter.h>
#include <Ports/GpuProgram.h>

#include <memory>

namespace ck
{
    class Renderer2d :
            public cc::NonCopyable,
            public ck::ColoredRectangleDrawer
    {
    public:
        explicit Renderer2d(cp::GpuAdapter&);

        void updateSize(cc::Vector2ui size);

        void drawRectangle(const cc::Vector2f& pos, const cc::Vector2f& size, const cb::Color& color) override;
        void drawSprite(const cc::Vector2f& pos, const cc::Vector2f& size, const cp::Texture& texture);

        private:
        cp::GpuAdapter& m_gpuAdapter;
        std::shared_ptr<cp::VertexBuffer> m_rectangleVertices;
        std::shared_ptr<cp::IndexBuffer> m_rectangleIndices;
        std::shared_ptr<cp::GpuProgram> m_programColor;
        std::shared_ptr<cp::GpuProgram> m_programTexture;
        std::shared_ptr<cp::Uniform> m_color;
        std::shared_ptr<cp::Uniform> m_texture;

        void setViewTransform(const cc::Matrix4f& proj, const cc::Matrix4f& view);
    };
}

#endif //CYBERCRAFT_RENDERER2D_H
