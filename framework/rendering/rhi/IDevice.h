#ifndef SUISHO_RENDERING_IDEVICE_H_
#define SUISHO_RENDERING_IDEVICE_H_

#include "rendering/rhi/ICommandBuffer.h"

namespace suisho::rhi {

struct IDevice {
    virtual ~IDevice() {};

    virtual bool allocateCommandBuffer(ICommandBuffer& out) = 0;
    virtual void freeCommandBuffer(ICommandBuffer& cb) = 0;
    virtual bool submit(ICommandBuffer& cb) = 0;
};

} // namespace suisho::rhi

#endif // SUISHO_RENDERING_DEVICE_H_
