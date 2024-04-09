#ifndef BASE_OPERATIONS_H
#define BASE_OPERATIONS_H

#include "base-types.h"

namespace cheshkovskiy
{
  rectangle_t createRectangle(const point_t& A, const point_t& B);
  double triangleArea(const point_t& A, const point_t& B, const point_t& C);
  bool isIntersect(const point_t& A, const point_t& B, const point_t& C, const point_t& D);
  double length(const point_t& A, const point_t& B);
  point_t scalePoint(const point_t& pos, const point_t& center, double k);
  point_t unsafeScale(const point_t& point, const point_t& posScale, double kScale);
}

#endif
