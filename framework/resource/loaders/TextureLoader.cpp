#include "resource/loaders/TextureLoader.hpp"
#include "rendering/backend/vulkan/VulkanDevice.hpp"
#include "rendering/backend/vulkan/VulkanTexture.hpp"
#include "resource/loaders/stb_image.h"
#include <stdexcept>

using namespace suisho;

TextureLoader::TextureLoader(std::shared_ptr<backend::VulkanDevice> device) : device_(device)
{}

Resource* TextureLoader::load(const std::string& uri) {
    int width, height, channels;
    stbi_uc* pixels = stbi_load(uri.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    if (pixels == nullptr) {
        throw std::runtime_error("TextureLoader::load(): failed to load " + uri);
    }

    backend::VulkanTexture* texture = new backend::VulkanTexture(device_->createTexture(static_cast<uint32_t>(width), static_cast<uint32_t>(height), pixels, VK_FORMAT_R8G8B8A8_SRGB));
    stbi_image_free(pixels);
    return texture;
}

bool TextureLoader::unload(Resource* res) {
    device_->destroyTexture(*static_cast<backend::VulkanTexture*>(res));
    delete res;
    return true;
}

std::vector<std::string> TextureLoader::getSupportedExtensions() const {
    return { "png", "jpg" };
}
