#include "data-set.h"

#include <iostream>
#include <functional>
#include <memory>

#include "traverse.h"

namespace
{
  void outShape(std::unique_ptr< cheshkovskiy::Shape >& shape, std::ostream& stream)
  {
    stream << ' ' << shape->getFrameRect();
  }

  struct sumShapesArea
  {
    sumShapesArea():
      area(0.f)
    {}

    void operator()(std::unique_ptr< cheshkovskiy::Shape >& shape)
    {
      area += shape->getArea();
    }

    double getArea() const
    {
      return area;
    }

  private:
    double area;
  };
}

void cheshkovskiy::outShapes(shapesArray_t& shapes, size_t size, std::ostream& stream)
{
  sumShapesArea functor;
  functor = traverse(shapes, size, functor);
  stream << functor.getArea();
  traverse(shapes, size, std::bind(outShape, std::placeholders::_1, std::ref(stream)));
  stream << '\n';
}
