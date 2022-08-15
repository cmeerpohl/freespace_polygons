//
// Created by cmeerpohl on 08.10.20.
//

#ifndef SRC_RINGGENERATOR_H
#define SRC_RINGGENERATOR_H

#include "OccupancyMap.h"
#include "Ring.h"
#include <memory>

namespace k2i
{
namespace o2c
{
namespace coll
{

class RingGenerator
{
  public:
    RingGenerator() = delete;
    RingGenerator(std::shared_ptr<OccupancyMap2D const> map, double radiusOuterCircle, double radiusCheckCircle,
                  size_t numberOfAngles, double threshold) noexcept;
    [[nodiscard]] Ring generateRingFromPose(const types::PoseSE2 &globalPose) const;

  private:
    [[nodiscard]] std::vector<types::Point2D> sendoutCircles(const types::PoseSE2 &localPose) const;
    [[nodiscard]] types::Point2I addCollisionPointOnLine(const types::Point2I &startPoint, double angle) const;
    [[nodiscard]] types::Point2I determineLastCollisionPointOnLine(const types::Point2I &startPoint, double angle) const;
    [[nodiscard]] bool checkCircleForCollision(const std::vector<types::Point2I> &circlePoints, types::Point2I &collisionPoint) const;
    [[nodiscard]] bool checkPointForCollision(const types::Point2I &point) const;

  private:
    std::shared_ptr<OccupancyMap2D const> m_map;
    double m_radiusOuterCircle{};
    double m_radiusCheckCircle{};
    size_t m_numberOfAngles{};
    double m_threshold{};
};

} // namespace coll
} // namespace o2c
} // namespace k2i

#endif // SRC_RINGGENERATOR_H
