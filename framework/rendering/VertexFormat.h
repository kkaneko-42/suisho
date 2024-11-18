#ifndef SUISHO_RENDERING_VERTEX_FORMAT_H_
#define SUISHO_RENDERING_VERTEX_FORMAT_H_

#include <cstdint>

namespace suisho {
    enum class VertexFormat : uint32_t {
        kNone       = 0,
        kPosition   = 1 << 0,
        kNormal     = 1 << 1,
        kTexCoord2D = 1 << 2,
    };

    constexpr VertexFormat operator |(VertexFormat a, VertexFormat b) {
        return static_cast<VertexFormat>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
    }

    constexpr VertexFormat operator &(VertexFormat a, VertexFormat b) {
        return static_cast<VertexFormat>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
    }
}

#endif // SUISHO_RENDERING_VERTEX_FORMAT_H_
