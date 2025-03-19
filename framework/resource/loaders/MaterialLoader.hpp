#ifndef SUISHO_RESOURCE_MATERIAL_LOADER_H_
#define SUISHO_RESOURCE_MATERIAL_LOADER_H_

#include "resource/IResourceLoader.hpp"
#include "rendering/backend/vulkan/VulkanDevice.hpp" // FIXME
#include <memory>

namespace suisho {

class MaterialLoader : public IResourceLoader {
public:
    MaterialLoader(std::shared_ptr<backend::VulkanDevice> device);
    Resource* load(const std::string& uri) override;
    bool unload(Resource* res) override;
    std::vector<std::string> getSupportedExtensions() const override;

private:
    std::shared_ptr<backend::VulkanDevice> device_;
};

}

#endif
