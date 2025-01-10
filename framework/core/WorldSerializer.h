#ifndef SUISHO_CORE_WORLD_SERIALIZER_H_
#define SUISHO_CORE_WORLD_SERIALIZER_H_

#include "core/World.h"
#include <cereal/archives/json.hpp>
#include <functional>

namespace suisho {

/**
 * @brief Save/Load World status
 * 
 */
class WorldSerializer {
public:
    /**
     * @brief Construct a new World Serializer object
     * 
     * @param world Serialize/Deserialized World
     */
    WorldSerializer(World& world);

    /**
     * @brief Register component type information. If it is already registered, overwrite
     * 
     * @tparam T Registered type
     * @param name Component name
     * @return If it is registered for the first time (that is, not overwritten), true
     */
    template <class T>
    static bool registerComponent(const std::string& name) {
        const bool is_created = (getLoaders().count(name) == 0);

        getSavers()[entt::type_id<T>().hash()] = [name](cereal::JSONOutputArchive& archive, const void* src) { archive(cereal::make_nvp(name, *reinterpret_cast<const T*>(src))); };
        getLoaders()[name] = [name](cereal::JSONInputArchive& archive, World& dst, Entity e) {
            T data;
            archive(cereal::make_nvp(name, data));
            dst.addComponent<T>(e, data);
        };

        return is_created;
    }

    /**
     * @brief Save the state of the World specified in constructor to the file
     * 
     * @param dst_path Path of the destination file
     */
    void serialize(const std::string& dst_path) const;

    /**
     * @brief Write the state read from the file into the World specified in the constructor
     * 
     * @param src_path Path of reading file
     */
    void deserialize(const std::string& src_path);

private:
    World& target_;

    // @see Static initialization order fiasco
    static std::unordered_map<entt::id_type, std::function<void(cereal::JSONOutputArchive&, const void*)>>& getSavers() {
        static auto savers = new std::unordered_map<entt::id_type, std::function<void(cereal::JSONOutputArchive&, const void* data)>>();
        return *savers;
    }

    // @see Static initialization order fiasco
    static std::unordered_map<std::string, std::function<void(cereal::JSONInputArchive&, World&, Entity)>>& getLoaders() {
        static auto loaders = new std::unordered_map<std::string, std::function<void(cereal::JSONInputArchive&, World&, Entity)>>();
        return *loaders;
    }
};

} // namespace suisho

#endif
