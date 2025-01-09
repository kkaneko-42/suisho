#include "core/WorldSerializer.h"
#include "core/Transform.h"
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

using namespace suisho;

WorldSerializer::WorldSerializer(World& target)
: target_(target) {}

void WorldSerializer::serialize(std::ostream& dst) const {
    cereal::JSONOutputArchive archive(dst);
    archive.setNextName("entities");
    archive.startNode();
    archive.makeArray();
    const auto& reg = target_.reg_;
    for (auto e : reg.view<entt::entity>()) {
        // Serialize entity
        archive.startNode();
        for (auto&& [id, pool] : reg.storage()) {
            if (pool.contains(e)) {
                auto& savers = getSavers();
                if (savers.count(id) == 0) {
                    std::stringstream ss;
                    ss << "WorldSerializer: " << pool.type().name() << " is not registered." << std::endl;
                    throw std::runtime_error(ss.str());
                }

                getSavers().at(id).save(archive, pool.value(e));
            }
        }
        archive.finishNode();
    }
    archive.finishNode();
}

void WorldSerializer::deserialize(std::istream& src) {

}
