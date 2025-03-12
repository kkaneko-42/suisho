#include "resource/ResourceManager.hpp"

using namespace suisho;

const std::string ResourceManager::kLocalScheme = "res://";
std::string ResourceManager::res_dir_ = "./resources/";
std::vector<std::shared_ptr<IResourceLoader>> ResourceManager::loaders_;

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
