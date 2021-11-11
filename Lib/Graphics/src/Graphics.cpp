//
// Created by jngl on 10/07/2021.
//

#include "Graphics/Graphics.h"

#include "private_Graphics.h"

namespace cg{
    [[maybe_unused]] std::unique_ptr<cp::GraphicsAdapter> createGraphicsAdapter()
    {
        return std::make_unique<Impl::GraphicsAdapter>();
    }
}
