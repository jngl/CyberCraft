//
// Created by jngl on 15/04/2021.
//

#ifndef CYBERCRAFT_TEXTURE_H
#define CYBERCRAFT_TEXTURE_H

#include <Core/Id.h>
#include <Core/Bases.h>

namespace cc
{
    using TextureHandle = Id<unsigned int, struct TextureHandleTag>;

    class TextureManager : public NonCopyable{
    public:
        [[nodiscard]] virtual TextureHandle getHandleFromFile(std::string_view filename) = 0;
        virtual void loadTexture(TextureHandle) = 0;
        virtual void unloadTexture(TextureHandle) = 0;
    };
}

#endif //CYBERCRAFT_TEXTURE_H
