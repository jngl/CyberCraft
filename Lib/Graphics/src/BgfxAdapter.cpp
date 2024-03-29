//
// Created by jngl on 11/07/2021.
//

#include "BgfxAdapterPrivate.h"

#include "SdlWindowAdapter.h"
#include "BimgAdapter.h"

#include <CyberBase/Error.hpp>
#include <CyberBase/Color.hpp>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

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

    bgfx::UniformType::Enum convUniformType(cp::Uniform::Type type){
        switch (type) {
            case cp::Uniform::Type::Sampler:
                return bgfx::UniformType::Sampler;
            case cp::Uniform::Type::Mat3:
                return bgfx::UniformType::Mat3;
            case cp::Uniform::Type::Mat4:
                return bgfx::UniformType::Mat4;
            case cp::Uniform::Type::Vec4:
                return bgfx::UniformType::Vec4;
            default:
                return bgfx::UniformType::Count;
        }
    }

    bgfx::Attrib::Enum convAttrib(cp::Attrib attrib){
        switch (attrib) {
            case cp::Attrib::Position:
                return bgfx::Attrib::Position;
            case cp::Attrib::Normal:
                return bgfx::Attrib::Normal;
            case cp::Attrib::Tangent:
                return bgfx::Attrib::Tangent;
            case cp::Attrib::Bitangent:
                return bgfx::Attrib::Bitangent;
            case cp::Attrib::Color0:
                return bgfx::Attrib::Color0;
            case cp::Attrib::Color1:
                return bgfx::Attrib::Color1;
            case cp::Attrib::Color2:
                return bgfx::Attrib::Color2;
            case cp::Attrib::Color3:
                return bgfx::Attrib::Color3;
            case cp::Attrib::Indices:
                return bgfx::Attrib::Indices;
            case cp::Attrib::Weight:
                return bgfx::Attrib::Weight;
            case cp::Attrib::TexCoord0:
                return bgfx::Attrib::TexCoord0;
            case cp::Attrib::TexCoord1:
                return bgfx::Attrib::TexCoord1;
            case cp::Attrib::TexCoord2:
                return bgfx::Attrib::TexCoord2;
            case cp::Attrib::TexCoord3:
                return bgfx::Attrib::TexCoord3;
            case cp::Attrib::TexCoord4:
                return bgfx::Attrib::TexCoord4;
            case cp::Attrib::TexCoord5:
                return bgfx::Attrib::TexCoord5;
            case cp::Attrib::TexCoord6:
                return bgfx::Attrib::TexCoord6;
            case cp::Attrib::TexCoord7:
                return bgfx::Attrib::TexCoord7;
            default:
                return bgfx::Attrib::Count;
        }
    }

    bgfx::AttribType::Enum convAttribType(cp::AttribType type){
        switch (type) {
            case cp::AttribType::Uint8:
                return bgfx::AttribType::Uint8;
            case cp::AttribType::Uint10:
                return bgfx::AttribType::Uint10;
            case cp::AttribType::Int16:
                return bgfx::AttribType::Int16;
            case cp::AttribType::Half:
                return bgfx::AttribType::Half;
            case cp::AttribType::Float:
                return bgfx::AttribType::Float;
            default:
                return bgfx::AttribType::Count;
        }
    }

    const bgfx::Memory* createBgfxMemory(const cc::ByteArrayView& mem){
        const bgfx::Memory* bgfxMem = bgfx::alloc(mem.size());
        memcpy(bgfxMem->data, mem.data(), mem.size());
        return bgfxMem;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BgfxAdapter::BgfxAdapter(SdlWindowAdapter& win):
        m_context(win),
        m_programs(m_context)
    {
    }

    void BgfxAdapter::beginFrame(cc::Vector2ui newSize){
        m_context.beginFrame(newSize);
    }

    cp::GraphicsApi BgfxAdapter::getApi() const {
        return m_context.getApi();
    }

    void BgfxAdapter::endFrame() {
        m_context.endFrame();
    }

    cp::GpuProgramFactory &BgfxAdapter::getProgramFactory() {
        return m_programs;
    }

    void BgfxAdapter::setTransform(const cc::Matrix4f &transform) {
        bgfx::setTransform(transform.m.data());
    }

    void BgfxAdapter::setVertexBuffer(uint8_t stream, const cp::VertexBuffer&vertices) {
        const auto* bgfxBuffer = dynamic_cast<const BgfxVertexBuffer*>(&vertices);
        if(bgfxBuffer != nullptr){
            bgfx::setVertexBuffer(0, bgfxBuffer->getBgfxHandle());
        }
    }

    void BgfxAdapter::setIndexBuffer(const cp::IndexBuffer &indices) {
        const auto* bgfxBuffer = dynamic_cast<const BgfxIndexBuffer*>(&indices);
        if(bgfxBuffer != nullptr){
            bgfx::setIndexBuffer(bgfxBuffer->getBgfxHandle());
        }
    }

    void BgfxAdapter::submit(const cp::GpuProgram &program) {
        const auto* bgfxProgram = dynamic_cast<const BgfxProgram*>(&program);
        if(bgfxProgram != nullptr){
            bgfx::submit(0, bgfxProgram->getHandle());
        }
    }

    void BgfxAdapter::dbgTextPrint(uint16_t _x, uint16_t _y, std::string_view text) {
        std::string textStr(text);
        bgfx::dbgTextPrintf(0, 0, 0x0f, textStr.c_str());
    }

    cp::TextureFactory &BgfxAdapter::getTextureFactory() {
        return m_textures;
    }

    cp::UniformFactory &BgfxAdapter::getUniformFactory() {
        return m_uniforms;
    }

    cp::GpuBufferFactory &BgfxAdapter::getBufferFactory() {
        return m_buffers;
    }

    void BgfxAdapter::setViewTransform(const cc::Matrix4f &proj, const cc::Matrix4f &view) {
        bgfx::setViewTransform(0, view.m.data(), proj.m.data());
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BgfxTexture::BgfxTexture(int width,
                             int height,
                             bool hasMips,
                             int numLayers,
                             TextureFormat format,
                             cc::Uint64 flags,
                             const cc::ByteArrayView &mem):
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
            throw cb::Error("Texture File not found");
        }

        std::optional<ImageContainer> imageContainer = imageParse(data.value());
        if (!imageContainer.has_value()){
            throw cb::Error(std::string("Texture File format not supported : ") + std::string(filePath));
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
            throw cb::Error("Invalid Texture");
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
                           const cc::ByteArrayView &mem)
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
            throw cb::Error("Error when loading a texture");
        }
    }

    bgfx::TextureHandle BgfxTexture::getHandle() const {
        return m_handle;
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
        if(file.extension() != ".dds" &&
            file.extension() != ".png" &&
            file.extension() != ".jpg" ){
            return;
        }

        std::cout<<"load texture : "<<file.stem()<<"\n";

        std::shared_ptr<BgfxTexture> texture( new BgfxTexture(file.string()));

        m_textures.push_back(Texture{file, texture});

    }

    std::shared_ptr<cp::Texture> BgfxTextureFactory::loadTextureFromFile(std::string_view filename) {
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
    BgfxShader::BgfxShader(const cc::ByteArrayView& data) {
        const bgfx::Memory* bgfxMem = createBgfxMemory(data);
        m_handle = bgfx::createShader(bgfxMem);

        if(!bgfx::isValid(m_handle)){
            throw cb::Error("Error when loading a shader");
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
            throw cb::Error("Error when loading a shader program");
        }
    }

    BgfxProgram::~BgfxProgram() {
        if(bgfx::isValid(m_handle)){
            bgfx::destroy(m_handle);
        }
    }

    bgfx::ProgramHandle BgfxProgram::getHandle() const {
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
    BgfxUniform::BgfxUniform(std::string_view name, cp::Uniform::Type type, int num) {
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

    void BgfxUniform::setColor(const cb::Color & color) {
        float colorTmp[4] = {static_cast<float>(color.red) / 255.f,
                             static_cast<float>(color.green) / 255.f,
                             static_cast<float>(color.blue) / 255.f,
                             static_cast<float>(color.alpha) / 255.f};
        bgfx::setUniform(m_handle, colorTmp, 1);
    }

    void BgfxUniform::setTexture(const cp::Texture& texture) {
        const auto* bgfxTexture = dynamic_cast<const BgfxTexture*>(&texture);
        bgfx::setTexture(0, m_handle, bgfxTexture->getHandle());
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<cp::Uniform> BgfxUniformFactory::createUniform(std::string_view name,
                                                                   cp::Uniform::Type type,
                                                                   int num)
    {
        return std::make_shared<BgfxUniform>(name, type, num);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    BgfxProgramFactory::BgfxProgramFactory(BgfxContext& bgfxContext):
    m_bgfxContext(bgfxContext){
        namespace fs = std::filesystem;
        for (const auto &p: fs::directory_iterator(getProgramDir())) {
            auto name = fileStemToProgramName(p.path().stem().string());
            if(name.has_value()){
                loadProgramProgram(name.value());
            }
        }
    }

    std::shared_ptr<cp::GpuProgram> BgfxProgramFactory::loadProgramFromFile(std::string_view filename) {
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
        std::string shaderType(cp::GetGraphicsApiShaderType(m_bgfxContext.getApi()));
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
        std::string filePath = "./data/shader/" + std::string(cp::GetGraphicsApiShaderType(m_bgfxContext.getApi())) + "/" + std::string(name) + ".bin";
        std::optional<cc::ByteArray> memory = cc::ByteArray::loadFromFile(filePath);
        if(!memory.has_value()){
            throw cb::Error("error while opening a shader file");
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
    void BgfxVertexLayout::begin() {
        m_layout.begin();
    }

    void BgfxVertexLayout::add(cp::Attrib attrib, uint8_t num, cp::AttribType type, bool normalized, bool asInt) {
        bgfx::Attrib::Enum bgfxAttrib = convAttrib(attrib);
        bgfx::AttribType::Enum bgfxType = convAttribType(type);
        m_layout.add(bgfxAttrib, num, bgfxType, normalized, asInt);
    }

    void BgfxVertexLayout::end() {
        m_layout.end();
    }

    const bgfx::VertexLayout &BgfxVertexLayout::getBgfxLayout() const {
        return m_layout;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<cp::IndexBuffer> bgfxGpuBufferFactory::createIndexBuffer(const cc::ByteArrayView &data) {
        return std::make_unique<BgfxIndexBuffer>(data);
    }

    std::unique_ptr<cp::VertexBuffer>
    bgfxGpuBufferFactory::createVertexBuffer(const cc::ByteArrayView& data, const cp::VertexLayout& layout) {
        const auto& bgfxLayout = dynamic_cast<const BgfxVertexLayout&>(layout);
        return std::make_unique<BgfxVertexBuffer>(data, bgfxLayout);
    }

    std::unique_ptr<cp::VertexLayout> bgfxGpuBufferFactory::createVertexLayout() {
        return std::make_unique<BgfxVertexLayout>();
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    BgfxVertexBuffer::BgfxVertexBuffer(const cc::ByteArrayView& data, const BgfxVertexLayout& layout) {
        m_handle  = bgfx::createVertexBuffer(
                createBgfxMemory(data),
                layout.getBgfxLayout()
        );
    }

    BgfxVertexBuffer::~BgfxVertexBuffer() {
        bgfx::destroy(m_handle);
    }

    bgfx::VertexBufferHandle BgfxVertexBuffer::getBgfxHandle() const {
        return m_handle;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    BgfxIndexBuffer::BgfxIndexBuffer(const cc::ByteArrayView& data) {
        m_handle = bgfx::createIndexBuffer(createBgfxMemory(data));
    }

    BgfxIndexBuffer::~BgfxIndexBuffer() {
        bgfx::destroy(m_handle);
    }

    bgfx::IndexBufferHandle BgfxIndexBuffer::getBgfxHandle() const {
        return m_handle;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    BgfxContext::BgfxContext(SdlWindowAdapter& win) {
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

    BgfxContext::~BgfxContext() {

    }

    void BgfxContext::beginFrame(cc::Vector2ui newSize) {
        if(newSize.x != m_size.x || newSize.y != m_size.y){
            std::cout<<"resize "<<newSize.x<<" "<<newSize.y<<std::endl;
            bgfx::reset(newSize.x, newSize.y);
            m_size = newSize;
        }

        bgfx::setViewRect(0, 0, 0, uint16_t(m_size.x), uint16_t(m_size.y) );
        bgfx::touch(0);

        bgfx::dbgTextClear();
    }

    void BgfxContext::endFrame() {
        bgfx::frame();
    }

    bool BgfxContext::sdlSetWindow(SdlWindowAdapter& win)
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

    cp::GraphicsApi BgfxContext::getApi() const {
        switch (bgfx::getRendererType()){
            case bgfx::RendererType::Noop:
                return cp::GraphicsApi::Noop;
            case bgfx::RendererType::Direct3D9:
                return cp::GraphicsApi::Direct3D9;
            case bgfx::RendererType::Direct3D11:
                return cp::GraphicsApi::Direct3D11;
            case bgfx::RendererType::Direct3D12:
                return cp::GraphicsApi::Direct3D12;
            case bgfx::RendererType::Gnm:
                return cp::GraphicsApi::Gnm;
            case bgfx::RendererType::Metal:
                return cp::GraphicsApi::Metal;
            case bgfx::RendererType::Nvn:
                return cp::GraphicsApi::Nvn;
            case bgfx::RendererType::OpenGL:
                return cp::GraphicsApi::OpenGL;
            case bgfx::RendererType::OpenGLES:
                return cp::GraphicsApi::OpenGLES;
            case bgfx::RendererType::Vulkan:
                return cp::GraphicsApi::Vulkan;
            case bgfx::RendererType::WebGPU:
                return cp::GraphicsApi::WebGPU;
            default:
                throw cb::Error{"Unknown Graphics Api"};
        }
    }
}

namespace cg {
    std::unique_ptr<cp::GpuAdapter> createBgfxAdapter(Impl::SdlWindowAdapter& win){
        return std::make_unique<Impl::BgfxAdapter>(win);
    }
}