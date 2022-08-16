#pragma once

#include "Ring.h"

namespace freespace
{

namespace polygons
{

class Polygon
{

  public:
    Polygon() = delete;
    explicit Polygon(Ring exteriorRing) noexcept;
    bool operator==(const Polygon &other) const noexcept;
    bool operator!=(const Polygon &other) const noexcept;
    [[nodiscard]] bool isEmpty() const noexcept;
    [[nodiscard]] std::stringstream toStringStream() const;
    [[nodiscard]] const Ring &exterior() const noexcept;
    [[nodiscard]] const std::vector<Ring> &interiors() const noexcept;
    void addInterior(const Ring& interiorRing) noexcept;

  private:
    Ring m_exteriorRing;
    std::vector<Ring> m_interiorRings;
};

std::ostream &operator<<(std::ostream &os, const Polygon &poly);

}
}