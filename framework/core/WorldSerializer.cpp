#include "core/WorldSerializer.h"
#include "core/Transform.h"
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

using namespace suisho;

WorldSerializer::WorldSerializer(World& target)
: target_(target) {}

void WorldSerializer::serialize(std::ostream& dst) const {
    const auto& reg = target_.reg_;
    cereal::JSONOutputArchive archive(dst);

    std::stack<entt::entity> entities;
    for (auto e : reg.view<entt::entity>()) {
        entities.push(e);
    }

    archive.setNextName("entities");
    archive.startNode();
    archive.makeArray();
    while (!entities.empty()) {
        // Serialize the entity
        entt::entity e = entities.top();
        archive.startNode();
        // Serialize the components attached to the e
        for (auto&& [id, pool] : reg.storage()) {
            if (pool.contains(e)) {
                auto& savers = getSavers();
                if (savers.count(id) == 0) {
                    std::stringstream ss;
                    ss << "WorldSerializer: " << pool.type().name() << " is not registered." << std::endl;
                    throw std::runtime_error(ss.str());
                }

                getSavers().at(id)(archive, pool.value(e));
            }
        }
        archive.finishNode();
        entities.pop();
    }
    archive.finishNode(); // End "entities" section
}

void WorldSerializer::deserialize(std::istream& src) {
    cereal::JSONInputArchive archive(src);
    archive.startNode(); // Begin "entities" section
    while (true) {
        // Begin entity section
        try {
            archive.startNode();
        } catch (const cereal::Exception& e) {
            // If no array element found, break
            break;
        }

        Entity e = target_.createEntity();
        while (archive.getNodeName() != nullptr) {
            getLoaders().at(archive.getNodeName())(archive, target_, e);
        }
        archive.finishNode(); // End entity section
    }
    archive.finishNode(); // End "entities" section
}
