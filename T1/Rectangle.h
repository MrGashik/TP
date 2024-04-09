#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include "base-types.h"

namespace cheshkovskiy
{
  class Rectangle: public Shape
  {
  public:
    Rectangle() = delete;
    Rectangle(const point_t& downLeft, const point_t& upRight);
    Rectangle(const rectangle_t& rect);
    ~Rectangle() = default;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dX, double dY) override;
    void scale(double k) override;

  private:
    rectangle_t rectangle_;
  };
}

#endif
