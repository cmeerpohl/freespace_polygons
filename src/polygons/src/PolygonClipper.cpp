//
// Created by cmeerpohl on 08.10.20.
//

#include "PolygonClipper.h"

namespace freespace
{

namespace polygons
{

std::vector<Polygon> PolygonClipper::unify(const std::vector<Polygon> &inputPolygons)
{
    auto clipper = getClipper(inputPolygons);
    // clipper.StrictlySimple(true);
    ClipperLib::Paths paths;
    clipper.Execute(ClipperLib::ctUnion, paths, ClipperLib::pftNonZero, ClipperLib::pftNonZero);
    // const double dist = 0.05 * CLIPPER_FACTOR;
    // ClipperLib::CleanPolygons(paths, dist);
    return clipperPathsToPolygons(paths);
}

ClipperLib::Clipper PolygonClipper::getClipper(const std::vector<Polygon> &polygons)
{
    ClipperLib::Clipper clipper;
    constexpr bool pathIsClosed = true;
    for (const auto & polygon : polygons)
    {
        if (!clipper.AddPath(ClipperLib::Path(polygon.exterior()), ClipperLib::ptSubject, pathIsClosed))
        {
            // l_wrn("Cannot add exterior of polygon " << idx << " to Clipper paths.");
        }
        const auto &holes = polygon.interiors();
        for (const auto & hole : holes)
        {
            if (!clipper.AddPath(ClipperLib::Path(hole), ClipperLib::ptSubject, pathIsClosed))
            {
                // l_wrn("Cannot add interior " << intIdx << " of polygon " << idx << " to Clipper paths.");
            }
        }
    }
    return clipper;
}

std::vector<Polygon> PolygonClipper::clipperPathsToPolygons(const ClipperLib::Paths &paths)
{
    std::vector<Polygon> polygonOut;

    for (const auto &path : paths)
    {
        // From manual: For closed paths (polygons) in the solution returned by Clipper's Execute method,
        // their orientations will always be true for outer polygons and false for hole polygons.
        const bool orientation = ClipperLib::Orientation(path);

        if (orientation /* == true*/)
        {
            Polygon poly{Ring(path)};

            for (const auto &hole : paths)
            {
                if (ClipperLib::Orientation(hole) != orientation)
                {
                    if (!hole.empty())
                    {
                        const ClipperLib::IntPoint p(hole.front().X, hole.front().Y);
                        if (ClipperLib::PointInPolygon(p, path))
                        {
                            poly.addInterior(Ring(hole));
                        }
                    }
                }
            }
            polygonOut.push_back(std::move(poly));
        }
    }
    return polygonOut;
}

}
}