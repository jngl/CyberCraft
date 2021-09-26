//
// Created by jngl on 10/07/2021.
//

#include "private_Graphics.h"

#include <Core/Debug.h>

#include <iostream>
#include <string>
#include <algorithm>
#include <optional>

#include "BimgAdapter.h"

namespace cg::Impl{

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextureHandle loadTextureFile(BgfxAdapter& bgfxAdapter,
                                    std::string_view filePath,
                                    uint64_t _flags,
                                    Orientation* _orientation)
    {


        std::optional<cc::ByteArray> data = cc::ByteArray::loadFromFile(filePath);
        if (!data.has_value()) {
            throw cc::Error("Texture File not found");
        }

        std::optional<ImageContainer> imageContainer = imageParse(data.value());
        if (!imageContainer.has_value()){
            throw cc::Error(std::string("Texture File format not supported : ") + std::string(filePath));
        }

        TextureHandle handle;
       /*

            if (imageContainer.has_value())
            {
                if (nullptr != _orientation)
                {
                    *_orientation = imageContainer->m_orientation;
                }

                if (bgfx::isTextureValid(0,
                                              false,
                                              imageContainer->m_numLayers,
                                              bgfx::TextureFormat::Enum(imageContainer->m_format), _flags) )
                {
                    bgfxAdapter.createTexture2D(
                            uint16_t(imageContainer->m_width),
                            uint16_t(imageContainer->m_height),
                            1 < imageContainer->m_numMips,
                            imageContainer->m_numLayers,
                            imageContainer->m_format,
                            _flags,
                            imageContainer->data
                            );
                }

//                if (bgfx::isValid(handle) )
//                {
//                    bgfx::setName(handle, _filePath);
//                }

            }*/

        return handle;
    }

    TextureManager::TextureManager(BgfxAdapter& bgfxAdapter):
    m_bgfxAdapter(bgfxAdapter)
    {
        namespace fs = std::filesystem;
        for(const auto& p: fs::directory_iterator("data")){
            loadTexture(p.path());
        }
    }

    void TextureManager::loadTexture(const std::filesystem::path& file) {
        if(file.extension() != ".dds" /*&& file.extension() != ".png"*/){
            return;
        }

        TextureHandle texture = loadTextureFile(m_bgfxAdapter, file.string(), 0, nullptr);

        m_textures.push_back(Texture{file, texture});

        std::cout<<"load texture : "<<file.stem()<<"\n";
    }

    ck::TextureHandle TextureManager::getHandleFromFile(std::string_view filename) {
        auto isFileNameCorrect = [filename](const Texture& texture) -> bool{
            return texture.file.stem() == filename;
        };

        auto it = std::find_if(m_textures.begin(), m_textures.end(), isFileNameCorrect);

        if(it == std::end(m_textures)){
            return ck::TextureHandle();
        }

        unsigned int index = static_cast<unsigned int>(it - std::begin(m_textures));

        return ck::TextureHandle(index);
    }

    void TextureManager::loadTexture(ck::TextureHandle) {
    }

