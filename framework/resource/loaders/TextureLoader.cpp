#include "resource/loaders/TextureLoader.hpp"

using namespace suisho;

Resource* TextureLoader::load(const std::string& uri) {
    return nullptr;
}

bool TextureLoader::unload(Resource* res) {
    return false;
}

std::vector<std::string> TextureLoader::getSupportedExtensions() const {
    return { "png", "jpg" };
}
