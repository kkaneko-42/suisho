#include "resource/loaders/MaterialLoader.hpp"

using namespace suisho;

MaterialLoader::MaterialLoader(std::shared_ptr<backend::VulkanDevice> device) : device_(device)
{}

Resource* MaterialLoader::load(const std::string& uri) {
    return nullptr;
}

bool MaterialLoader::unload(Resource* res) {
    return false;
}

std::vector<std::string> MaterialLoader::getSupportedExtensions() const {
    return { "mat" };
}
