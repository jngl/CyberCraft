//
// Created by jngl on 15/04/2021.
//

#ifndef CYBERCRAFT_TEXTURE_H
#define CYBERCRAFT_TEXTURE_H

#include <Core/Id.h>
#include <Core/Bases.h>

#include <memory>

namespace ck
{
    class Texture : public cc::NonCopyable
    {
    public:
    };

    class TextureFactory : public cc::NonCopyable
    {
    public:
        virtual std::shared_ptr<Texture> loadTextureFromFile(std::string_view filename) = 0;
    };
}

#endif //CYBERCRAFT_TEXTURE_H
