//
// Created by jngl on 11/11/2021.
//

#include "Kernel/Renderer2d.h"

#include <Core/Memory.h>

#include <Kernel/GpuBuffer.h>

#include <fmt/core.h>

namespace ck
{
    struct Pos2dVertex
    {
        float m_x;
        float m_y;
        float m_u;
        float m_v;

        static std::unique_ptr<ck::VertexLayout> getLayout(ck::GpuBufferFactory& factory){
            std::unique_ptr<ck::VertexLayout> layout = factory.createVertexLayout();

            layout->begin();
            layout->add(ck::Attrib::Position, 2, ck::AttribType::Float);
            layout->add(ck::Attrib::TexCoord0, 2, ck::AttribType::Float);
            layout->end();

            return layout;
        }
    };

    constexpr std::array<Pos2dVertex, 4> g_rectangleVerticesData{
            {
                    {-1.0f, 1.0f, 0.f, 1.f},
                    {1.0f,  1.0f, 1.f, 1.f},
                    {-1.0f, -1.0f, 0.f, 0.f},
                    {1.0f,  -1.0f, 1.f, 0.f}
            }
    };

    constexpr std::array<uint16_t, 6> g_rectangleIndicesData{
            {
                    0, 1, 2,
                    1, 3, 2,
            }
    };


    Renderer2d::Renderer2d(ck::GpuAdapter& bgfxAdapter):
            m_gpuAdapter(bgfxAdapter),
            m_rectangleVertices(m_gpuAdapter.getBufferFactory().createVertexBuffer(
                    cc::ByteArrayView::fromArray(g_rectangleVerticesData),
                    *Pos2dVertex::getLayout(m_gpuAdapter.getBufferFactory()))),
            m_rectangleIndices(m_gpuAdapter.getBufferFactory().createIndexBuffer(
                    cc::ByteArrayView::fromArray(g_rectangleIndicesData))),
            m_program(m_gpuAdapter.getProgramFactory().loadProgramFromFile("simple2d")),
            m_textureTest(m_gpuAdapter.getTextureFactory().loadTextureFromFile("dirt")),
            m_color(m_gpuAdapter.getUniformFactory().createUniform("u_color", ck::Uniform::Type::Vec4, 1)),
            m_texture(m_gpuAdapter.getUniformFactory().createUniform("u_texture", ck::Uniform::Type::Sampler, 1))
    {
    }

    void Renderer2d::drawRectangle(const cc::Vector2f &pos, const cc::Vector2f &size, const cc::Color &color) {
        std::string msg = fmt::format("Pos = {: 4.0f} ; {: 4.0f}       Size = {: 2.0f} ; {: 2.0f}       Color = {} {} {} {}",
                                      pos.x, pos.y, size.x, size.y, color.red, color.green, color.blue, color.alpha);
        m_gpuAdapter.dbgTextPrint(0, 0, msg);

        cc::Matrix4f transform;
        transform.addTranslation(pos.x, pos.y, 0.f);
        transform.addScale(size.x, size.y, 1.f);

        // Set model matrix for rendering.
        m_gpuAdapter.setTransform(transform);

        // Set vertex and index buffer.
        m_gpuAdapter.setVertexBuffer(0, *m_rectangleVertices);
        m_gpuAdapter.setIndexBuffer(*m_rectangleIndices);

        m_color->setColor(color);
        m_texture->setTexture(*m_textureTest);

        // Submit primitive for rendering to view 0.
        m_gpuAdapter.submit(*m_program);
    }

    void Renderer2d::updateSize(cc::Vector2ui size) {
        cc::Matrix4f proj;
        constexpr float dist = 100.f;
        proj.projectOrthographic(0, static_cast<float>(size.x), static_cast<float>(size.y), 0, -dist, dist);

        cc::Matrix4f view;

        setViewTransform(proj, view);
    }

    void Renderer2d::setViewTransform(const cc::Matrix4f &proj, const cc::Matrix4f &view) {
        m_gpuAdapter.setViewTransform(proj, view);
    }
}