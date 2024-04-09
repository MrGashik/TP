#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <functional>

#include "Shape.h"
#include "Rectangle.h"
#include "Concave.h"
#include "Complexquad.h"

#include "base-types.h"
#include "base-operations.h"

#include "parse.h"
#include "data-set.h"
#include "memory-shapes.h"
#include "traverse.h"

namespace mrgashik = cheshkovskiy;

namespace
{
  void scale(const mrgashik::point_t& scalePos, const double k, std::unique_ptr< mrgashik::Shape >& shape)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("Error scale coefficient!\n");
    }
    mrgashik::point_t oldCenter = shape->getFrameRect().pos;
    shape->move(scalePos);
    double dX = shape->getFrameRect().pos.x - oldCenter.x;
    double dY = shape->getFrameRect().pos.y - oldCenter.y;
    shape->getScale(k);
    shape->move(-dX * k, -dY * k);
  }
}

int main()
{
  using ushape_t = std::unique_ptr< mrgashik::Shape >;
  std::cout << std::fixed << std::setprecision(1);
  size_t size = 0;
  size_t capacity = 0;
  std::unique_ptr< ushape_t[] > shapes = std::make_unique< ushape_t[] >(capacity);
  bool isScaled = false;
  while (!std::cin.eof())
  {
    try
    {
      std::string str = "";
      std::getline(std::cin, str);
      if (str.size())
      {
        std::string name = mrgashik::getSubstring(str);
        if (name == "RECTANGLE")
        {
          mrgashik::point_t A = mrgashik::convertStrToPoint(str);
          mrgashik::point_t B = mrgashik::convertStrToPoint(str);
          ushape_t shape = std::make_unique< mrgashik::Rectangle >(A, B);
          shapes = mrgashik::push< ushape_t, mrgashik::GoldenRatio >(std::move(shapes), size, capacity, std::move(shape));
        }
        else if (name == "CONCAVE")
        {
          mrgashik::point_t A = mrgashik::convertStrToPoint(str);
          mrgashik::point_t B = mrgashik::convertStrToPoint(str);
          mrgashik::point_t C = mrgashik::convertStrToPoint(str);
          mrgashik::point_t D = mrgashik::convertStrToPoint(str);
          ushape_t shape = std::make_unique< mrgashik::Concave >(A, B, C, D);
          shapes = mrgashik::push< ushape_t, mrgashik::GoldenRatio >(std::move(shapes), size, capacity, std::move(shape));
        }
        else if (name == "COMPLEXQUAD")
        {
          mrgashik::point_t A = mrgashik::convertStrToPoint(str);
          mrgashik::point_t B = mrgashik::convertStrToPoint(str);
          mrgashik::point_t C = mrgashik::convertStrToPoint(str);
          mrgashik::point_t D = mrgashik::convertStrToPoint(str);
          ushape_t shape = std::make_unique< mrgashik::Complexquad >(A, B, C, D);
          shapes = mrgashik::push< ushape_t, mrgashik::GoldenRatio >(std::move(shapes), size, capacity, std::move(shape));
        }
        else if (name == "SCALE")
        {
          mrgashik::point_t scalePos = mrgashik::convertStrToPoint(str);
          double k = std::stod(str);
          mrgashik::outShapes(shapes, size, std::cout);
          mrgashik::traverse(shapes, size, std::bind(scale, scalePos, k, std::placeholders::_1));
          mrgashik::outShapes(shapes, size, std::cout);
          isScaled = true;
          break;
        }
        else
        {
          continue;
        }
      }
    }
    catch (const std::exception& err)
    {
      std::cerr << err.what() << '\n';
    }
  }
  if (size == 0 || !isScaled)
  {
    std::cerr << "Error args!\n";
    return 1;
  }
  return 0;
}
