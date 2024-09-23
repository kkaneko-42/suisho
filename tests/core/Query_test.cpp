#include <gtest/gtest.h>
#include "core/Query.h"

using namespace suisho;

/// @todo Well test for Query
TEST(QueryTest, EasyTest) {
    World world;
    Query<std::tuple<const int, const std::string>> query(world);
    query.forEach([](const int&, const std::string&) {});

    Query<std::tuple<int, std::string>> query_mut(world);
    query_mut.forEach([](int&, std::string&) {  });
}
