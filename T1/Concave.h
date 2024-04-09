#ifndef CONCAVE_H
#define CONCAVE_H

#include "Shape.h"
#include "base-types.h"

namespace cheshkovskiy
{
  class Concave: public Shape
  {
  public:
    Concave() = delete;
    Concave(const point_t& pA, const point_t& pB, const point_t& pC, const point_t& pD);
    ~Concave() = default;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& newPos) override;
    void move(double dX, double dY) override;
    void scale(double k) override;

  private:
    point_t pointA_;
    point_t pointB_;
    point_t pointC_;
    point_t center_;
  };
}
#endif
