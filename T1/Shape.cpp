#include "Shape.h"

#include <stdexcept>

void cheshkovskiy::Shape::getScale(double k)
{
  if (k < 0.0)
  {
    throw std::invalid_argument("Error coefficient!\n");
  }
  scale(k);
}
