//
// Created by jngl on 10/07/2021.
//

#include "private_Graphics.h"

#include <SDL.h>
#include <SDL2/SDL_syswm.h>

#include <iostream>
#include <string>
#include <algorithm>

#include <bx/readerwriter.h>
#include <bx/file.h>

#include <bgfx/platform.h>

namespace cg::Impl{

    WindowSdl::WindowSdl(){
        if(SDL_Init(0) != 0){
            throw ck::GraphicsError{SDL_GetError()};
        }

        m_window = SDL_CreateWindow("OpenGL Test", 0, 0, windowSizeXDefault, windowSizeYDefault, SDL_WINDOW_RESIZABLE);
        if (m_window == nullptr) {
            throw ck::GraphicsError{SDL_GetError()};
        }
    }

    WindowSdl::~WindowSdl(){
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    SDL_Window* WindowSdl::GetSdlWindow(){
        return m_window;
    }

    void WindowSdl::swap(){
        SDL_GL_SwapWindow(m_window);
    }

    void* WindowSdl::sdlNativeWindowHandle()
    {
        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(m_window, &wmi) )
        {
            return NULL;
        }

#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
        #		if ENTRY_CONFIG_USE_WAYLAND
        wl_egl_window *win_impl = (wl_egl_window*)SDL_GetWindowData(_window, "wl_egl_window");
		if(!win_impl)
		{
			int width, height;
			SDL_GetWindowSize(_window, &width, &height);
			struct wl_surface* surface = wmi.info.wl.surface;
			if(!surface)
				return nullptr;
			win_impl = wl_egl_window_create(surface, width, height);
			SDL_SetWindowData(_window, "wl_egl_window", win_impl);
		}
		return (void*)(uintptr_t)win_impl;
#		else
        return reinterpret_cast<void*>(wmi.info.x11.window);
#		endif
#	elif BX_PLATFORM_OSX
        return wmi.info.cocoa.window;
#	elif BX_PLATFORM_WINDOWS
        return wmi.info.win.window;
#   else
        throw SystemError("Unknown platform in MySdlWindow");
#	endif // BX_PLATFORM_
    }

    [[nodiscard]] cc::Vector2ui WindowSdl::getSize() const {
        int x = 1;
        int y = 1;
        SDL_GetWindowSize(m_window, &x, &y);
        return cc::Vector2ui{static_cast<uint>(x), static_cast<uint>(y)};
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Context::Context(WindowSdl& win){
        sdlSetWindow(win);

        m_size = win.getSize();

        bgfx::renderFrame();

        bgfx::Init init;
        init.type = bgfx::RendererType::Vulkan;
        init.resolution.width  = m_size.x;
        init.resolution.height = m_size.y;
        bgfx::init(init);

        bgfx::setDebug(BGFX_DEBUG_TEXT);

        bgfx::setViewClear(0
                , BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
                , 0x303030ff
                , 1.0f
                , 0
        );
    }

    void Context::beginFrame(cc::Vector2ui newSize){
        if(newSize.x != m_size.x || newSize.y != m_size.y){
            std::cout<<"resize "<<newSize.x<<" "<<newSize.y<<std::endl;
            bgfx::reset(newSize.x, newSize.y);
            m_size = newSize;
        }

        bgfx::setViewRect(0, 0, 0, uint16_t(m_size.x), uint16_t(m_size.y) );
        bgfx::touch(0);

        bgfx::dbgTextClear();
        bgfx::dbgTextPrintf(0, 1, 0x0f, "win : %i %i", m_size.x, m_size.y);
    }

    bool Context::sdlSetWindow(WindowSdl& win)
    {
        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(win.GetSdlWindow(), &wmi) )
        {
            return false;
        }

        bgfx::PlatformData pd;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
        #		if ENTRY_CONFIG_USE_WAYLAND
    pd.ndt          = wmi.info.wl.display;
#		else
    pd.ndt          = wmi.info.x11.display;
#		endif
#	elif BX_PLATFORM_OSX
        pd.ndt          = NULL;
#	elif BX_PLATFORM_WINDOWS
        pd.ndt          = NULL;
#	endif // BX_PLATFORM_
        pd.nwh          = win.sdlNativeWindowHandle();

        pd.context      = NULL;
        pd.backBuffer   = NULL;
        pd.backBufferDS = NULL;
        bgfx::setPlatformData(pd);

        return true;
    }

