#pragma once

#include "../../types/src/PoseSE2.h"
#include "Polygon.h"

#include <memory>

namespace k2i
{
namespace o2c
{
namespace coll
{

class Freespace
{
  public:
    static constexpr double INFEASIBLE_DISTANCE = -10E9;

    Freespace() = delete;
    explicit Freespace(std::vector<Polygon> polygons) noexcept;
    bool operator==(const Freespace &other) const noexcept;
    bool operator!=(const Freespace &other) const noexcept;
    /**
     *
     * @param point Point in global coordinates
     * @return closed distance to polygons. A positive sign indicates feasibility, a negative sign indicates infeasibility
     */
    [[nodiscard]] double computeSignedDistanceSquaredToPoint(const types::Point2D &globalPoint) const;
    [[nodiscard]] double computeSignedDistanceToPoint(const types::Point2D &globalPoint) const;
    [[nodiscard]] const std::vector<Polygon> &getPolygons() const noexcept;

  private:
    std::vector<Polygon> m_polygons;
};


} // namespace coll
} // namespace o2c
} // namespace k2i