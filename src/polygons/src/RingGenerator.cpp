//
// Created by cmeerpohl on 08.10.20.
//

#include "RingGenerator.h"
#include "Geometry.h"
#include <utility>

namespace freespace
{

namespace polygons
{

namespace {

void shiftCircleBy(std::vector<types::Point2I> &circlePoints, const types::Point2I& shiftPoint)
{
    for (auto &pixel : circlePoints)
    {
        pixel += shiftPoint;
    }
}

types::Point2D shiftIntegerPoint(const types::Point2I &point, const types::Point2I &origin)
{
    types::Point2D ret(point(0), point(1));
    const auto xdiff = point(0) - origin(0);
    const auto ydiff = point(1) - origin(1);
    if (xdiff < .0)
    {
        ret(0) += 0.5;
    }
    else
    {
        ret(0) -= 0.5;
    }
    if (ydiff < .0)
    {
        ret(1) += 0.5;
    }
    else
    {
        ret(1) -= 0.5;
    }
    return ret;
}

}

RingGenerator::RingGenerator(std::shared_ptr<const types::OccupancyMap2D> map, double radiusOuterCircle,
                             double radiusCheckCircle, size_t numberOfAngles, double threshold) noexcept :
      m_map(std::move(map)),
      m_radiusOuterCircle(radiusOuterCircle),
      m_radiusCheckCircle(radiusCheckCircle),
      m_numberOfAngles(numberOfAngles),
      m_threshold(threshold)
{

}

Ring RingGenerator::generateRingFromPose(const types::PoseSE2 &globalPose) const
{
    std::vector<types::Point2D> pointsGlobal;
    if (!m_map) {
        throw std::runtime_error("No map to create Ring for.");
    }
    const auto localPose = m_map->transformPoseToMap(globalPose);
    const auto pointsLocal = sendoutCircles(localPose);
    for (const auto &point : pointsLocal)
    {
        pointsGlobal.push_back(m_map->transformPositionFromMap(point));
    }
    return Ring(pointsGlobal);
}

std::vector<types::Point2D> RingGenerator::sendoutCircles(const types::PoseSE2 &localPose) const
{
    const types::Point2I pointerPositionInt(round2Int(localPose.x()), round2Int(localPose.y()));
    const auto deltaRadianStep = 2 * M_PI / m_numberOfAngles;
    double angle = localPose.phi() + M_PI;
    const types::Point2I firstPoint(addCollisionPointOnLine(pointerPositionInt, angle));
    auto newPointD(shiftIntegerPoint(firstPoint, pointerPositionInt));
    std::vector<types::Point2D> pointsLocal;
    pointsLocal.push_back(newPointD);
    for (size_t i = 1; i < m_numberOfAngles; i++)
    {
        angle -= deltaRadianStep;
        const types::Point2I newPoint(addCollisionPointOnLine(pointerPositionInt, angle));
        newPointD = shiftIntegerPoint(newPoint, pointerPositionInt);
        const int relation(isRight(types::Point2D(localPose.x(), localPose.y()), pointsLocal.back(), newPointD));
        if (relation == 1)
        {
            pointsLocal.push_back(newPointD);
        }
    }
    return pointsLocal;
}

types::Point2I RingGenerator::addCollisionPointOnLine(const types::Point2I &startPoint, double angle) const
{
    std::vector<types::Point2I> linePixels;
    auto collisionPoint = determineLastCollisionPointOnLine(startPoint, angle);
    getLinePixels(linePixels, startPoint, collisionPoint);
    const auto maxCircleRadiusInPixels = static_cast<int>(std::round(m_radiusCheckCircle / m_map->resolution()));
    std::vector<types::Point2I> circlePixels = getHalfCircle(startPoint, maxCircleRadiusInPixels, angle);
    for (auto lineIter = linePixels.begin() + 1; lineIter != linePixels.end();
         ++lineIter)
    {
        const types::Point2I shift = *lineIter - *std::prev(lineIter);
        shiftCircleBy(circlePixels, shift);
        const bool isColliding = checkCircleForCollision(circlePixels, collisionPoint);
        if (isColliding)
        {
            return collisionPoint;
        }
    }
    return collisionPoint;
}

types::Point2I RingGenerator::determineLastCollisionPointOnLine(const types::Point2I &startPoint, double angle) const
{
    int maxRadiusX =
        startPoint[0] + round2Int((m_radiusOuterCircle + m_radiusCheckCircle) / (m_map->resolution()) * cos(angle));
    int maxRadiusY =
        startPoint[1] + round2Int((m_radiusOuterCircle + m_radiusCheckCircle) / (m_map->resolution()) * sin(angle));

    maxRadiusX = std::min(maxRadiusX, static_cast<int>(m_map->width()));
    maxRadiusX = std::max(maxRadiusX, 0);
    maxRadiusY = std::min(maxRadiusY, static_cast<int>(m_map->height()));
    maxRadiusY = std::max(maxRadiusY, 0);
    return types::Point2I(maxRadiusX, maxRadiusY);
}

bool RingGenerator::checkCircleForCollision(const std::vector<types::Point2I> &circlePoints, types::Point2I &collisionPoint) const
{
    for (const auto &circleIter : circlePoints)
    {
        if (checkPointForCollision(circleIter))
        {
            collisionPoint = circleIter;
            return true;
        }
    }
    return false;
}

bool RingGenerator::checkPointForCollision(const types::Point2I &point) const
{
    return (m_map->getValueAt(point) > m_threshold);
}

}
}
