#include "base-operations.h"

#include <algorithm>
#include <cassert>
#include <cmath>

using pnt_t = cheshkovskiy::point_t;

namespace
{
  double getArea(const pnt_t& A, const pnt_t& B, const pnt_t& C)
  {
    return ((B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x));
  }

  bool isIntersect(double A, double B, double C, double D)
  {
    if (A > B)
    {
      std::swap(A, B);
    }
    if (C > D)
    {
      std::swap(C, D);
    }
    return (std::max(A, C) <= std::min(B, D));
  }
}

cheshkovskiy::rectangle_t cheshkovskiy::createRectangle(const point_t& A, const point_t& B)
{
  rectangle_t tempRectangle;
  tempRectangle.width = std::abs(A.x - B.x);
  tempRectangle.height = std::abs(A.y - B.y);
  tempRectangle.pos.x = ((A.x + B.x) / 2);
  tempRectangle.pos.y = ((A.y + B.y) / 2);
  return tempRectangle;
}

double cheshkovskiy::triangleArea(const point_t& pA, const point_t& pB, const point_t& pC)
{
  double sideAB = cheshkovskiy::length(pA, pB);
  double sideBC = cheshkovskiy::length(pB, pC);
  double sideCA = cheshkovskiy::length(pA, pC);
  double halfPerimeter = (sideAB + sideBC + sideCA) / 2;
  return std::sqrt(halfPerimeter * (halfPerimeter - sideAB) * (halfPerimeter - sideBC) * (halfPerimeter - sideCA));
}

bool cheshkovskiy::isIntersect(const point_t& A, const point_t& B, const point_t& C, const point_t& D)
{
  bool intersect = ::isIntersect(A.x, B.x, C.x, D.x) && ::isIntersect(A.y, B.y, C.y, D.y);
  return (intersect && ::getArea(A, B, C) * ::getArea(A, B, D) <= 0 && ::getArea(C, D, A) * ::getArea(C, D, B) <= 0);
}

double cheshkovskiy::length(const point_t& A, const point_t& B)
{
  return std::sqrt(std::pow((B.x - A.x), 2) + pow((B.y - A.y), 2));
}

pnt_t cheshkovskiy::scalePoint(const point_t& pos, const point_t& center, double k)
{
  return point_t{ center.x + k * (pos.x - center.x), center.y + k * (pos.y - center.y) };
}

pnt_t cheshkovskiy::unsafeScale(const point_t& tempPoint, const point_t& posScale, double kScale)
{
  assert(kScale > 0);
  pnt_t point{ (kScale - 1) * (tempPoint.x - posScale.x), (kScale - 1) * (tempPoint.y - posScale.y) };
  return point;
}
