#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iosfwd>
#include <string>

namespace cheshkovskiy
{
  using sll_lit = long long;
  using ull_oct = unsigned long long;

  struct DataStruct {
    sll_lit key1;
    ull_oct key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
  bool operator<(const DataStruct& left, const DataStruct& right);
}

#endif
