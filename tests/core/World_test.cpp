#include <gtest/gtest.h>
#include "core/World.h"

using namespace suisho;

/// @todo Well test for World
TEST(WorldTest, EasyTest) {
    World world;
    auto e = world.createEntity();
    auto e_invalid = world.createEntity();
    EXPECT_NO_THROW(world.destroyEntity(e_invalid));

    EXPECT_THROW(world.destroyEntity(e_invalid), std::invalid_argument);
    EXPECT_THROW(world.addComponent<int>(e_invalid), std::invalid_argument);
    EXPECT_THROW(world.removeComponent<int>(e_invalid), std::invalid_argument);
    EXPECT_THROW(world.hasComponent<int>(e_invalid), std::invalid_argument);
    EXPECT_THROW(world.getComponent<int>(e_invalid), std::invalid_argument);

    EXPECT_FALSE(world.hasComponent<int>(e));
    EXPECT_EQ(42, world.addComponent<int>(e, 42));
    EXPECT_TRUE(world.hasComponent<int>(e));
    ASSERT_NE(nullptr, world.getComponent<int>(e));
    EXPECT_EQ(42, *world.getComponent<int>(e));
    EXPECT_EQ(0, world.addComponent<int>(e));
    EXPECT_EQ(0, *world.getComponent<int>(e));
    EXPECT_EQ(1, world.removeComponent<int>(e));
    EXPECT_EQ(nullptr, world.getComponent<int>(e));
    EXPECT_EQ(0, world.removeComponent<int>(e));
    EXPECT_FALSE(world.hasComponent<int>(e));
}
