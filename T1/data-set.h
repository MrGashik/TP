#ifndef DATA_SET_H
#define DATA_SET_H

#include <iosfwd>
#include <memory>

#include "Shape.h"
#include "base-types.h"

namespace cheshkovskiy
{
  using shapesArray_t = std::unique_ptr< std::unique_ptr< cheshkovskiy::Shape >[] >;
  using pointsArray_t = std::unique_ptr< point_t[] >;
  void outShapes(shapesArray_t&, size_t, std::ostream&);
}

#endif
