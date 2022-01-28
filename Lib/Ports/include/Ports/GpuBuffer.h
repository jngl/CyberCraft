//
// Created by jngl on 06/11/2021.
//

#ifndef CYBERCRAFT_GPUBUFFER_H
#define CYBERCRAFT_GPUBUFFER_H

#include <CyberBase/Bases.h>

namespace cc
{
    class ByteArrayView;
}

namespace cp
{
    /// Corresponds to vertex shader attribute.
    enum class Attrib
    {
        Position,  //!< a_position
        Normal,    //!< a_normal
        Tangent,   //!< a_tangent
        Bitangent, //!< a_bitangent
        Color0,    //!< a_color0
        Color1,    //!< a_color1
        Color2,    //!< a_color2
        Color3,    //!< a_color3
        Indices,   //!< a_indices
        Weight,    //!< a_weight
        TexCoord0, //!< a_texcoord0
        TexCoord1, //!< a_texcoord1
        TexCoord2, //!< a_texcoord2
        TexCoord3, //!< a_texcoord3
        TexCoord4, //!< a_texcoord4
        TexCoord5, //!< a_texcoord5
        TexCoord6, //!< a_texcoord6
        TexCoord7, //!< a_texcoord7

        Count
    };

    /// Vertex attribute type enum.
    enum class AttribType
    {
        Uint8,  //!< Uint8
        Uint10, //!< Uint10, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_UINT10`.
        Int16,  //!< Int16
        Half,   //!< Half, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_HALF`.
        Float,  //!< Float

        Count
    };

    class IndexBuffer : public cc::NonCopyable
    {
    public:
    };

    class VertexBuffer : public cc::NonCopyable{
    public:
    };

    class VertexLayout : public cc::Copyable{
    public:
        virtual void begin() = 0;
        virtual void add(Attrib attrib, uint8_t num, AttribType type, bool normalized = false, bool asInt = false) = 0;
        virtual void end() = 0;
    };

    class GpuBufferFactory : public cc::NonCopyable{
    public:
        virtual std::unique_ptr<IndexBuffer> createIndexBuffer(const cc::ByteArrayView&) = 0;
        virtual std::unique_ptr<VertexBuffer> createVertexBuffer(const cc::ByteArrayView& data, const VertexLayout& layout) = 0;
        virtual std::unique_ptr<VertexLayout> createVertexLayout() = 0;
    };
}

#endif //CYBERCRAFT_GPUBUFFER_H