    GraphicsApi Context::getApi() const {
        switch (bgfx::getRendererType()){
            case bgfx::RendererType::Noop:
                return GraphicsApi::Noop;
            case bgfx::RendererType::Direct3D9:
                return GraphicsApi::Direct3D9;
            case bgfx::RendererType::Direct3D11:
                return GraphicsApi::Direct3D11;
            case bgfx::RendererType::Direct3D12:
                return GraphicsApi::Direct3D12;
            case bgfx::RendererType::Gnm:
                return GraphicsApi::Gnm;
            case bgfx::RendererType::Metal:
                return GraphicsApi::Metal;
            case bgfx::RendererType::Nvn:
                return GraphicsApi::Nvn;
            case bgfx::RendererType::OpenGL:
                return GraphicsApi::OpenGL;
            case bgfx::RendererType::OpenGLES:
                return GraphicsApi::OpenGLES;
            case bgfx::RendererType::Vulkan:
                return GraphicsApi::Vulkan;
            case bgfx::RendererType::WebGPU:
                return GraphicsApi::WebGPU;
            default:
                throw ck::GraphicsError{"Unknown Graphics Api"};
        }
    }

    void Context::endFrame() {
        bgfx::frame();
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TextureManager::TextureManager() {
        namespace fs = std::filesystem;
        for(const auto& p: fs::directory_iterator("data")){
            loadTexture(p.path());
        }
    }

    void TextureManager::loadTexture(const std::filesystem::path& file) {
        if(file.extension() != ".dds" && file.extension() != ".png"){
            return;
        }

        m_textures.push_back(Texture{file});

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

    void TextureManager::loadTexture(ck::TextureHandle /*unused*/) {
    }

    void TextureManager::unloadTexture(ck::TextureHandle /*unused*/) {
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // TODO temporary
    static const bgfx::Memory* loadMem(bx::FileReaderI* _reader, const char* _filePath)
    {
        if (bx::open(_reader, _filePath) )
        {
            uint32_t size = (uint32_t)bx::getSize(_reader);
            const bgfx::Memory* mem = bgfx::alloc(size+1);
            bx::read(_reader, mem->data, size);
            bx::close(_reader);
            mem->data[mem->size-1] = '\0';
            return mem;
        }

        std::cout<<"Failed to load "<< _filePath<<std::endl;
        return nullptr;
    }

    static bx::FileReaderI* s_fileReader = NULL;

    ShaderManager::ShaderManager(Context& ctx):
            m_context(ctx)
    {
        s_fileReader = new bx::FileReader();

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

    bgfx::ShaderHandle ShaderManager::loadShader(std::string_view name) {
        std::string filePath = "./data/shader/" + std::string(GetGraphicsApiShaderType(m_context.getApi())) + "/" + std::string(name) + ".bin";

        bgfx::ShaderHandle handle = bgfx::createShader(loadMem(s_fileReader, filePath.c_str()) );
        bgfx::setName(handle, std::string(name).c_str());

        return handle;
    }

    void ShaderManager::loadShaderProgram(std::string_view name) {
        std::cout<<"load shader "<<name<<std::endl;

        bgfx::ShaderHandle vsh = loadShader(std::string("vs_")+std::string(name));
        bgfx::ShaderHandle fsh = loadShader(std::string("fs_")+std::string(name));

        bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh, true);

        m_shaders.push_back(Shader{std::string(name), program});
    }

    bgfx::ProgramHandle ShaderManager::get(ck::ShaderHandle handle) {
        if(handle.value() < 0 || handle.value() >= m_shaders.size()){
            return bgfx::ProgramHandle();
        }

        return m_shaders[handle.value()].m_program;
    }

    ck::ShaderHandle ShaderManager::getHandleFromFile(std::string_view filename) {
        auto isFileNameCorrect = [filename](const Shader& shader) -> bool{
            return shader.name == filename;
        };

        auto it = std::find_if(m_shaders.begin(), m_shaders.end(), isFileNameCorrect);

        if(it == std::end(m_shaders)){
            return ck::ShaderHandle();
        }

        unsigned int index = static_cast<unsigned int>(it - std::begin(m_shaders));

        return ck::ShaderHandle(index);
    }

    void ShaderManager::loadShader(ck::ShaderHandle /*handle*/) {

    }

    void ShaderManager::unloadShader(ck::ShaderHandle /*handle*/) {

    }

    std::string ShaderManager::getShaderDir() const {
        std::string shaderType(GetGraphicsApiShaderType(m_context.getApi()));
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
        bgfx::submit(0, m_program);
    }

    void Renderer2d::setShader(bgfx::ProgramHandle shader) {
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

    GraphicsData::GraphicsData():
            m_context(m_window),
            m_shaders(m_context)
    {
        m_renderer2d.setShader(m_shaders.get(m_shaders.getHandleFromFile("simple2d")));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Frame::Frame(Graphics &graphics):
            m_graphics(graphics)
    {
        auto size = m_graphics.m_data->m_window.getSize();
        m_graphics.m_data->m_context.beginFrame(size);
        m_graphics.m_data->m_renderer2d.updateSize(size);
    }

    ck::ColoredRectangleDrawer &Frame::getColoredRectangleDrawer() {
        return m_graphics.m_data->m_renderer2d;
    }

    Frame::~Frame() {
        m_graphics.m_data->m_context.endFrame();
    }
}