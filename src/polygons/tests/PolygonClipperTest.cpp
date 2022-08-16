//
// Created by cmeerpohl on 09.10.20.
//

#include "Polygons/PolygonClipper.h"

#include <gtest/gtest.h>

namespace freespace
{

namespace polygons
{

TEST(PolygonClipperTest, EmptyPolygonList)
{
    std::vector<Polygon> input;
    const auto output = PolygonClipper::unify(input);
    ASSERT_TRUE(output.empty());
}

TEST(PolygonClipperTest, SeparatePolygons)
{
    std::vector<types::Point2D> firstExteriorPoints = {{.0, .0}, {10.0, 0.0}, {10.0, 10.0}, {.0, 10.0}};
    std::vector<types::Point2D> secondExteriorPoints = {{20.0, 20.0}, {30.0, 20.0}, {30.0, 30.0}, {20.0, 30.0}};
    Polygon firstPolygon((Ring(firstExteriorPoints)));
    Polygon secondPolygon((Ring(secondExteriorPoints)));
    std::vector<Polygon> input = {firstPolygon, secondPolygon};
    const auto output = PolygonClipper::unify(input);
    ASSERT_TRUE(std::is_permutation(input.begin(), input.end(), output.begin()));
}

TEST(PolygonClipperTest, IntersectingPolygons)
{
    std::vector<types::Point2D> firstExteriorPoints = {{.0, .0}, {7.0, 0.0}, {7.0, 7.0}, {.0, 7.0}};
    std::vector<types::Point2D> secondExteriorPoints = {{5.0, 5.0}, {10.0, 5.0}, {10.0, 10.0}, {5.0, 10.0}};
    std::vector<types::Point2D> expectedUnifiedPoints = {{0.0, 0.0},   {7.0, 0.0},  {7.0, 5.0}, {10.0, 5.0},
                                                         {10.0, 10.0}, {5.0, 10.0}, {5.0, 7.0}, {0.0, 7.0}};
    Polygon firstPolygon((Ring(firstExteriorPoints)));
    Polygon secondPolygon((Ring(secondExteriorPoints)));
    Polygon expectedUnifiedPolygon((Ring(expectedUnifiedPoints)));
    std::vector<Polygon> input = {firstPolygon, secondPolygon};
    const auto output = PolygonClipper::unify(input);
    ASSERT_EQ(output.size(), 1);
    ASSERT_EQ(expectedUnifiedPolygon,output.front());

}

TEST(PolygonClipperTest, IntersectingPolygonsWithHole)
{
    std::vector<types::Point2D> firstExteriorPoints = {{.0, .0}, {10.0, 0.0}, {10.0, 5.0}, {8.0, 5.0},
                                                       {8.0,2.0},{2.0,2.0},{2.0,5.0},{0.0,5.0}};
    std::vector<types::Point2D> secondExteriorPoints = {{0.0, 10.0}, {10.0, 10.0}, {10.0, 5.0}, {8.0, 5.0},
                                                        {8.0,8.0},{2.0,8.0},{2.0,5.0},{0.0,5.0}};
    std::vector<types::Point2D> expectedPointsExterior = {{0.0, 0.0},   {10.0, 0.0},  {10.0, 10.0}, {0.0, 10.0}};
    std::vector<types::Point2D> expectedPointsInterior = {{2.0, 2.0},   {2.0, 8.0},  {8.0, 8.0}, {8.0, 2.0}};


    Polygon firstPolygon((Ring(firstExteriorPoints)));
    Polygon secondPolygon((Ring(secondExteriorPoints)));
    Polygon expectedUnifiedPolygon((Ring(expectedPointsExterior)));
    expectedUnifiedPolygon.addInterior(Ring(expectedPointsInterior));
    std::vector<Polygon> input = {firstPolygon, secondPolygon};
    const auto output = PolygonClipper::unify(input);
    ASSERT_EQ(output.size(), 1);
    ASSERT_EQ(output.front().interiors().size(), 1);
    ASSERT_EQ(output.front(), expectedUnifiedPolygon);

}

}
}