    void TextureManager::unloadTexture(ck::TextureHandle) {
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ShaderManager::ShaderManager(BgfxAdapter& bgfxAdapter):
            m_bgfxAdapter(bgfxAdapter)
    {
        namespace fs = std::filesystem;
        for (const auto &p: fs::directory_iterator(getShaderDir())) {
            auto name = fileStemToShaderName(p.path().stem().string());
            if(name.has_value()){
                loadShaderProgram(name.value());
            }
        }
    }

    std::optional<std::string> ShaderManager::fileStemToShaderName(std::string_view fileStem) {
        size_t indexUnderscore = fileStem.find('_');
        if (indexUnderscore == std::string::npos) {
            return {};
        }

        std::string prefix(fileStem.substr(0, indexUnderscore));
        std::string name(fileStem.substr(indexUnderscore + 1));

        if (prefix != "vs") {
            return {};
        }

        return {name};
    }

    ShaderHandle ShaderManager::loadShader(std::string_view name) {
        std::string filePath = "./data/shader/" + std::string(GetGraphicsApiShaderType(m_bgfxAdapter.getApi())) + "/" + std::string(name) + ".bin";
        std::optional<cc::ByteArray> memory = cc::ByteArray::loadFromFile(filePath);
        if(!memory.has_value()){
            std::cout<<"error while loading the shader "<<name<<std::endl;
            return {};
        }
        return m_bgfxAdapter.createShader(memory.value());
    }

    void ShaderManager::loadShaderProgram(std::string_view name) {
        std::cout<<"load shader "<<name<<std::endl;

        ShaderHandle vsh = loadShader(std::string("vs_")+std::string(name));
        ShaderHandle fsh = loadShader(std::string("fs_")+std::string(name));

        ProgramHandle program = m_bgfxAdapter.createProgram(vsh, fsh, true);

        m_shaders.push_back(Shader{std::string(name), program});
    }

    ProgramHandle ShaderManager::getHandleFromFile(std::string_view filename) {
        auto isFileNameCorrect = [filename](const Shader& shader) -> bool{
            return shader.name == filename;
        };

        auto it = std::find_if(m_shaders.begin(), m_shaders.end(), isFileNameCorrect);

        if(it == std::end(m_shaders)){
            return {};
        }

        return it->m_program;
    }

    std::string ShaderManager::getShaderDir() const {
        std::string shaderType(GetGraphicsApiShaderType(m_bgfxAdapter.getApi()));
        return "data/shader/" + shaderType;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
    }

    Renderer2d::~Renderer2d() {
        bgfx::destroy(m_rectangleIndices);
        bgfx::destroy(m_rectangleVertices);
    }

    void Renderer2d::drawRectangle(const cc::Vector2f &pos, const cc::Vector2f &size, const cc::Color &color) {
        bgfx::dbgTextPrintf(0, 0, 0x0f,
                            "rect : %.2f %.2f %.2f %.2f %i %i %i %i",
                            static_cast<double>(pos.x),
                            static_cast<double>(pos.y),
                            static_cast<double>(size.x),
                            static_cast<double>(size.y),
                            static_cast<int>(color.red),
                            static_cast<int>(color.green),
                            static_cast<int>(color.blue),
                            static_cast<int>(color.alpha));

        cc::Matrix4f transform;
        transform.addTranslation(pos.x, pos.y, 0.f);
        transform.addScale(size.x, size.y, 1.f);

        // Set model matrix for rendering.
        bgfx::setTransform(transform.m.data());

        // Set vertex and index buffer.
        bgfx::setVertexBuffer(0, m_rectangleVertices);
        bgfx::setIndexBuffer(m_rectangleIndices);

        float colorTmp[4] = {static_cast<float>(color.red) / 255.f,
                             static_cast<float>(color.green) / 255.f,
                             static_cast<float>(color.blue) / 255.f,
                             static_cast<float>(color.alpha) / 255.f};

        bgfx::setUniform(m_color, colorTmp, 1);

        // Submit primitive for rendering to view 0.
        bgfx::submit(0, bgfx::ProgramHandle{static_cast<uint16_t>(m_program.value())});
    }

    void Renderer2d::setShader(ProgramHandle shader) {
        m_program = shader;

        m_color = bgfx::createUniform("u_color", bgfx::UniformType::Vec4, 1);
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
            m_textures(m_bgfxAdapter),
            m_shaders(m_bgfxAdapter)
    {
        m_renderer2d.setShader(m_shaders.getHandleFromFile("simple2d"));
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
            m_common(common)
    {
        m_common.startFrame();
    }

    ck::ColoredRectangleDrawer &Frame::getColoredRectangleDrawer() {
        return m_common.getRenderer2d();
    }

    Frame::~Frame() {
        m_common.endFrame();
    }
}