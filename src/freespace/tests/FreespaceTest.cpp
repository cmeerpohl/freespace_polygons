//
// Created by cmeerpohl on 09.10.20.
//

#include "../src/Freespace.h"

#include <gtest/gtest.h>

namespace k2i
{
namespace o2c
{
namespace coll
{

TEST(FreespaceTest, ExteriorRingOnly)
{
    std::vector<types::Point2D> exteriorPoints = {{.0, .0}, {1.0, 0.0}, {1.0,1.0},{.0,1.0}};
    Polygon poly{Ring(exteriorPoints)};
    Freespace area({ poly } );
    ASSERT_FALSE(area.getPolygons().empty());
    ASSERT_TRUE(area.getPolygons().size() == 1);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({.0,.0}), .0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({.5,.5}), 0.25);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({.25,.5}), 0.0625);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({0.5,1.5}), -0.25);
}

TEST(FreespaceTest, ExteriorWithHoles)
{
    std::vector<types::Point2D> exteriorPoints = {{.0, .0}, {10.0, 0.0}, {10.0,10.0},{.0,10.0}};
    std::vector<types::Point2D> firstInteriorPoints = {{1.0, 1.0}, {5.0, 1.0}, {5.0,5.0},{1.0,5.0}};
    std::vector<types::Point2D> secondInteriorPoints = {{6.0, 6.0}, {9.0, 6.0}, {9.0,9.0},{6.0,9.0}};
    Polygon poly{Ring(exteriorPoints)};
    poly.addInterior(Ring(firstInteriorPoints));
    poly.addInterior(Ring(secondInteriorPoints));
    Freespace area( { poly } );
    ASSERT_FALSE(area.getPolygons().empty());
    ASSERT_TRUE(area.getPolygons().size() == 1);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({.0,.0}), .0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceToPoint({.0,.0}), .0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({-1.0, -1.0}), -2.0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceToPoint({-1.0, -1.0}), -std::sqrt(2.0));
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({3.0,3.0}), -4.0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceToPoint({3.0,3.0}), -std::sqrt(4.0));
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({7.0,7.0}), -1.0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceToPoint({7.0,7.0}), -1.0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({5.5,5.5}), 0.5);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceToPoint({5.5,5.5}), std::sqrt(0.5));
}

TEST(FreespaceTest, SquaredOrNonSquaredDistance)
{
    std::vector<types::Point2D> exteriorPoints = {{.0, .0}, {10.0, 0.0}, {10.0,10.0},{.0,10.0}};
    std::vector<types::Point2D> firstInteriorPoints = {{1.0, 1.0}, {5.0, 1.0}, {5.0,5.0},{1.0,5.0}};
    std::vector<types::Point2D> secondInteriorPoints = {{6.0, 6.0}, {9.0, 6.0}, {9.0,9.0},{6.0,9.0}};
    Polygon poly{Ring(exteriorPoints)};
    poly.addInterior(Ring(firstInteriorPoints));
    poly.addInterior(Ring(secondInteriorPoints));
    Freespace area( { poly } );
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({.0,.0}), .0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceToPoint({.0,.0}), .0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({-1.0, -1.0}), -2.0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceToPoint({-1.0, -1.0}), -std::sqrt(2.0));
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({3.0,3.0}), -4.0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceToPoint({3.0,3.0}), -std::sqrt(4.0));
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({7.0,7.0}), -1.0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceToPoint({7.0,7.0}), -1.0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({5.5,5.5}), 0.5);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceToPoint({5.5,5.5}), std::sqrt(0.5));
}

TEST(FreespaceTest, MultiplePolygons)
{
    std::vector<types::Point2D> firstExteriorPoints = {{.0, .0}, {10.0, 0.0}, {10.0,10.0},{.0,10.0}};
    std::vector<types::Point2D> secondExteriorPoints = {{20.0, 20.0}, {30.0, 20.0}, {30.0,30.0},{20.0,30.0}};
    Polygon firstPolygon((Ring(firstExteriorPoints)));
    Polygon secondPolygon((Ring(secondExteriorPoints)));
    Freespace area( { firstPolygon, secondPolygon } );
    ASSERT_FALSE(area.getPolygons().empty());
    ASSERT_TRUE(area.getPolygons().size() == 2);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({.0,.0}), .0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({5.0,5.0}), 25.0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({20.0,20.0}), .0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({25.0,25.0}), 25.0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({15.0,15.0}), -50.0);
    ASSERT_DOUBLE_EQ(area.computeSignedDistanceSquaredToPoint({15.0,20.0}), -25.0);
}



} // namespace coll
} // namespace o2c
} // namespace k2i