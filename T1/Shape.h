#ifndef SHAPE_H
#define SHAPE_H

#include "base-types.h"

namespace cheshkovskiy
{
  class Shape
  {
  public:

    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& point) = 0;
    virtual void move(double dX, double dY) = 0;
    void getScale(double k);

  protected:
    virtual void scale(double k) = 0;
  };
}

#endif
