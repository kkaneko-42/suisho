#include "resource/ResourceManager.hpp"
#include <stdexcept>

using namespace suisho;

const std::string ResourceManager::kLocalScheme = "res://";
std::string ResourceManager::res_dir_ = "./resources/";
std::vector<std::shared_ptr<IResourceLoader>> ResourceManager::loaders_;

std::shared_ptr<Resource> ResourceManager::load(const std::string& uri) {
    auto loader_itr = std::find_if(
        loaders_.begin(), loaders_.end(),
        [&uri](const std::shared_ptr<IResourceLoader>& loader) {
            return loader->isSupported(uri);
        }
    );

    if (loader_itr == loaders_.end()) {
        throw std::runtime_error("ResourceManager::load(): " + uri + " loader not found");
    }

    return std::shared_ptr<Resource>((*loader_itr)->load(uri), [loader = *loader_itr](Resource* res) { loader->unload(res); });
}

bool ResourceManager::addLoader(std::shared_ptr<IResourceLoader> loader) {
    if (std::find(loaders_.begin(), loaders_.end(), loader) != loaders_.end()) {
        return false;
    }

    loaders_.push_back(loader);
    return true;
}

void ResourceManager::setResourceDirectory(const std::string& path) {
    res_dir_ = path;
}
