#include "Geometry.h"
#include "bslam/utils/Convenience.h"

#include <set>

namespace freespace
{

namespace polygons
{

namespace {

bool compPairFirstQuadrant(const types::Point2I &a, const types::Point2I &b) noexcept
{
    if (a(0) < b(0))
        return true;
    else if ((a(0) == b(0)) && (a(1) > b(1)))
        return true;
    else
        return false;
}

bool compPairSecondQuadrant(const types::Point2I &a, const types::Point2I &b) noexcept
{
    if (a(0) > b(0))
        return true;
    else if ((a(0) == b(0)) && (a(1) > b(1)))
        return true;
    else
        return false;
}

bool compPairThirdQuadrant(const types::Point2I &a, const types::Point2I &b) noexcept
{
    if (a(0) > b(0))
        return true;
    else if ((a(0) == b(0)) && (a(1) < b(1)))
        return true;
    else
        return false;
}

bool compPairFourthQuadrant(const types::Point2I &a, const types::Point2I &b) noexcept
{
    if (a(0) < b(0))
        return true;
    else if ((a(0) == b(0)) && (a(1) < b(1)))
        return true;
    else
        return false;
}

struct compIntegerPair
{
    constexpr bool operator()(const std::pair<types::Point2I, double> &a, const std::pair<types::Point2I, double> &b) const noexcept
    {
        return a.second < b.second;
    }
};

void addPoint(std::set<std::pair<types::Point2I, double>, compIntegerPair> &points, types::Point2I candidate, const types::Point2I &origin,
              double direction) noexcept
{
    const double angle = std::atan2((double)candidate(1) - (double)origin(1), (double)candidate(0) - (double)origin(0));
    auto normalizedDirection = bslam::ANGLE_NORMALIZE_INPLACE(direction);
    auto difference = angle - normalizedDirection;
    if (std::fabs(bslam::ANGLE_NORMALIZE_INPLACE(difference)) <= M_PI_2 + 1E-6)
    {
        points.emplace(candidate, angle);
    }
}

}


int round2Int(double dblValue) noexcept
{
    return static_cast<int>(dblValue < 0 ? dblValue - 0.5 : dblValue + 0.5);
}

int isRight(const types::Point2D &a, const types::Point2D &b, const types::Point2D &c) noexcept
{
    if ((a[0] == b[0] && a[1] == b[1]) || (a[0] == c[0] && a[1] == c[1]))
    {
        return 0; // Coincident points.
    }
    // Translate to the origin.
    types::Point2D btmp(b - a), ctmp(c - a);
    double slope2 = btmp[1] / btmp[0];
    double slopep = ctmp[1] / ctmp[0];
    if (slope2 == slopep || (btmp[0] == 0 && ctmp[0] == 0))
        return btmp[1] > 0 // Colinear.
                   ? (ctmp[1] < 0         ? -1
                      : ctmp[1] > btmp[1] ? 1
                                          : 0)
                   : (ctmp[1] > 0         ? -1
                      : ctmp[1] < btmp[1] ? 1
                                          : 0);
    if (btmp[0] >= 0 && slope2 >= 0)
        return ctmp[0] >= 0 // Quadrant 1.
                   ? (slope2 > slopep ? 1 : -1)
                   : (slope2 < slopep ? 1 : -1);
    if (btmp[1] > 0)
        return ctmp[0] < 0 // Quadrant 2.
                   ? (slope2 > slopep ? 1 : -1)
                   : (slope2 < slopep ? 1 : -1);
    if (slope2 >= 0.0)
        return ctmp[0] >= 0 // Quadrant 3.
                   ? (slope2 < slopep ? 1 : -1)
                   : (slope2 > slopep ? 1 : -1);
    return ctmp[0] < 0 // Quadrant 4.
               ? (slope2 < slopep ? 1 : -1)
               : (slope2 > slopep ? 1 : -1);
}

void getLinePixels(std::vector<types::Point2I> &linePixels, const types::Point2I &start,
                   const types::Point2I &end) noexcept
{
    int x0 = start[0];
    int y0 = start[1];
    int x1 = end[0];
    int y1 = end[1];
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    while (true)
    {
        linePixels.emplace_back(x0, y0);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 > dy)
        {
            err += dy;
            x0 += sx;
        } /* e_xy+e_x > 0 */
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        } /* e_xy+e_y < 0 */
    }
}

std::vector<types::Point2I> getCirclePixels(const types::Point2I &midPoint, int radius) noexcept
{
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;

    std::vector<types::Point2I> circlePixels;
    circlePixels.emplace_back(midPoint[0], midPoint[1] + radius);
    circlePixels.emplace_back(midPoint[0] + radius, midPoint[1]);
    circlePixels.emplace_back(midPoint[0], midPoint[1] - radius);
    circlePixels.emplace_back(midPoint[0] - radius, midPoint[1]);
    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;

        circlePixels.emplace_back(midPoint[0] + x, midPoint[1] + y);
        circlePixels.emplace_back(midPoint[0] - x, midPoint[1] + y);
        circlePixels.emplace_back(midPoint[0] - x, midPoint[1] - y);
        circlePixels.emplace_back(midPoint[0] + x, midPoint[1] - y);
        circlePixels.emplace_back(midPoint[0] + y, midPoint[1] + x);
        circlePixels.emplace_back(midPoint[0] - y, midPoint[1] + x);
        circlePixels.emplace_back(midPoint[0] - y, midPoint[1] - x);
        circlePixels.emplace_back(midPoint[0] + y, midPoint[1] - x);
    }
    return circlePixels;
}

