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
        const bool is_created = (getLoaders().count(name) == 0);

        getSavers()[entt::type_id<T>().hash()] = [name](cereal::JSONOutputArchive& archive, const void* src) { archive(cereal::make_nvp(name, *reinterpret_cast<const T*>(src))); };
        getLoaders()[name] = [name](cereal::JSONInputArchive& archive, World& dst, Entity e) {
            T data;
            archive(cereal::make_nvp(name, data));
            dst.addComponent<T>(e, data);
            std::cout << "loaded: " << data.position.x << std::endl;
        };

        return is_created;
    }

    void serialize(std::ostream& dst) const;
    void deserialize(std::istream& src);

private:
    World& target_;

    static std::unordered_map<entt::id_type, std::function<void(cereal::JSONOutputArchive&, const void*)>>& getSavers() {
        static auto savers = new std::unordered_map<entt::id_type, std::function<void(cereal::JSONOutputArchive&, const void* data)>>();
        return *savers;
    }

    static std::unordered_map<std::string, std::function<void(cereal::JSONInputArchive&, World&, Entity)>>& getLoaders() {
        static auto loaders = new std::unordered_map<std::string, std::function<void(cereal::JSONInputArchive&, World&, Entity)>>();
        return *loaders;
    }
};

} // namespace suisho

#endif
