#pragma once

#include "Point.h"
#include "PoseSE2.h"

namespace freespace {

namespace types {

class OccupancyMap2D
{
    static constexpr int8_t MAX_VALUE = 100;
    static constexpr int8_t THRESHOLD = 20;

  public:
    OccupancyMap2D();
    OccupancyMap2D(std::vector<int8_t> values, PoseSE2 origin,
                   double resolution, size_t size);

    [[nodiscard]] types::PoseSE2 transformPoseToMap(const PoseSE2 &pose) const noexcept;
    [[nodiscard]] types::PoseSE2 transformPoseFromMap(const PoseSE2 &pose) const noexcept;
    [[nodiscard]] Point2D transformPositionFromMap(const Point2D &position) const noexcept;
    [[nodiscard]] int8_t getValueAt(const types::Point2I &point) const;
    int8_t operator[](const types::Point2I &point) const noexcept;
    [[nodiscard]] bool isOccupied(const types::Point2I &point) const;
    [[nodiscard]] std::string print() const;

    [[nodiscard]] const std::vector<int8_t> &values() const noexcept;
    std::vector<int8_t> &values() noexcept;
    [[nodiscard]] const PoseSE2 &origin() const noexcept;
    PoseSE2 &origin() noexcept;
    [[nodiscard]] double resolution() const noexcept;
    double &resolution() noexcept;
    [[nodiscard]] size_t width() const noexcept;
    size_t &width() noexcept;
    [[nodiscard]] size_t height() const noexcept;
    size_t &height() noexcept;

  private:
    [[nodiscard]] size_t getIndexFromPoint(const types::Point2I &point) const noexcept;
    [[nodiscard]] types::Point2I getPointAtIndex(size_t i) const noexcept;

  protected:
    std::vector<int8_t> m_values;
    PoseSE2 m_origin;
    double m_resolution;
    size_t m_width;
    size_t m_height;
};

}
}

