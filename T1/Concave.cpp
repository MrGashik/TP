#include "Concave.h"

#include <stdexcept>

#include "base-operations.h"

cheshkovskiy::Concave::Concave(const point_t& pA, const point_t& pB, const point_t& pC, const point_t& pD):
  pointA_(pA),
  pointB_(pB),
  pointC_(pC),
  center_(pD)
{
  double sideAB = cheshkovskiy::length(pA, pB);
  double sideBC = cheshkovskiy::length(pB, pC);
  double sideCA = cheshkovskiy::length(pA, pC);
  if (!((sideAB < sideBC + sideCA) && (sideBC < sideAB + sideCA) && (sideCA < sideAB + sideBC)))
  {
    throw std::invalid_argument("Incorrect figure!");
  }
  double expr1 = (pA.x - pD.x) * (pB.y - pA.y) - (pB.x - pA.x) * (pA.y - pD.y);
  double expr2 = (pB.x - pD.x) * (pC.y - pB.y) - (pC.x - pB.x) * (pB.y - pD.y);
  double expr3 = (pC.x - pD.x) * (pA.y - pC.y) - (pA.x - pC.x) * (pC.y - pD.y);
  if (!((expr1 > 0 && expr2 > 0 && expr3 > 0) || (expr1 < 0 && expr2 < 0 && expr3 < 0)))
  {
    throw std::invalid_argument("Incorrect figure!");
  }
}
double cheshkovskiy::Concave::getArea() const
{
  double mainArea = cheshkovskiy::triangleArea(pointA_, pointB_, pointC_);
  double subArea = cheshkovskiy::triangleArea(pointB_, pointC_, center_);
  return mainArea - subArea;
}
cheshkovskiy::rectangle_t cheshkovskiy::Concave::getFrameRect() const
{
  double minX = std::min(std::min(pointA_.x, pointB_.x), pointC_.x);
  double maxX = std::max(std::max(pointA_.x, pointB_.x), pointC_.x);
  double minY = std::min(std::min(pointA_.y, pointB_.y), pointC_.y);
  double maxY = std::max(std::max(pointA_.y, pointB_.y), pointC_.y);
  point_t center{ (minX + maxX) / 2, (minY + maxY) / 2 };
  rectangle_t frameRect{ maxX - minX, maxY - minY, center };
  return frameRect;
}
void cheshkovskiy::Concave::move(const point_t& newPos)
{
  double xOffset = newPos.x - center_.x;
  double yOffset = newPos.y - center_.y;
  move(xOffset, yOffset);
}
void cheshkovskiy::Concave::move(double dX, double dY)
{
  point_t offset{ dX, dY };
  pointA_ += offset;
  pointB_ += offset;
  pointC_ += offset;
  center_ += offset;
}
void cheshkovskiy::Concave::scale(double k)
{
  pointA_ += cheshkovskiy::unsafeScale(pointA_, center_, k);
  pointB_ += cheshkovskiy::unsafeScale(pointB_, center_, k);
  pointC_ += cheshkovskiy::unsafeScale(pointC_, center_, k);
}
