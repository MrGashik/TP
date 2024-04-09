#ifndef TRAVERSE_H
#define TRAVERSE_H

#include <memory>

namespace cheshkovskiy
{
  template< typename T, typename F >
  F traverse(std::unique_ptr< T[] >& array, size_t size, F f)
  {
    for (auto i = size_t{ 0 }; i < size; ++i)
    {
      f(array[i]);
    }
    return f;
  }
}

#endif
