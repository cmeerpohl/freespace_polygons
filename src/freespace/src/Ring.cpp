#include "Ring.h"

#include <cmath>
#include <utility>

namespace k2i
{
namespace o2c
{
namespace coll
{

Ring::Ring(std::vector<Point2D> points) noexcept : m_points(std::move(points))
{
}

Ring::Ring(const Clipper2Lib::PathD &path) noexcept
{
    m_points.reserve(path.size());
    for (const auto &p : path)
    {
        m_points.emplace_back(p.X / CLIPPER_FACTOR, p.Y / CLIPPER_FACTOR);
    }
}

bool Ring::operator==(const Ring &other) const noexcept
{
    return std::is_permutation(m_points.begin(), m_points.end(), other.m_points.begin(),
                               [](const types::Point2D &a, const types::Point2D &b){ return types::AreSame(a,b); });
}

bool Ring::operator!=(const Ring &other) const noexcept
{
    return !(this->operator==(other));
}



const std::vector<types::Point2D> &Ring::values() const noexcept
{
    return m_points;
}

Ring::operator Clipper2Lib::PathD() const noexcept
{
    Clipper2Lib::PathD ret;
    ret.reserve(m_points.size());
    for (const auto &p : m_points)
    {
        ret.emplace_back(std::round(p.x() * CLIPPER_FACTOR), std::round(p.y() * CLIPPER_FACTOR));
    }
    return ret;
}

} // namespace coll
} // namespace o2c
} // namespace k2i