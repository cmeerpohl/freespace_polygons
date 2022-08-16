//
// Created by cmeerpohl on 08.10.20.
//

#ifndef SRC_POLYGONCLIPPER_H
#define SRC_POLYGONCLIPPER_H

#include "Polygon.h"
#include <vector>

namespace freespace
{

namespace polygons
{

class PolygonClipper
{
  public:
    static std::vector<Polygon> unify(const std::vector<Polygon> &inputPolygons);

  private:
    static ClipperLib::Clipper getClipper(const std::vector<Polygon> &polygons);
    static std::vector<Polygon> clipperPathsToPolygons(const ClipperLib::Paths &paths);
};

}
}

#endif // SRC_POLYGONCLIPPER_H
