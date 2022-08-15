#include "OccupancyMap.h"
 #include <utility>

namespace k2i
{
namespace o2c
{
namespace coll
{

OccupancyMap2D::OccupancyMap2D() : m_values{}, m_origin{}, m_creationTime{}, m_resolution{.0}, m_width{0}, m_height{0}
{
}

OccupancyMap2D::OccupancyMap2D(std::vector<int8_t> values, types::PoseSE2 origin, const types::Timestamp &creationTime, double resolution, size_t size)
    : m_values(std::move(values)), m_origin(std::move(origin)), m_creationTime(creationTime), m_resolution(resolution), m_width(size), m_height(size)
{
}

types::PoseSE2 OccupancyMap2D::transformPoseToMap(const types::PoseSE2 &pose) const noexcept
{
    types::PoseSE2 newOrigin(0.0, 0.0, 0.0);
    types::PoseSE2 transform = newOrigin.oplus(m_origin);
    types::PoseSE2 poseTemp(pose.ominus(transform));
    return types::PoseSE2(poseTemp.translation() / m_resolution, poseTemp.phi());
}

types::PoseSE2 OccupancyMap2D::transformPoseFromMap(const types::PoseSE2 &pose) const noexcept
{
    types::PoseSE2 scaledPose(m_resolution * pose.x(), m_resolution * pose.y(), pose.phi());
    types::PoseSE2 newOrigin(0.0, 0.0, 0.0);
    types::PoseSE2 transform = newOrigin.oplus(m_origin);
    return scaledPose.oplus(transform);
}

types::Point2D OccupancyMap2D::transformPositionFromMap(const types::Point2D &position) const noexcept
{
    types::PoseSE2 localPose(m_resolution * position[0], m_resolution * position[1], 0.0);
    types::PoseSE2 newOrigin(0.0, 0.0, 0.0);
    types::PoseSE2 transform = newOrigin.oplus(m_origin);
    types::PoseSE2 globalPose(localPose.oplus(transform));
    return types::Point2D(globalPose.x(), globalPose.y());
}

int8_t OccupancyMap2D::getValueAt(const types::Point2I &point) const
{
    return m_values.at(getIndexFromPoint(point));
}

int8_t OccupancyMap2D::operator[](const types::Point2I &point) const noexcept
{
    return m_values[getIndexFromPoint(point)];
}

bool OccupancyMap2D::isOccupied(const types::Point2I &point) const
{
    const auto entry = getIndexFromPoint(point);
    assert(entry <= m_values.size());
    return m_values[entry] > THRESHOLD;
}

std::string OccupancyMap2D::print() const
{

    std::stringstream stream;

    for (size_t i = 0; i < m_values.size(); i++)
    {

        if (m_values[i] > THRESHOLD)
        {

            const auto point = getPointAtIndex(i);
            const auto ret = transformPositionFromMap({point.x(), point.y()});

            stream << ret.x() << " " << ret.y() << std::endl;
        }
    }
    return stream.str();
}

size_t OccupancyMap2D::getIndexFromPoint(const types::Point2I &point) const noexcept
{
    return static_cast<size_t>(point.y() * m_width + point.x());
}

types::Point2I OccupancyMap2D::getPointAtIndex(size_t i) const noexcept
{

    const auto aux = std::div(static_cast<long>(i), static_cast<long>(m_width));
    return {aux.rem, aux.quot};
}

const std::vector<int8_t> &OccupancyMap2D::values() const noexcept
{
    return m_values;
}

std::vector<int8_t> &OccupancyMap2D::values() noexcept
{
    return m_values;
}

const types::PoseSE2 &OccupancyMap2D::origin() const noexcept
{
    return m_origin;
}

types::PoseSE2 &OccupancyMap2D::origin() noexcept
{
    return m_origin;
}

const types::Timestamp& OccupancyMap2D::time() const noexcept
{
    return m_creationTime;
}

types::Timestamp& OccupancyMap2D::time() noexcept
{
    return m_creationTime;
}

double OccupancyMap2D::resolution() const noexcept
{
    return m_resolution;
}

double &OccupancyMap2D::resolution() noexcept
{
    return m_resolution;
}

size_t OccupancyMap2D::width() const noexcept
{
    return m_width;
}

size_t &OccupancyMap2D::width() noexcept
{
    return m_width;
}

size_t OccupancyMap2D::height() const noexcept
{
    return m_height;
}

size_t &OccupancyMap2D::height() noexcept
{
    return m_height;
}

} // namespace coll
} // namespace o2c
} // namespace k2i