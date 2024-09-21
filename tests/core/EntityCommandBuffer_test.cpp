#include <gtest/gtest.h>
#include "core/EntityCommandBuffer.h"

using namespace suisho;

int g_int_value = 0;
size_t g_count = 0;
std::vector<Entity> g_entities;

static void tester(const int& i, const std::string& s) {
    g_int_value += i;
    g_count += 1;
}

static void gatherEntities(Entity e) {
    g_entities.push_back(e);
}

/// @todo Well test for EntityCommandBuffer
TEST(EntityCommandBufferTest, EasyTest) {
    EntityCommandBuffer buf;
    buf.createEntity(42, std::string("42"));
    buf.createEntity(24, std::string("24"));
    buf.createEntity();

    World world;
    buf.submit(world);
    world.forEachComponent(tester);
    EXPECT_EQ(66, g_int_value);
    EXPECT_EQ(2, g_count);

    world.forEachEntity<int, std::string>(gatherEntities);
    for (const auto& e : g_entities) {
        buf.removeComponent<int>(e);
        buf.destroyEntity(e);
    }

    g_int_value = g_count = 0;
    world.forEachComponent(tester);
    EXPECT_EQ(66, g_int_value);
    EXPECT_EQ(2, g_count);

    buf.submit(world);
    g_int_value = g_count = 0;
    world.forEachComponent(tester);
    EXPECT_EQ(0, g_int_value);
    EXPECT_EQ(0, g_count);
}
