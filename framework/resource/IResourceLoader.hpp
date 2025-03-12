#ifndef SUISHO_RESOURCE_IRESOURCE_LOADER_H_
#define SUISHO_RESOURCE_IRESOURCE_LOADER_H_

#include "resource/Resource.hpp"
#include "resource/utils.hpp"
#include <vector>
#include <algorithm>

namespace suisho {

struct IResourceLoader {
    virtual ~IResourceLoader() {}

    virtual Resource* load(const std::string& uri) = 0;
    virtual bool unload(Resource* res) = 0;
    virtual std::vector<std::string> getSupportedExtensions() const = 0;

    virtual bool isSupported(const std::string& uri) const {
        const auto exts = getSupportedExtensions();
        return (std::find(exts.begin(), exts.end(), getExtension(uri)) != exts.end());
    }
};

}

#endif
