#ifndef SUISHO_RESOURCE_TEXTURE_LOADER_H_
#define SUISHO_RESOURCE_TEXTURE_LOADER_H_

#include "resource/IResourceLoader.hpp"

namespace suisho {

class TextureLoader : public IResourceLoader {
public:
    Resource* load(const std::string& uri) override;
    bool unload(Resource* res) override;
    std::vector<std::string> getSupportedExtensions() const override;
};

}

#endif
