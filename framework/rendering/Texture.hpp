#ifndef SUISHO_RENDERING_TEXTURE_H_
#define SUISHO_RENDERING_TEXTURE_H_

#include "resource/Resource.hpp"

namespace suisho {

class Texture : public Resource {
public:
    uint32_t getWidth() const { return width_; }
    uint32_t getHeight() const { return height_; }
    virtual const void* getNativeHandle() const = 0;

protected:
    uint32_t width_;
    uint32_t height_;
};

}

#endif
