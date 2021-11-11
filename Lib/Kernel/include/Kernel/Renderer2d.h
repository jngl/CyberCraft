//
// Created by jngl on 11/11/2021.
//

#ifndef CYBERCRAFT_RENDERER2D_H
#define CYBERCRAFT_RENDERER2D_H

#include <Core/Bases.h>

#include <Kernel/Engine2D.h>
#include <Kernel/GpuAdapter.h>
#include <Kernel/GpuProgram.h>

#include <memory>

namespace ck
{
    class Renderer2d : public cc::NonCopyable, public ck::ColoredRectangleDrawer {
    public:
        explicit Renderer2d(ck::GpuAdapter&);

        void updateSize(cc::Vector2ui size);

        void drawRectangle(const cc::Vector2f& pos, const cc::Vector2f& size, const cc::Color& color) override;

        private:
        ck::GpuAdapter& m_gpuAdapter;
        std::shared_ptr<cp::VertexBuffer> m_rectangleVertices;
        std::shared_ptr<cp::IndexBuffer> m_rectangleIndices;
        std::shared_ptr<ck::GpuProgram> m_program;
        std::shared_ptr<cp::Texture> m_textureTest;
        std::shared_ptr<ck::Uniform> m_color;
        std::shared_ptr<ck::Uniform> m_texture;

        void setViewTransform(const cc::Matrix4f& proj, const cc::Matrix4f& view);
    };
}

#endif //CYBERCRAFT_RENDERER2D_H
