#ifndef BASE_TYPES_H
#define BASE_TYPES_H

#include <iosfwd>

namespace cheshkovskiy
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };

  bool operator==(const point_t& A, const point_t& B);
  point_t& operator+=(point_t& defultPoint, const point_t& increasePoint);
  std::ostream& operator<<(std::ostream& out, const point_t& point);
  std::ostream& operator<<(std::ostream& out, const rectangle_t& rect);
}

#endif
