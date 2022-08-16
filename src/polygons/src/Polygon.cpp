#include "Polygon.h"

#include <fstream>
#include <utility>
#include <chrono>

namespace freespace
{

namespace polygons
{

Polygon::Polygon(Ring exteriorRing) noexcept : m_exteriorRing(std::move(exteriorRing))
{
}

bool Polygon::operator==(const Polygon &other) const noexcept
{
    return (m_exteriorRing == other.m_exteriorRing &&
            std::is_permutation(m_interiorRings.begin(), m_interiorRings.end(), other.m_interiorRings.begin()));
}

bool Polygon::operator!=(const Polygon &other) const noexcept
{
    return !(this->operator==(other));
}

bool Polygon::isEmpty() const noexcept
{
    return m_exteriorRing.values().empty();
}

std::stringstream Polygon::toStringStream() const
{
    std::stringstream stream;
    for (const auto &exteriorPoint : m_exteriorRing.values())
    {
        stream << exteriorPoint[0] << " " << exteriorPoint[1] << std::endl;
    }
    for (const auto &interiorRing : m_interiorRings)
    {
        stream << std::endl;
        for (const auto &interiorPoint : interiorRing.values())
        {
            stream << interiorPoint.x() << " " << interiorPoint.y() << std::endl;
        }
    };
    return stream;
}

const Ring &Polygon::exterior() const noexcept
{
    return m_exteriorRing;
}

const std::vector<Ring> &Polygon::interiors() const noexcept
{
    return m_interiorRings;
}

void Polygon::addInterior(const Ring &ring) noexcept
{
    m_interiorRings.emplace_back(ring);
}

std::ostream &operator<<(std::ostream &os, const Polygon &poly)
{

    for (const auto &ext : poly.exterior().values())
    {
        os << ext.x() << " " << ext.y() << std::endl;
    }
    return os;
}

}
}