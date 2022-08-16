//
// Created by cmeerpohl on 08.10.20.
//

#ifndef SRC_FREESPACEGENERATOR_H
#define SRC_FREESPACEGENERATOR_H

#include "Freespace.h"
#include "Types/PoseSE2.h"



namespace freespace
{

namespace types {
    class OccupancyMap2D;
}

namespace polygons
{

class FreespaceGenerator
{
  public:
    FreespaceGenerator() noexcept;
    FreespaceGenerator(double radiusOuterCircle, double radiusCheckCircle, size_t numberOfAngles, double threshold) noexcept;
    [[nodiscard]] Freespace generateFreespace(std::shared_ptr<types::OccupancyMap2D const> map,
                                                               const std::vector<types::PoseSE2> &origins) const;

  private:
    double m_radiusOuterCircle;
    double m_radiusCheckCircle;
    size_t m_numberOfAngles;
    double m_threshold;
};

}
}

#endif // SRC_FREESPACEGENERATOR_H
