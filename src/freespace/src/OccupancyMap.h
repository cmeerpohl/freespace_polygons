#pragma once

#include "../../types/src/Point.h"
#include "../../types/src/PoseSE2.h"
#include "../../types/src/Timestamp.h"

namespace k2i
{
namespace o2c
{
namespace coll
{

class OccupancyMap2D
{
    static constexpr int8_t MAX_VALUE = 100;
    static constexpr int8_t THRESHOLD = 20;

  public:
    OccupancyMap2D();
    OccupancyMap2D(std::vector<int8_t> values, types::PoseSE2 origin, const types::Timestamp &creationTime,
                   double resolution, size_t size);

    types::PoseSE2 transformPoseToMap(const types::PoseSE2 &pose) const noexcept;
    types::PoseSE2 transformPoseFromMap(const types::PoseSE2 &pose) const noexcept;
    types::Point2D transformPositionFromMap(const types::Point2D &position) const noexcept;
    int8_t getValueAt(const types::Point2I &point) const;
    int8_t operator[](const types::Point2I &point) const noexcept;
    bool isOccupied(const types::Point2I &point) const;
    std::string print() const;

    const std::vector<int8_t> &values() const noexcept;
    std::vector<int8_t> &values() noexcept;
    const types::PoseSE2 &origin() const noexcept;
    types::PoseSE2 &origin() noexcept;
    const types::Timestamp &time() const noexcept;
    types::Timestamp &time() noexcept;
    double resolution() const noexcept;
    double &resolution() noexcept;
    size_t width() const noexcept;
    size_t &width() noexcept;
    size_t height() const noexcept;
    size_t &height() noexcept;

  private:
    size_t getIndexFromPoint(const types::Point2I &point) const noexcept;
    types::Point2I getPointAtIndex(size_t i) const noexcept;

  protected:
    std::vector<int8_t> m_values;
    types::PoseSE2 m_origin;
    types::Timestamp m_creationTime;
    double m_resolution;
    size_t m_width;
    size_t m_height;
};

} // namespace coll
} // namespace o2c
} // namespace k2i
