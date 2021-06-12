//
// Created by jngl on 05/06/2021.
//

#include "Renderer2d.h"

#include <array>

struct Pos2dVertex
{
    float m_x;
    float m_y;

    static const bgfx::VertexLayout& getLayout(){
        auto init = [](){
            bgfx::VertexLayout layout;

            layout.begin();
            layout.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float);
            layout.end();

            return layout;
        };

        static bgfx::VertexLayout layout = init();

        return layout;
    }
};

constexpr std::array<Pos2dVertex, 4> g_rectangleVerticesData{
        {
                {-1.0f, 1.0f},
                {1.0f,  1.0f},
                {-1.0f, -1.0f},
                {1.0f,  -1.0f}
        }
};

constexpr std::array<uint16_t, 6> g_rectangleIndicesData{
        {
                0, 1, 2,
                1, 3, 2,
        }
};


Renderer2d::Renderer2d() {
    m_rectangleVertices  = bgfx::createVertexBuffer(
            bgfx::makeRef(g_rectangleVerticesData.data(), sizeof(g_rectangleVerticesData) ),
            Pos2dVertex::getLayout()
    );

    m_rectangleIndices = bgfx::createIndexBuffer(
            bgfx::makeRef(g_rectangleIndicesData.data(), sizeof(g_rectangleIndicesData) )
    );

    // TODO shader
}

Renderer2d::~Renderer2d() {
    bgfx::destroy(m_rectangleIndices);
    bgfx::destroy(m_rectangleVertices);
}

void Renderer2d::drawRectangle(const cc::Vector2f &pos, const cc::Vector2f &size, const cc::Color &color) {
    cc::Matrix4f transform;
    transform.addTranslation(pos.x, pos.y, 0.f);
    transform.addScale(size.x, size.y, 1.f);

    // Set model matrix for rendering.
    bgfx::setTransform(transform.m.data());

    // Set vertex and index buffer.
    bgfx::setVertexBuffer(0, m_rectangleVertices);
    bgfx::setIndexBuffer(m_rectangleIndices);

    // Submit primitive for rendering to view 0.
    bgfx::submit(0, {0});
}

void Renderer2d::setViewTransform(const cc::Matrix4f &proj, const cc::Matrix4f &view) {
    bgfx::setViewTransform(0, view.m.data(), proj.m.data());
}
