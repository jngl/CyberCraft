//
// Created by jngl on 11/07/2021.
//

#ifndef CYBERCRAFT_BGFXADAPTER_H
#define CYBERCRAFT_BGFXADAPTER_H

#include <Kernel/GpuAdapter.h>

#include <memory>

namespace cg::Impl {
    class SdlWindowAdapter;
}

namespace cg {
    std::unique_ptr<ck::GpuAdapter> createBgfxAdapter(Impl::SdlWindowAdapter& win);
}

#endif //CYBERCRAFT_BGFXADAPTER_H