std::vector<types::Point2I> getHalfCirclePixels(const types::Point2I &midPoint, int radius) noexcept
{
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;

    std::vector<types::Point2I> circlePixels;
    circlePixels.emplace_back(midPoint[0], midPoint[1] + radius);
    circlePixels.emplace_back(midPoint[0] + radius, midPoint[1]);
    circlePixels.emplace_back(midPoint[0] - radius, midPoint[1]);
    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;

        circlePixels.emplace_back(midPoint[0] + x, midPoint[1] + y);
        circlePixels.emplace_back(midPoint[0] - x, midPoint[1] + y);
        circlePixels.emplace_back(midPoint[0] + y, midPoint[1] + x);
        circlePixels.emplace_back(midPoint[0] - y, midPoint[1] + x);
    }
    // std::sort(circlePixels.begin(), circlePixels.end(), cause::compIntegerPair);
    return circlePixels;
}

bool isPointInPolygon(const std::vector<types::Point2D> &lines, const types::Point2D &testPoint)
{
    assert(lines.size() >= 3);
    bool inside = false;
    types::Point2D last = lines.back();
    for (const auto &lineIter : lines)
    {
        if ((lineIter[1] > testPoint[1]) != (last[1] > testPoint[1]) &&
            testPoint[0] <
                (last[0] - lineIter[0]) * (testPoint[1] - lineIter[1]) / (last[1] - lineIter[1]) + lineIter[0])
        {
            inside = !inside;
        }
        last = lineIter;
    }
    return inside;
}

double distancePolygonToPoint(const std::vector<types::Point2D> &polygon, const types::Point2D &point)
{
    assert(polygon.size() >= 3);
    double distMin = 10E6;
    auto firstIter = polygon.begin();
    auto secondIter = std::next(polygon.begin());
    for (; secondIter != polygon.end(); ++firstIter, ++secondIter)
    {
        distMin = std::min(sqDistPointSegment(*firstIter, *secondIter, point), distMin);
    }
    distMin = std::min(sqDistPointSegment(polygon.back(), polygon.front(), point), distMin);
    return distMin;
}

double sqDistPointPoint(const types::Point2D &a, const types::Point2D &b) noexcept
{
    types::Point2D ab(b - a);
    return ab.dot(ab);
}

double sqDistPointSegment(const types::Point2D &a, const types::Point2D &b, const types::Point2D &c) noexcept
{
    types::Point2D ab(b - a), ac(c - a), bc(c - b);
    double e = ac.dot(ab);
    // Handle cases where c projects outside ab
    if (e <= 0.0)
        return ac.dot(ac);
    double f = ab.dot(ab);
    if (e >= f)
        return bc.dot(bc);
    // Handle cases where c projects onto ab
    return ac.dot(ac) - e * e / f;
}

double interpolate(double valueLow, double valueUp, double alpha) noexcept
{
    return (1 - alpha) * valueLow + alpha * valueUp;
}

/*
types::PoseSE3 fixEndPose(const types::PoseSE3 &startPose, const types::PoseSE3 &endPose)
{
    types::Quaternion newQuat;
    newQuat.f(endPose.q(). * -1.0);
    const types::PoseSE3 newEndPose(endPose.translation(), newQuat);
    double prodNormal = (endPose.toVector() - startPose.toVector()).dot(endPose.toVector() - startPose.toVector());
    double prodNew = (newEndPose.toVector() - startPose.toVector()).dot(newEndPose.toVector() - startPose.toVector());
    return prodNormal > prodNew ? newEndPose : endPose;
} */

