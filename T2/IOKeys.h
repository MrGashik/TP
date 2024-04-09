#ifndef IOKEYS_H
#define IOKEYS_H

#include <string>
#include <iosfwd>

namespace cheshkovskiy
{
  using sll_lit = long long;
  using ull_oct = unsigned long long;

  struct SllLitIO
  {
    sll_lit& ref;
  };

  struct UllOctIO
  {
    ull_oct& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  std::istream& operator>>(std::istream&, SllLitIO&&);
  std::istream& operator>>(std::istream&, UllOctIO&&);
  std::istream& operator>>(std::istream&, StringIO&&);
}

#endif
