#ifndef SUISHO_CORE_WORLD_SERIALIZER_H_
#define SUISHO_CORE_WORLD_SERIALIZER_H_

#include "core/World.h"
#include <cereal/archives/json.hpp>
#include <iostream>
#include <functional>

namespace suisho {

class WorldSerializer {
public:
    WorldSerializer(World& world);

    template <class T>
    static bool registerComponent(const std::string& name) {
        const bool is_created = (getSavers().count(entt::type_id<T>().hash()) == 0);

        ComponentSerializer cs;
        cs.save = [name](cereal::JSONOutputArchive& archive, const void* data) { archive(cereal::make_nvp(name, *reinterpret_cast<const T*>(data))); };

        getSavers()[entt::type_id<T>().hash()] = cs;
        return is_created;
    }

    void serialize(std::ostream& dst) const;
    void deserialize(std::istream& src);

private:
    World& target_;

    struct ComponentSerializer {
        std::function<void(cereal::JSONOutputArchive& archive, const void* data)> save;
    };

    static std::unordered_map<entt::id_type, ComponentSerializer>& getSavers() {
        static auto savers = new std::unordered_map<entt::id_type, ComponentSerializer>();
        return *savers;
    }
};

} // namespace suisho

#endif
