#pragma once

#include "../../types/src/Point.h"
#include "clipper.h"

#include <vector>

namespace k2i
{
namespace o2c
{
namespace coll
{

class Ring
{
    using Point2D = types::Point2D;

  public:
    Ring() = delete;
    explicit Ring(std::vector<Point2D> points) noexcept;
    explicit Ring(const Clipper2Lib::PathD &path) noexcept;
    bool operator==(const Ring &other) const noexcept;
    bool operator!=(const Ring &other) const noexcept;

    [[nodiscard]] explicit operator Clipper2Lib::PathD() const noexcept;
    [[nodiscard]] const std::vector<Point2D> &values() const noexcept;

  private:
    static constexpr double CLIPPER_FACTOR = 1000.;
    std::vector<Point2D> m_points;
};

} // namespace coll
} // namespace o2c
} // namespace k2i
