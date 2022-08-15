//
// Created by cmeerpohl on 08.10.20.
//

#ifndef SRC_POLYGONCLIPPER_H
#define SRC_POLYGONCLIPPER_H

#include "Polygon.h"
#include <vector>

namespace k2i
{
namespace o2c
{
namespace coll
{

class PolygonClipper
{
  public:
    static std::vector<Polygon> unify(const std::vector<Polygon> &inputPolygons);

  private:
    static Clipper2Lib::ClipperD getClipper(const std::vector<Polygon> &polygons);
    static std::vector<Polygon> clipperPathsToPolygons(const Clipper2Lib::PathsD &paths);
};

} // namespace coll
} // namespace o2c
} // namespace k2i

#endif // SRC_POLYGONCLIPPER_H
