
#include "Freespace.h"
#include "Geometry.h"


namespace freespace
{

namespace polygons
{

Freespace::Freespace(std::vector<Polygon> polygons) noexcept : m_polygons(std::move(polygons))
{
}

bool Freespace::operator==(const Freespace &other) const noexcept
{
    return std::is_permutation(m_polygons.begin(), m_polygons.end(), other.m_polygons.begin());
}

bool Freespace::operator!=(const Freespace &other) const noexcept
{
    return !(this->operator==(other));
}

const std::vector<Polygon>&Freespace::getPolygons() const noexcept
{
    return m_polygons;
}

double Freespace::computeSignedDistanceSquaredToPoint(const types::Point2D &globalPoint) const
{
    if (!m_polygons.empty())
    {
        double distMinToExteriorRing = std::numeric_limits<double>::lowest();
        for (const auto &polygon : m_polygons)
        {
            const auto distToExteriorRing = distancePolygonToPoint(polygon.exterior().values(), globalPoint);
            if (isPointInPolygon(polygon.exterior().values(), globalPoint))
            {
                double distMinToInteriorRings = std::numeric_limits<double>::max();
                for (const auto &interiorRingIter : polygon.interiors())
                {
                    const auto distToInteriorRing = distancePolygonToPoint(interiorRingIter.values(), globalPoint);
                    if (isPointInPolygon(interiorRingIter.values(), globalPoint))
                    {
                        return -distToInteriorRing;
                    }
                    else
                    {
                        distMinToInteriorRings = std::min(distMinToInteriorRings, distToInteriorRing);
                    }
                }
                return std::min(distMinToInteriorRings, distToExteriorRing);
            }
            distMinToExteriorRing = std::max(distMinToExteriorRing, -distToExteriorRing);
        }
        return distMinToExteriorRing;
    }
    return INFEASIBLE_DISTANCE;
}

double Freespace::computeSignedDistanceToPoint(const types::Point2D &globalPoint) const
{
    const double signedDistSquared = computeSignedDistanceSquaredToPoint(globalPoint);
    return signedDistSquared >= .0 ? std::sqrt(signedDistSquared) : -std::sqrt(-signedDistSquared);
}

}
}