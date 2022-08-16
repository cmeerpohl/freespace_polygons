//
// Created by cmeerpohl on 08.10.20.
//

#include "FreespaceGenerator.h"
#include "RingGenerator.h"
#include "PolygonClipper.h"
#include "Types/OccupancyMap.h"

#include <utility>

namespace freespace
{

namespace polygons
{


FreespaceGenerator::FreespaceGenerator() noexcept
    : m_radiusOuterCircle(7.0), m_radiusCheckCircle(0.2), m_numberOfAngles(90), m_threshold(20)
{
}

FreespaceGenerator::FreespaceGenerator(double radiusOuterCircle, double radiusCheckCircle, size_t numberOfAngles,
                                       double threshold) noexcept
    : m_radiusOuterCircle(radiusOuterCircle), m_radiusCheckCircle(radiusCheckCircle), m_numberOfAngles(numberOfAngles),
      m_threshold(threshold)
{
}

Freespace FreespaceGenerator::generateFreespace(
    std::shared_ptr<types::OccupancyMap2D const> map, const std::vector<types::PoseSE2> &origins) const
{
    RingGenerator generator( std::move(map), m_radiusOuterCircle, m_radiusCheckCircle, m_numberOfAngles, m_threshold);
    std::vector<Polygon> exteriorRings;
    exteriorRings.reserve(origins.size());
    for(const auto& origin : origins) {
        exteriorRings.emplace_back(Polygon(generator.generateRingFromPose(origin)));
    }
    const auto polygonUnion = PolygonClipper::unify(exteriorRings);
    return Freespace( polygonUnion );
}

}
}
