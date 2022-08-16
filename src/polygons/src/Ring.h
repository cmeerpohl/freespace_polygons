#pragma once

#include "clipper.hpp"
#include "Types/Point.h"

#include <vector>

namespace freespace
{
namespace polygons
{

class Ring
{
    using Point2D = types::Point2D;

public:
    Ring() = delete;
    explicit Ring(std::vector<Point2D> points) noexcept;
    explicit Ring(const ClipperLib::Path &path) noexcept;
    bool operator==(const Ring &other) const noexcept;
    bool operator!=(const Ring &other) const noexcept;

    [[nodiscard]] explicit operator ClipperLib::Path() const noexcept;
    [[nodiscard]] const std::vector<Point2D> &values() const noexcept;

  private:
    static constexpr double CLIPPER_FACTOR = 1000.;
    std::vector<Point2D> m_points;
};

}
}
