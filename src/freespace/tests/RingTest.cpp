//
// Created by cmeerpohl on 08.10.20.
//

#include "../src/Ring.h"

#include <gtest/gtest.h>

namespace k2i
{
namespace o2c
{
namespace coll
{

TEST(RingTest, NonEmptyRing)
{
    std::vector<types::Point2D> exteriorPoints = {{.0, .0}, {1.0, 0.0}, {1.0,1.0},{.0,1.0}};
    Ring ring(exteriorPoints);
    ASSERT_TRUE(ring.values().size() == exteriorPoints.size());
}

TEST(RingTest, Equality)
{
    std::vector<types::Point2D> firstExteriorPoints = {{.0, .0}, {1.0, 0.0}, {1.0,1.0},{.0,1.0}};
    std::vector<types::Point2D> secondExteriorPoints = {{1.0, 0.0}, {1.0,1.0},{.0,1.0},{.0, .0}};
    std::vector<types::Point2D> thirdExteriorPoints = {{.0,1.0}, {1.0,1.0}, {1.0, 0.0},{.0, .0}};
    std::vector<types::Point2D> fourthExteriorPoints = {{.0, .0}, {1.0, 0.0}, {1.0,1.0},{0.0,2.0}};
    Ring firstRing(firstExteriorPoints);
    Ring secondRing(secondExteriorPoints);
    Ring thirdRing(thirdExteriorPoints);
    Ring fourthRing(fourthExteriorPoints);
    ASSERT_EQ(firstRing,secondRing);
    ASSERT_EQ(firstRing,thirdRing);
    ASSERT_NE(firstRing,fourthRing);
}

} // namespace coll
} // namespace o2c
} // namespace k2i