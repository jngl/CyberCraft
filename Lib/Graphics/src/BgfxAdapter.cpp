//
// Created by jngl on 11/07/2021.
//

#include "BgfxAdapter.h"

#include "SdlWindowAdapter.h"
#include "BimgAdapter.h"

#include <Core/Debug.h>

#include "Kernel/Engine.h"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <SDL.h>
#include <SDL2/SDL_syswm.h>

#include <iostream>
#include <algorithm>

namespace cg::Impl {

    bgfx::TextureFormat::Enum convTextureFormat(TextureFormat format){
        switch (format) {
            case TextureFormat::BC1:
                return bgfx::TextureFormat::BC1;
            case TextureFormat::BC2:
                return bgfx::TextureFormat::BC2;
            case TextureFormat::BC3:
                return bgfx::TextureFormat::BC3;
            case TextureFormat::BC4:
                return bgfx::TextureFormat::BC4;
            case TextureFormat::BC5:
                return bgfx::TextureFormat::BC5;
            case TextureFormat::BC6H:
                return bgfx::TextureFormat::BC6H;
            case TextureFormat::BC7:
                return bgfx::TextureFormat::BC7;
            case TextureFormat::ETC1:
                return bgfx::TextureFormat::ETC1;
            case TextureFormat::ETC2:
                return bgfx::TextureFormat::ETC2;
            case TextureFormat::ETC2A:
                return bgfx::TextureFormat::ETC2A;
            case TextureFormat::ETC2A1:
                return bgfx::TextureFormat::ETC2A1;
            case TextureFormat::PTC12:
                return bgfx::TextureFormat::PTC12;
            case TextureFormat::PTC14:
                return bgfx::TextureFormat::PTC14;
            case TextureFormat::PTC12A:
                return bgfx::TextureFormat::PTC12A;
            case TextureFormat::PTC14A:
                return bgfx::TextureFormat::PTC14A;
            case TextureFormat::PTC22:
                return bgfx::TextureFormat::PTC22;
            case TextureFormat::PTC24:
                return bgfx::TextureFormat::PTC24;
            case TextureFormat::ATC:
                return bgfx::TextureFormat::ATC;
            case TextureFormat::ATCE:
                return bgfx::TextureFormat::ATCE;
            case TextureFormat::ATCI:
                return bgfx::TextureFormat::ATCI;
            case TextureFormat::ASTC4x4:
                return bgfx::TextureFormat::ASTC4x4;
            case TextureFormat::ASTC5x5:
                return bgfx::TextureFormat::ASTC5x5;
            case TextureFormat::ASTC6x6:
                return bgfx::TextureFormat::ASTC6x6;
            case TextureFormat::ASTC8x5:
                return bgfx::TextureFormat::ASTC8x5;
            case TextureFormat::ASTC8x6:
                return bgfx::TextureFormat::ASTC8x6;
            case TextureFormat::ASTC10x5:
                return bgfx::TextureFormat::ASTC10x5;
            case TextureFormat::R1:
                return bgfx::TextureFormat::R1;
            case TextureFormat::A8:
                return bgfx::TextureFormat::A8;
            case TextureFormat::R8:
                return bgfx::TextureFormat::R8;
            case TextureFormat::R8I:
                return bgfx::TextureFormat::R8I;
            case TextureFormat::R8U:
                return bgfx::TextureFormat::R8U;
            case TextureFormat::R8S:
                return bgfx::TextureFormat::R8S;
            case TextureFormat::R16:
                return bgfx::TextureFormat::R16;
            case TextureFormat::R16I:
                return bgfx::TextureFormat::R16I;
            case TextureFormat::R16U:
                return bgfx::TextureFormat::R16U;
            case TextureFormat::R16F:
                return bgfx::TextureFormat::R16F;
            case TextureFormat::R16S:
                return bgfx::TextureFormat::R16S;
            case TextureFormat::R32I:
                return bgfx::TextureFormat::R32I;
            case TextureFormat::R32U:
                return bgfx::TextureFormat::R32U;
            case TextureFormat::R32F:
                return bgfx::TextureFormat::R32F;
            case TextureFormat::RG8:
                return bgfx::TextureFormat::RG8;
            case TextureFormat::RG8I:
                return bgfx::TextureFormat::RG8I;
            case TextureFormat::RG8U:
                return bgfx::TextureFormat::RG8U;
            case TextureFormat::RG8S:
                return bgfx::TextureFormat::RG8S;
            case TextureFormat::RG16:
                return bgfx::TextureFormat::RG16;
            case TextureFormat::RG16I:
                return bgfx::TextureFormat::RG16I;
            case TextureFormat::RG16U:
                return bgfx::TextureFormat::RG16U;
            case TextureFormat::RG16F:
                return bgfx::TextureFormat::RG16F;
            case TextureFormat::RG16S:
                return bgfx::TextureFormat::RG16S;
            case TextureFormat::RG32I:
                return bgfx::TextureFormat::RG32I;
            case TextureFormat::RG32U:
                return bgfx::TextureFormat::RG32U;
            case TextureFormat::RG32F:
                return bgfx::TextureFormat::RG32F;
            case TextureFormat::RGB8:
                return bgfx::TextureFormat::RGB8;
            case TextureFormat::RGB8I:
                return bgfx::TextureFormat::RGB8I;
            case TextureFormat::RGB8U:
                return bgfx::TextureFormat::RGB8U;
            case TextureFormat::RGB8S:
                return bgfx::TextureFormat::RGB8S;
            case TextureFormat::RGB9E5F:
                return bgfx::TextureFormat::RGB9E5F;
            case TextureFormat::BGRA8:
                return bgfx::TextureFormat::BGRA8;
            case TextureFormat::RGBA8:
                return bgfx::TextureFormat::RGBA8;
            case TextureFormat::RGBA8I:
                return bgfx::TextureFormat::RGBA8I;
            case TextureFormat::RGBA8U:
                return bgfx::TextureFormat::RGBA8U;
            case TextureFormat::RGBA8S:
                return bgfx::TextureFormat::RGBA8S;
            case TextureFormat::RGBA16:
                return bgfx::TextureFormat::RGBA16;
            case TextureFormat::RGBA16I:
                return bgfx::TextureFormat::RGBA16I;
            case TextureFormat::RGBA16U:
                return bgfx::TextureFormat::RGBA16U;
            case TextureFormat::RGBA16F:
                return bgfx::TextureFormat::RGBA16F;
            case TextureFormat::RGBA16S:
                return bgfx::TextureFormat::RGBA16S;
            case TextureFormat::RGBA32I:
                return bgfx::TextureFormat::RGBA32I;
            case TextureFormat::RGBA32U:
                return bgfx::TextureFormat::RGBA32U;
            case TextureFormat::RGBA32F:
                return bgfx::TextureFormat::RGBA32F;
            case TextureFormat::R5G6B5:
                return bgfx::TextureFormat::R5G6B5;
            case TextureFormat::RGBA4:
                return bgfx::TextureFormat::RGBA4;
            case TextureFormat::RGB5A1:
                return bgfx::TextureFormat::RGB5A1;
            case TextureFormat::RGB10A2:
                return bgfx::TextureFormat::RGB10A2;
            case TextureFormat::RG11B10F:
                return bgfx::TextureFormat::RG11B10F;
            case TextureFormat::D16:
                return bgfx::TextureFormat::D16;
            case TextureFormat::D24:
                return bgfx::TextureFormat::D24;
            case TextureFormat::D24S8:
                return bgfx::TextureFormat::D24S8;
            case TextureFormat::D32:
                return bgfx::TextureFormat::D32;
            case TextureFormat::D16F:
                return bgfx::TextureFormat::D16F;
            case TextureFormat::D24F:
                return bgfx::TextureFormat::D24F;
            case TextureFormat::D32F:
                return bgfx::TextureFormat::D32F;
            case TextureFormat::D0S8:
                return bgfx::TextureFormat::D0S8;
            default:
                return bgfx::TextureFormat::Unknown;
        }
    }

