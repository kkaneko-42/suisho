#ifndef SUISHO_RENDERING_RENDERABLE_H_
#define SUISHO_RENDERING_RENDERABLE_H_

#include "rendering/Material.hpp"
#include <memory>

namespace suisho {

struct Renderable {
    Renderable(std::shared_ptr<Material> mat = nullptr) : material(mat) {}
    std::shared_ptr<Material> material;
};

}

#endif
