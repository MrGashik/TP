#include "Complexquad.h"

#include <algorithm>
#include <stdexcept>

#include "base-operations.h"

cheshkovskiy::Complexquad::Complexquad(const point_t& A, const point_t& B, const point_t& C, const point_t& D):
  A_(A),
  B_(B),
  C_(C),
  D_(D)
{
  bool isEqual = ((A == B) || (A == C) || (A == D) || (B == C) || (B == D) || (C == D));
  point_t intersectPos = getCenterPos();
  bool isPos = intersectPos == A || intersectPos == B || intersectPos == C || intersectPos == D;
  if (isEqual || isPos || !isIntersect(A, B, C, D))
  {
    throw std::invalid_argument("Error values!");
  }
}

double cheshkovskiy::Complexquad::getArea() const
{
  point_t pos = getCenterPos();
  return (triangleArea(A_, pos, D_) + triangleArea(C_, B_, pos));
}

cheshkovskiy::rectangle_t cheshkovskiy::Complexquad::getFrameRect() const
{
  point_t leftDown{ std::min({A_.x, B_.x, C_.x, D_.x}), std::min({A_.y, B_.y, C_.y, D_.y}) };
  point_t rightUp{ std::max({A_.x, B_.x, C_.x, D_.x}), std::max({A_.y, B_.y, C_.y, D_.y}) };
  return createRectangle(leftDown, rightUp);
}

void cheshkovskiy::Complexquad::move(const point_t& newPos)
{
  point_t pos = getCenterPos();
  point_t dPoint{ newPos.x - pos.x, newPos.y - pos.y };
  A_ += dPoint;
  B_ += dPoint;
  C_ += dPoint;
  D_ += dPoint;
}

void cheshkovskiy::Complexquad::move(double dX, double dY)
{
  point_t dPoint{ dX, dY };
  A_ += dPoint;
  B_ += dPoint;
  C_ += dPoint;
  D_ += dPoint;
}

void cheshkovskiy::Complexquad::scale(double k)
{
  point_t pos = getCenterPos();
  A_ = scalePoint(A_, pos, k);
  B_ = scalePoint(B_, pos, k);
  C_ = scalePoint(C_, pos, k);
  D_ = scalePoint(D_, pos, k);
}

cheshkovskiy::point_t cheshkovskiy::Complexquad::getCenterPos() const
{
  point_t pos;
  double n = 0;
  if (B_.y - A_.y != 0)
  {
    double q = (B_.x - A_.x) / (A_.y - B_.y);
    double sn = (C_.x - D_.x) + (C_.y - D_.y) * q;
    double fn = (C_.x - A_.x) + (C_.y - A_.y) * q;
    n = fn / sn;
  }
  else
  {
    n = (C_.y - A_.y) / (C_.y - D_.y);
  }
  pos.x = C_.x + (D_.x - C_.x) * n;
  pos.y = C_.y + (D_.y - C_.y) * n;
  return pos;
}
