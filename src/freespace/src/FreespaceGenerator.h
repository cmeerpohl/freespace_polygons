//
// Created by cmeerpohl on 08.10.20.
//

#ifndef SRC_FREESPACEGENERATOR_H
#define SRC_FREESPACEGENERATOR_H

#include "Freespace.h"

namespace k2i
{
namespace o2c
{
namespace coll
{

class OccupancyMap2D;

class FreespaceGenerator
{
  public:
    FreespaceGenerator() noexcept;
    FreespaceGenerator(double radiusOuterCircle, double radiusCheckCircle, size_t numberOfAngles, double threshold) noexcept;
    [[nodiscard]] Freespace generateFreespace(std::shared_ptr<OccupancyMap2D const> map,
                                                               const std::vector<types::PoseSE2> &origins) const;

  private:
    double m_radiusOuterCircle;
    double m_radiusCheckCircle;
    size_t m_numberOfAngles;
    double m_threshold;
};

} // namespace coll
} // namespace o2c
} // namespace k2i

#endif // SRC_FREESPACEGENERATOR_H
