#include "base-types.h"

#include <iostream>

using pnt_t = cheshkovskiy::point_t;

bool cheshkovskiy::operator==(const pnt_t& A, const pnt_t& B)
{
  return (A.x == B.x && A.y == B.y);
}

pnt_t& cheshkovskiy::operator+=(point_t& defultPoint, const point_t& increasePoint)
{
  defultPoint.x += increasePoint.x;
  defultPoint.y += increasePoint.y;
  return defultPoint;
}

std::ostream& cheshkovskiy::operator<<(std::ostream& out, const point_t& point)
{
  out << point.x << ' ' << point.y;
  return out;
}

std::ostream& cheshkovskiy::operator<<(std::ostream& out, const rectangle_t& rect)
{
  point_t leftDown{ rect.pos.x - rect.width / 2, rect.pos.y - rect.height / 2 };
  point_t rightUp{ rect.pos.x + rect.width / 2, rect.pos.y + rect.height / 2 };
  out << leftDown << ' ' << rightUp;
  return out;
}
