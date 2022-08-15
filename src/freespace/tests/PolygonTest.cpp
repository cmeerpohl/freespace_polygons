//
// Created by cmeerpohl on 09.10.20.
//

#include "../src/Polygon.h"

#include <gtest/gtest.h>

namespace k2i
{
namespace o2c
{
namespace coll
{

TEST(PolygonTest, ExteriorRingOnly)
{
    std::vector<types::Point2D> exteriorPoints = {{.0, .0}, {1.0, 0.0}, {1.0,1.0},{.0,1.0}};
    Polygon poly{Ring(exteriorPoints)};
    ASSERT_FALSE(poly.isEmpty());
    ASSERT_TRUE(poly.interiors().size() == 0);
}

TEST(PolygonTest, ExteriorWithHoles)
{
    std::vector<types::Point2D> exteriorPoints = {{.0, .0}, {10.0, 0.0}, {10.0,10.0},{.0,10.0}};
    std::vector<types::Point2D> firstInteriorPoints = {{1.0, 1.0}, {5.0, 1.0}, {5.0,5.0},{1.0,5.0}};
    std::vector<types::Point2D> secondInteriorPoints = {{6.0, 6.0}, {9.0, 6.0}, {9.0,9.0},{6.0,9.0}};
    Polygon poly{Ring(exteriorPoints)};
    poly.addInterior(Ring(firstInteriorPoints));
    poly.addInterior(Ring(secondInteriorPoints));
    ASSERT_FALSE(poly.isEmpty());
    ASSERT_TRUE(poly.interiors().size() == 2);
}

} // namespace coll
} // namespace o2c
} // namespace k2i