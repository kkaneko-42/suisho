#ifndef SUISHO_RENDERING_BACKEND_VULKAN_DEVICE_H_
#define SUISHO_RENDERING_BACKEND_VULKAN_DEVICE_H_

#include "rendering/rhi/IDevice.h"

namespace suisho::backend {

struct VulkanDeviceImpl;

class VulkanDevice : public suisho::rhi::IDevice {
public:
    VulkanDevice();
    ~VulkanDevice();

    VulkanDevice(const VulkanDevice&) = delete;
    VulkanDevice& operator=(const VulkanDevice&) = delete;

    bool allocateCommandBuffer(rhi::ICommandBuffer& out) override;
    void freeCommandBuffer(rhi::ICommandBuffer& buf) override;
    bool submit(rhi::ICommandBuffer& cb) override;

private:
    VulkanDeviceImpl* impl_;
};

} // namespace suisho::backend

#endif // SUISHO_RENDERING_BACKEND_VULKAN_DEVICE_H_