std::vector<types::Point2I> getSortedCirclePixels(const types::Point2I &midPoint, int radius) noexcept
{
    std::vector<types::Point2I> firstQuadrantPixels;
    std::vector<types::Point2I> secondQuadrantPixels;
    std::vector<types::Point2I> thirdQuadrantPixels;
    std::vector<types::Point2I> fourthQuadrantPixels;
    std::vector<types::Point2I> allPixels;
    {
        int f = 1 - radius;
        int ddF_x = 0;
        int ddF_y = -2 * radius;
        int x = 0;
        int y = radius;

        firstQuadrantPixels.emplace_back(midPoint[0], midPoint[1] + radius);
        secondQuadrantPixels.emplace_back(midPoint[0] + radius, midPoint[1]);
        thirdQuadrantPixels.emplace_back(midPoint[0], midPoint[1] - radius);
        fourthQuadrantPixels.emplace_back(midPoint[0] - radius, midPoint[1]);
        while (x < y)
        {
            if (f >= 0)
            {
                y--;
                ddF_y += 2;
                f += ddF_y;
            }
            x++;
            ddF_x += 2;
            f += ddF_x + 1;

            firstQuadrantPixels.emplace_back(midPoint[0] + x, midPoint[1] + y);
            firstQuadrantPixels.emplace_back(midPoint[0] + y, midPoint[1] + x);
            secondQuadrantPixels.emplace_back(midPoint[0] + x, midPoint[1] - y);
            secondQuadrantPixels.emplace_back(midPoint[0] + y, midPoint[1] - x);
            thirdQuadrantPixels.emplace_back(midPoint[0] - x, midPoint[1] - y);
            thirdQuadrantPixels.emplace_back(midPoint[0] - y, midPoint[1] - x);
            fourthQuadrantPixels.emplace_back(midPoint[0] - x, midPoint[1] + y);
            fourthQuadrantPixels.emplace_back(midPoint[0] - y, midPoint[1] + x);
        }
        std::sort(firstQuadrantPixels.begin(), firstQuadrantPixels.end(), compPairFirstQuadrant);
        std::sort(secondQuadrantPixels.begin(), secondQuadrantPixels.end(), compPairSecondQuadrant);
        std::sort(thirdQuadrantPixels.begin(), thirdQuadrantPixels.end(), compPairThirdQuadrant);
        std::sort(fourthQuadrantPixels.begin(), fourthQuadrantPixels.end(), compPairFourthQuadrant);
    }
    allPixels.insert(allPixels.end(), thirdQuadrantPixels.begin(), thirdQuadrantPixels.end());
    allPixels.insert(allPixels.end(), fourthQuadrantPixels.begin(), fourthQuadrantPixels.end());
    allPixels.insert(allPixels.end(), firstQuadrantPixels.begin(), firstQuadrantPixels.end());
    allPixels.insert(allPixels.end(), secondQuadrantPixels.begin(), secondQuadrantPixels.end());
    return allPixels;
}

std::vector<types::Point2I> getHalfCircle(const types::Point2I &midPoint, int radius, double angle) noexcept
{
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
    int lastX = x;
    int lastY = y;

    std::set<std::pair<types::Point2I, double>, compIntegerPair> circlePixels;
    addPoint(circlePixels, {midPoint[0], midPoint[1] + radius}, midPoint, angle);
    addPoint(circlePixels, {midPoint[0] + radius, midPoint[1]}, midPoint, angle);
    addPoint(circlePixels, {midPoint[0] - radius, midPoint[1]}, midPoint, angle);
    addPoint(circlePixels, {midPoint[0], midPoint[1] - radius}, midPoint, angle);

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;

        int diffX = x - lastX;
        int diffY = y - lastY;
        if ((abs(diffX) == 1) && (abs(diffY) == 1))
        {
            addPoint(circlePixels, {midPoint[0] + x, midPoint[1] + lastY}, midPoint, angle);
            addPoint(circlePixels, {midPoint[0] - x, midPoint[1] + lastY}, midPoint, angle);
            addPoint(circlePixels, {midPoint[0] - x, midPoint[1] - lastY}, midPoint, angle);
            addPoint(circlePixels, {midPoint[0] + x, midPoint[1] - lastY}, midPoint, angle);
            addPoint(circlePixels, {midPoint[0] + lastY, midPoint[1] + x}, midPoint, angle);
            addPoint(circlePixels, {midPoint[0] - lastY, midPoint[1] + x}, midPoint, angle);
            addPoint(circlePixels, {midPoint[0] - lastY, midPoint[1] - x}, midPoint, angle);
            addPoint(circlePixels, {midPoint[0] + lastY, midPoint[1] - x}, midPoint, angle);
        }

        addPoint(circlePixels, {midPoint[0] + x, midPoint[1] + y}, midPoint, angle);
        addPoint(circlePixels, {midPoint[0] - x, midPoint[1] + y}, midPoint, angle);
        addPoint(circlePixels, {midPoint[0] - x, midPoint[1] - y}, midPoint, angle);
        addPoint(circlePixels, {midPoint[0] + x, midPoint[1] - y}, midPoint, angle);
        addPoint(circlePixels, {midPoint[0] + y, midPoint[1] + x}, midPoint, angle);
        addPoint(circlePixels, {midPoint[0] - y, midPoint[1] + x}, midPoint, angle);
        addPoint(circlePixels, {midPoint[0] - y, midPoint[1] - x}, midPoint, angle);
        addPoint(circlePixels, {midPoint[0] + y, midPoint[1] - x}, midPoint, angle);

        lastX = x;
        lastY = y;
    }
    std::vector<types::Point2I> ret;
    ret.reserve(std::distance(circlePixels.begin(), circlePixels.end()));
    std::transform(circlePixels.begin(), circlePixels.end(), std::back_inserter(ret),
                   [](const std::pair<types::Point2I, double> &p) { return p.first; });
    return ret;
}

}
}