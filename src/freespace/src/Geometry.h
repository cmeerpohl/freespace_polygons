#pragma once

#include "../../types/src/Point.h"
#include "../../types/src/PoseSE3.h"

namespace k2i
{
namespace o2c
{
namespace coll
{

int round2Int(double dblValue) noexcept;
int isRight(const types::Point2D &a, const types::Point2D &b, const types::Point2D &c) noexcept;
void getLinePixels(std::vector<types::Point2I> &linePixels, const types::Point2I &start, const types::Point2I &end) noexcept;
std::vector<types::Point2I> getSortedCirclePixels(const types::Point2I &midPoint, int radius) noexcept;
std::vector<types::Point2I> getCirclePixels(const types::Point2I &midPoint, int radius) noexcept;
std::vector<types::Point2I> getHalfCirclePixels(const types::Point2I &midPoint, int radius) noexcept;
std::vector<types::Point2I> getHalfCircle(const types::Point2I &midPoint, int radius, double angle) noexcept;
bool isPointInPolygon(const std::vector<types::Point2D> &lines, const types::Point2D &testPoint);
double sqDistPointSegment(const types::Point2D &a, const types::Point2D &b, const types::Point2D &c) noexcept;
double sqDistPointPoint(const types::Point2D &a, const types::Point2D &b) noexcept;
double distancePolygonToPoint(const std::vector<types::Point2D> &polygon, const types::Point2D &point);
double interpolate(double valueLow, double valueUp, double alpha) noexcept;
//types::PoseSE3 fixEndPose(const types::PoseSE3 &startPose, const types::PoseSE3 &endPose);

} // namespace coll
} // namespace o2c
} // namespace k2i