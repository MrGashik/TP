#ifndef COMPLEXQUAD_H
#define COMPLEXQUAD_H

#include "Shape.h"
#include "base-types.h"

namespace cheshkovskiy
{
  class Complexquad: public Shape
  {
  public:
    Complexquad() = delete;
    Complexquad(const point_t& A, const point_t& B, const point_t& C, const point_t& D);
    ~Complexquad() = default;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& newPos) override;
    void move(double dX, double dY) override;
    void scale(double k) override;

  private:
    point_t A_;
    point_t B_;
    point_t C_;
    point_t D_;
    point_t getCenterPos() const;
  };
}

#endif

