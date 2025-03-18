#ifndef SUISHO_RESOURCE_TEXTURE_LOADER_H_
#define SUISHO_RESOURCE_TEXTURE_LOADER_H_

#include "resource/IResourceLoader.hpp"
#include "rendering/Texture.hpp"
#include "rendering/backend/vulkan/VulkanDevice.hpp" // FIXME
#include <memory>

namespace suisho {

class TextureLoader : public IResourceLoader {
public:
    TextureLoader(std::shared_ptr<backend::VulkanDevice> device); // FIXME: Rendering device abstraction
    Resource* load(const std::string& uri) override;
    bool unload(Resource* res) override;
    std::vector<std::string> getSupportedExtensions() const override;

private:
    std::shared_ptr<backend::VulkanDevice> device_;
};

}

#endif
