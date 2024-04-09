#include "Rectangle.h"

#include <stdexcept>

cheshkovskiy::Rectangle::Rectangle(const point_t& dL, const point_t& uR):
  rectangle_({uR.x - dL.x, uR.y - dL.y, point_t{(dL.x + uR.x) / 2,(dL.y + uR.y) / 2}})
{
  if ((dL.x >= uR.x) || (dL.y >= uR.y))
  {
    throw std::invalid_argument("Error rectangle!\n");
  }
}

cheshkovskiy::Rectangle::Rectangle(const rectangle_t& rect):
  rectangle_(rect)
{
  if ((rect.width <= 0.0) || (rect.height <= 0.0))
  {
    throw std::invalid_argument("Error rectangle!\n");
  }
}

double cheshkovskiy::Rectangle::getArea() const
{
  return (rectangle_.width * rectangle_.height);
}

cheshkovskiy::rectangle_t cheshkovskiy::Rectangle::getFrameRect() const
{
  return rectangle_;
}

void cheshkovskiy::Rectangle::move(const point_t& pos)
{
  rectangle_.pos = pos;
}

void cheshkovskiy::Rectangle::move(double dX, double dY)
{
  rectangle_.pos.x += dX;
  rectangle_.pos.y += dY;
}

void cheshkovskiy::Rectangle::scale(double k)
{
  rectangle_.width *= k;
  rectangle_.height *= k;
}
