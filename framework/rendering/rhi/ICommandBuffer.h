#ifndef SUISHO_RENDERING_RHI_ICOMMAND_BUFFER_H_
#define SUISHO_RENDERING_RHI_ICOMMAND_BUFFER_H_

#include <cstdint>

namespace suisho::rhi {

struct ICommandBuffer {
    virtual ~ICommandBuffer() {}
    virtual bool beginRecording() = 0;
    virtual void draw(uint32_t vertex_count) = 0;
    virtual bool endRecording() = 0;
};

} // namespace suisho::rhi

#endif
