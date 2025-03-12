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

    static std::shared_ptr<Resource> load(const std::string& uri);
    static bool addLoader(std::shared_ptr<IResourceLoader> loader);
    static void setResourceDirectory(const std::string& path);

private:
    static std::string res_dir_;
    static std::vector<std::shared_ptr<IResourceLoader>> loaders_;
};

}

#endif
