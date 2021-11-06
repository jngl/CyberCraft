//
// Created by jngl on 10/07/2021.
//

#include "private_Graphics.h"

#include <string>
#include <algorithm>

#include <fmt/core.h>

#include "BimgAdapter.h"

#include <Core/Memory.h>

namespace cg::Impl{

    struct Pos2dVertex
    {
        float m_x;
        float m_y;
        float m_u;
        float m_v;

        static const VertexLayout& getLayout(){
            auto init = [](){
                VertexLayout layout;

                layout.begin();
                layout.add(Attrib::Position, 2, AttribType::Float);
                layout.add(Attrib::TexCoord0, 2, AttribType::Float);
                layout.end();

                return layout;
            };

            static VertexLayout layout = init();

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


    Renderer2d::Renderer2d(BgfxAdapter& bgfxAdapter):
            m_bgfxAdapter(bgfxAdapter),
            m_rectangleVertices(cc::ByteArrayView::fromArray(g_rectangleVerticesData), Pos2dVertex::getLayout()),
            m_rectangleIndices(cc::ByteArrayView::fromArray(g_rectangleIndicesData)),
            m_program(m_bgfxAdapter.getProgramFactory().loadProgramFromFile("simple2d")),
            m_textureTest(m_bgfxAdapter.getTextureFactory().loadTextureFromFile("dirt")),
            m_color(m_bgfxAdapter.getUniformFactory().createUniform("u_color", ck::Uniform::Type::Vec4, 1)),
            m_texture(m_bgfxAdapter.getUniformFactory().createUniform("u_texture", ck::Uniform::Type::Sampler, 1))
    {
    }

    void Renderer2d::drawRectangle(const cc::Vector2f &pos, const cc::Vector2f &size, const cc::Color &color) {
        std::string msg = fmt::format("Pos = {: 4.0f} ; {: 4.0f}       Size = {: 2.0f} ; {: 2.0f}       Color = {} {} {} {}",
                                      pos.x, pos.y, size.x, size.y, color.red, color.green, color.blue, color.alpha);
        m_bgfxAdapter.dbgTextPrint(0,0,msg);

        cc::Matrix4f transform;
        transform.addTranslation(pos.x, pos.y, 0.f);
        transform.addScale(size.x, size.y, 1.f);

        // Set model matrix for rendering.
        m_bgfxAdapter.setTransform(transform);

        // Set vertex and index buffer.
        m_bgfxAdapter.setVertexBuffer(0, m_rectangleVertices);
        m_bgfxAdapter.setIndexBuffer(m_rectangleIndices);

        m_color->setColor(color);
        m_texture->setTexture(*m_textureTest);

        // Submit primitive for rendering to view 0.
        m_bgfxAdapter.submit(*m_program);
    }

    void Renderer2d::updateSize(cc::Vector2ui size) {
        cc::Matrix4f proj;
        constexpr float dist = 100.f;
        proj.projectOrthographic(0, static_cast<float>(size.x), static_cast<float>(size.y), 0, -dist, dist);

        cc::Matrix4f view;

        setViewTransform(proj, view);
    }

    void Renderer2d::setViewTransform(const cc::Matrix4f &proj, const cc::Matrix4f &view) {
        bgfx::setViewTransform(0, view.m.data(), proj.m.data());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Common::Common():
            m_bgfxAdapter(m_window),
            m_renderer2d(m_bgfxAdapter)
    {
    }

    void Common::startFrame() {
        auto size = m_window.getSize();
        m_bgfxAdapter.beginFrame(size);
        m_renderer2d.updateSize(size);
    }

    void Common::endFrame() {
        m_bgfxAdapter.endFrame();
    }

    Renderer2d &Common::getRenderer2d() {
        return m_renderer2d;
    }

    void Common::processEvent(ck::ExitListener &exitListener, ck::KeyListener &keyListener) {
        m_window.processEvent(exitListener, keyListener);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    GraphicsImpl::GraphicsImpl()
    {
    }

    void GraphicsImpl::processEvent(ck::ExitListener &exitListener, ck::KeyListener &keyListener) {
        m_common.processEvent(exitListener, keyListener);
    }

    std::unique_ptr<Frame> GraphicsImpl::createFrame() {
        return std::make_unique<Impl::Frame>(m_common);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Frame::Frame(Common &common):
            m_common(&common)
    {
        m_common->startFrame();
    }

    ck::ColoredRectangleDrawer &Frame::getColoredRectangleDrawer() {
        return m_common->getRenderer2d();
    }

    Frame::~Frame() {
        if(m_common != nullptr){
            m_common->endFrame();
        }
    }

    Frame::Frame(Frame && other) noexcept {
        m_common = other.m_common;
        other.m_common = nullptr;
    }

    Frame &Frame::operator=(Frame && other) noexcept {
        m_common = other.m_common;
        other.m_common = nullptr;
        return *this;
    }
}