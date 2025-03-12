#ifndef SUISHO_RESOURCE_RESOURCE_MANAGER_H_
#define SUISHO_RESOURCE_RESOURCE_MANAGER_H_

#include "resource/Resource.hpp"
#include "resource/IResourceLoader.hpp"
#include <memory>
#include <vector>
#include <algorithm>

namespace suisho {

class ResourceManager {
public:
    static const std::string kLocalScheme;

    template <class T>
    static std::shared_ptr<T> load(const std::string& uri) {
        static_assert(std::is_base_of_v<Resource, T>, "T must be derived from Resource");

        auto loader = std::find_if(
            loaders_.begin(), loaders_.end(),
            [&uri](const std::shared_ptr<IResourceLoader>& loader) {
                return loader->isSupported(uri);
            }
        );

        if (loader == loaders_.end()) {
            throw std::runtime_error("ResourceManager::load(): " + uri + " loader not found");
        }

        auto loaded = std::shared_ptr<Resource>(loader->load(uri), [loader](Resource* res) { loader->unload(res); });
        return std::static_pointer_cast<T>(loaded);
    }

    static bool addLoader(std::shared_ptr<IResourceLoader> loader);
    static void setResourceDirectory(const std::string& path);

private:
    static std::string res_dir_;
    static std::vector<std::shared_ptr<IResourceLoader>> loaders_;
};

}

#endif
