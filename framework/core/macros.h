#ifndef SUISHO_CORE_MACROS_H_
#define SUISHO_CORE_MACROS_H_

#include "core/internal/foreach_macro.h"
#include "core/WorldSerializer.h" // FIXME: Dependency

#define SUISHO_SERIALIZE_IMPL(prop)\
    archive(cereal::make_nvp(#prop, data.prop));

#define SUISHO_SERIALIZE(type, ...)\
    template <class Archive>\
    void serialize(Archive& archive, type& data) {\
        SUISHO_FOREACH_VA_ARGS(SUISHO_SERIALIZE_IMPL, __VA_ARGS__);\
    }\

#define SUISHO_COMPONENT(type, ...)\
    SUISHO_SERIALIZE(type, __VA_ARGS__);\
    namespace suisho_detail::type##Info {\
        struct WorldSerializerRegistration {\
            WorldSerializerRegistration() {\
                WorldSerializer::registerComponent<type>(#type);\
            }\
        };\
\
        inline WorldSerializerRegistration g_type##_registerer;\
    }

#endif
