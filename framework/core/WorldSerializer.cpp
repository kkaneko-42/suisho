#include "core/WorldSerializer.h"
#include <fstream>
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

using namespace suisho;

WorldSerializer::WorldSerializer(World& target)
: target_(target) {}

void WorldSerializer::serialize(const std::string& dst_path) const {
    // Open the file
    std::ofstream ofs(dst_path);
    if (!ofs) {
        throw std::runtime_error("WorldSerializer: Failed to open " + dst_path);
    }

    cereal::JSONOutputArchive archive(ofs);
    const auto& reg = target_.reg_;
    // Collect entities
    // NOTE: Reverse ordering required
    std::stack<entt::entity> entities;
    for (auto e : reg.view<entt::entity>()) {
        entities.push(e);
    }

    // Serialize entities
    archive.setNextName("entities");
    archive.startNode();
    archive.makeArray();
    while (!entities.empty()) {
        // Serialize the entity
        entt::entity e = entities.top();
        archive.startNode(); // Begin entity section
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
        archive.finishNode(); // End entity section
        entities.pop();
    }
    archive.finishNode(); // End "entities" section
}

void WorldSerializer::deserialize(const std::string& src_path) {
    // Open the file
    std::ifstream ifs(src_path);
    if (!ifs) {
        throw std::runtime_error("WorldSerializer: Failed to open " + src_path);
    }

    target_.clear();
    cereal::JSONInputArchive archive(ifs);
    archive.startNode(); // Begin "entities" section
    while (true) {
        // Begin entity section
        try {
            archive.startNode();
        } catch (const cereal::Exception& e) {
            // If no array element found, break
            break;
        }

        // Deserialize the components attached
        Entity e = target_.createEntity();
        while (archive.getNodeName() != nullptr) {
            getLoaders().at(archive.getNodeName())(archive, target_, e);
        }
        archive.finishNode(); // End entity section
    }
    archive.finishNode(); // End "entities" section
}
