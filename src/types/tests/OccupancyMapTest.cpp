//
// Created by cmeerpohl on 09.10.20.
//

#include "Types/OccupancyMap.h"

#include <gtest/gtest.h>

namespace k2i
{
namespace o2c
{
namespace coll
{

TEST(OccupancyMapTest, EmptyMap)
{
    OccupancyMap2D map;
    ASSERT_EQ(map.height(),0);
    ASSERT_EQ(map.width(),0);
    ASSERT_DOUBLE_EQ(map.resolution(),.0);
    ASSERT_TRUE(types::areSame(map.origin(), types::PoseSE2{}));
    ASSERT_TRUE(map.values().empty());
}

} // namespace coll
} // namespace o2c
} // namespace k2i