    bgfx::UniformType::Enum convUniformType(UniformType type){
        switch (type) {
            case UniformType::Sampler:
                return bgfx::UniformType::Sampler;
            case UniformType::Mat3:
                return bgfx::UniformType::Mat3;
            case UniformType::Mat4:
                return bgfx::UniformType::Mat4;
            case UniformType::Vec4:
                return bgfx::UniformType::Vec4;
            default:
                return bgfx::UniformType::Count;
        }
    }

    bgfx::Attrib::Enum convAttrib(Attrib attrib){
        switch (attrib) {
            case Attrib::Position:
                return bgfx::Attrib::Position;
            case Attrib::Normal:
                return bgfx::Attrib::Normal;
            case Attrib::Tangent:
                return bgfx::Attrib::Tangent;
            case Attrib::Bitangent:
                return bgfx::Attrib::Bitangent;
            case Attrib::Color0:
                return bgfx::Attrib::Color0;
            case Attrib::Color1:
                return bgfx::Attrib::Color1;
            case Attrib::Color2:
                return bgfx::Attrib::Color2;
            case Attrib::Color3:
                return bgfx::Attrib::Color3;
            case Attrib::Indices:
                return bgfx::Attrib::Indices;
            case Attrib::Weight:
                return bgfx::Attrib::Weight;
            case Attrib::TexCoord0:
                return bgfx::Attrib::TexCoord0;
            case Attrib::TexCoord1:
                return bgfx::Attrib::TexCoord1;
            case Attrib::TexCoord2:
                return bgfx::Attrib::TexCoord2;
            case Attrib::TexCoord3:
                return bgfx::Attrib::TexCoord3;
            case Attrib::TexCoord4:
                return bgfx::Attrib::TexCoord4;
            case Attrib::TexCoord5:
                return bgfx::Attrib::TexCoord5;
            case Attrib::TexCoord6:
                return bgfx::Attrib::TexCoord6;
            case Attrib::TexCoord7:
                return bgfx::Attrib::TexCoord7;
            default:
                return bgfx::Attrib::Count;
        }
    }

    bgfx::AttribType::Enum convAttribType(AttribType type){
        switch (type) {
            case AttribType::Uint8:
                return bgfx::AttribType::Uint8;
            case AttribType::Uint10:
                return bgfx::AttribType::Uint10;
            case AttribType::Int16:
                return bgfx::AttribType::Int16;
            case AttribType::Half:
                return bgfx::AttribType::Half;
            case AttribType::Float:
                return bgfx::AttribType::Float;
            default:
                return bgfx::AttribType::Count;
        }
    }

    const bgfx::Memory* createBgfxMemory(const cc::ByteArray& mem){
        const bgfx::Memory* bgfxMem = bgfx::alloc(mem.size());
        memcpy(bgfxMem->data, mem.data(), mem.size());
        return bgfxMem;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BgfxAdapter::BgfxAdapter(SdlWindowAdapter& win){
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

    void BgfxAdapter::beginFrame(cc::Vector2ui newSize){
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

    bool BgfxAdapter::sdlSetWindow(SdlWindowAdapter& win)
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

    ck::GraphicsApi BgfxAdapter::getApi() const {
        switch (bgfx::getRendererType()){
            case bgfx::RendererType::Noop:
                return ck::GraphicsApi::Noop;
            case bgfx::RendererType::Direct3D9:
                return ck::GraphicsApi::Direct3D9;
            case bgfx::RendererType::Direct3D11:
                return ck::GraphicsApi::Direct3D11;
            case bgfx::RendererType::Direct3D12:
                return ck::GraphicsApi::Direct3D12;
            case bgfx::RendererType::Gnm:
                return ck::GraphicsApi::Gnm;
            case bgfx::RendererType::Metal:
                return ck::GraphicsApi::Metal;
            case bgfx::RendererType::Nvn:
                return ck::GraphicsApi::Nvn;
            case bgfx::RendererType::OpenGL:
                return ck::GraphicsApi::OpenGL;
            case bgfx::RendererType::OpenGLES:
                return ck::GraphicsApi::OpenGLES;
            case bgfx::RendererType::Vulkan:
                return ck::GraphicsApi::Vulkan;
            case bgfx::RendererType::WebGPU:
                return ck::GraphicsApi::WebGPU;
            default:
                throw ck::GraphicsError{"Unknown Graphics Api"};
        }
    }

    void BgfxAdapter::endFrame() {
        bgfx::frame();
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BgfxTexture::BgfxTexture(int width,
                             int height,
                             bool hasMips,
                             int numLayers,
                             TextureFormat format,
                             cc::Uint64 flags,
                             const cc::ByteArray &mem):
            m_handle(BGFX_INVALID_HANDLE)
    {
        load(width, height, hasMips, numLayers, format, flags, mem);
    }

    BgfxTexture::~BgfxTexture() {
        bgfx::destroy(m_handle);
    }

    BgfxTexture::BgfxTexture(std::string_view filePath, uint64_t _flags, Orientation *_orientation) {
        std::optional<cc::ByteArray> data = cc::ByteArray::loadFromFile(filePath);
        if (!data.has_value()) {
            throw cc::Error("Texture File not found");
        }

        std::optional<ImageContainer> imageContainer = imageParse(data.value());
        if (!imageContainer.has_value()){
            throw cc::Error(std::string("Texture File format not supported : ") + std::string(filePath));
        }

        if (nullptr != _orientation)
        {
            *_orientation = imageContainer->m_orientation;
        }

        if(!bgfx::isTextureValid(0,
                                 false,
                                 imageContainer->m_numLayers,
                                 bgfx::TextureFormat::Enum(imageContainer->m_format), _flags))
        {
            throw cc::Error("Invalid Texture");
        }

        load(
                uint16_t(imageContainer->m_width),
                uint16_t(imageContainer->m_height),
                1 < imageContainer->m_numMips,
                imageContainer->m_numLayers,
                imageContainer->m_format,
                _flags,
                imageContainer->data
        );
    }

    void BgfxTexture::load(int width,
                           int height,
                           bool hasMips,
                           int numLayers,
                           TextureFormat format,
                           cc::Uint64 flags,
                           const cc::ByteArray &mem)
    {
        const bgfx::Memory* bgfxMem = createBgfxMemory(mem);

        bgfx::TextureFormat::Enum bgfxFormat = convTextureFormat(format);

        m_handle = bgfx::createTexture2D(static_cast<uint16_t >(width),
                                         static_cast<uint16_t >(height),
                                         hasMips,
                                         static_cast<uint16_t >(numLayers),
                                         bgfxFormat,
                                         flags,
                                         bgfxMem);

        if(!bgfx::isValid(m_handle)){
            throw cc::Error("Error when loading a texture");
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BgfxTextureFactory::BgfxTextureFactory()
    {
        namespace fs = std::filesystem;
        for(const auto& p: fs::directory_iterator("data")){
            loadTexture(p.path());
        }
    }

    void BgfxTextureFactory::loadTexture(const std::filesystem::path& file) {
        if(file.extension() != ".dds" /*&& file.extension() != ".png"*/){
            return;
        }

        std::shared_ptr<BgfxTexture> texture( new BgfxTexture(file.string()));

        m_textures.push_back(Texture{file, texture});

        std::cout<<"load texture : "<<file.stem()<<"\n";
    }

    std::shared_ptr<ck::Texture> BgfxTextureFactory::loadTextureFromFile(std::string_view filename) {
        auto isFileNameCorrect = [filename](const Texture& texture) -> bool{
            return texture.file.stem() == filename;
        };

        auto it = std::find_if(m_textures.begin(), m_textures.end(), isFileNameCorrect);

        if(it == std::end(m_textures)){
            return {};
        }

        return it->texture;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    BgfxShader::BgfxShader(const cc::ByteArray& data) {
        const bgfx::Memory* bgfxMem = createBgfxMemory(data);
        m_handle = bgfx::createShader(bgfxMem);

        if(!bgfx::isValid(m_handle)){
            throw cc::Error("Error when loading a shader");
        }
    }

    BgfxShader::~BgfxShader() {
        if(bgfx::isValid(m_handle)) {
            bgfx::destroy(m_handle);
        }
    }

    bgfx::ShaderHandle BgfxShader::getHandle() {
        return m_handle;
    }

    BgfxShader::BgfxShader(BgfxShader && other) noexcept {
        m_handle = other.m_handle;
        other.m_handle = BGFX_INVALID_HANDLE;
    }

    BgfxShader &BgfxShader::operator=(BgfxShader && other) noexcept {
        m_handle = other.m_handle;
        other.m_handle = BGFX_INVALID_HANDLE;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    BgfxProgram::BgfxProgram(BgfxShader &vsh, BgfxShader &fsh) {
        m_handle = bgfx::createProgram(vsh.getHandle(), fsh.getHandle());

        if(!bgfx::isValid(m_handle)){
            throw cc::Error("Error when loading a shader program");
        }
    }

    BgfxProgram::~BgfxProgram() {
        if(bgfx::isValid(m_handle)){
            bgfx::destroy(m_handle);
        }
    }

    bgfx::ProgramHandle BgfxProgram::getHandle() {
        return m_handle;
    }

    BgfxProgram::BgfxProgram(BgfxProgram && other) noexcept:
            m_handle(other.m_handle){
        other.m_handle = BGFX_INVALID_HANDLE;
    }

    BgfxProgram &BgfxProgram::operator=(BgfxProgram && other) noexcept{
        m_handle = other.m_handle;
        other.m_handle = BGFX_INVALID_HANDLE;
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    BgfxUniform::BgfxUniform(std::string_view name, UniformType type, int num) {
        m_handle = bgfx::createUniform(std::string(name).c_str(), convUniformType(type), static_cast<uint16_t >(num));
    }

    BgfxUniform::~BgfxUniform() {
        if(bgfx::isValid(m_handle)) {
            bgfx::destroy(m_handle);
        }
    }

    bgfx::UniformHandle BgfxUniform::getHandle() {
        return m_handle;
    }

    void BgfxUniform::setColor(const cc::Color & color) {
        float colorTmp[4] = {static_cast<float>(color.red) / 255.f,
                             static_cast<float>(color.green) / 255.f,
                             static_cast<float>(color.blue) / 255.f,
                             static_cast<float>(color.alpha) / 255.f};
        bgfx::setUniform(m_handle, colorTmp, 1);
    }

    BgfxUniform::BgfxUniform(BgfxUniform && other) noexcept{
        m_handle = other.m_handle;
        other.m_handle = BGFX_INVALID_HANDLE;
    }

    BgfxUniform &BgfxUniform::operator=(BgfxUniform && other) noexcept {
        m_handle = other.m_handle;
        other.m_handle = BGFX_INVALID_HANDLE;
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    BgfxProgramFactory::BgfxProgramFactory(BgfxAdapter& bgfxAdapter):
    m_bgfxAdapter(bgfxAdapter){
        namespace fs = std::filesystem;
        for (const auto &p: fs::directory_iterator(getProgramDir())) {
            auto name = fileStemToProgramName(p.path().stem().string());
            if(name.has_value()){
                loadProgramProgram(name.value());
            }
        }
    }

    std::shared_ptr<BgfxProgram> BgfxProgramFactory::loadProgramFromFile(std::string_view filename) {
        auto isFileNameCorrect = [filename](const Program& program) -> bool{
            return program.file.stem() == filename;
        };

        auto it = std::find_if(m_programs.begin(), m_programs.end(), isFileNameCorrect);

        if(it == std::end(m_programs)){
            return {};
        }

        return it->program;
    }

    std::string BgfxProgramFactory::getProgramDir() const {
        std::string shaderType(ck::GetGraphicsApiShaderType(m_bgfxAdapter.getApi()));
        return "data/shader/" + shaderType;
    }

    std::optional<std::string> BgfxProgramFactory::fileStemToProgramName(std::string_view fileStem) {
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

    BgfxShader BgfxProgramFactory::loadShader(std::string_view name) {
        std::string filePath = "./data/shader/" + std::string(ck::GetGraphicsApiShaderType(m_bgfxAdapter.getApi())) + "/" + std::string(name) + ".bin";
        std::optional<cc::ByteArray> memory = cc::ByteArray::loadFromFile(filePath);
        if(!memory.has_value()){
            throw cc::Error("error while opening a shader file");
        }
        BgfxShader shader(memory.value());
        return shader;
    }

    void BgfxProgramFactory::loadProgramProgram(std::string_view name) {
        std::cout<<"load shader "<<name<<std::endl;

        BgfxShader vsh = loadShader(std::string("vs_") + std::string(name));
        BgfxShader fsh = loadShader(std::string("fs_") + std::string(name));

        std::shared_ptr<BgfxProgram> program = std::make_shared<BgfxProgram>(vsh, fsh);

        m_programs.push_back(Program{std::string(name), program});
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    void VertexLayout::begin() {
        m_layout.begin();
    }

    void VertexLayout::add(Attrib attrib, uint8_t num, AttribType type, bool normalized, bool asInt) {
        bgfx::Attrib::Enum bgfxAttrib = convAttrib(attrib);
        bgfx::AttribType::Enum bgfxType = convAttribType(type);
        m_layout.add(bgfxAttrib, num, bgfxType, normalized, asInt);
    }

    void VertexLayout::end() {
        m_layout.end();
    }

    const bgfx::VertexLayout &VertexLayout::getBgfxLayout() const {
        return m_layout;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    VertexBuffer::VertexBuffer(const cc::ByteArray& data, const VertexLayout& layout) {
        m_handle  = bgfx::createVertexBuffer(
                createBgfxMemory(data),
                layout.getBgfxLayout()
        );
    }

    VertexBuffer::~VertexBuffer() {
        bgfx::destroy(m_handle);
    }

    bgfx::VertexBufferHandle VertexBuffer::getBgfxHandle() const {
        return m_handle;
    }
}
