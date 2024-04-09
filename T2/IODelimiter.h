#ifndef IODELIMITER_HPP
#define IODELIMITER_HPP

#include <iosfwd>

namespace cheshkovskiy
{
  struct DelimiterIO
  {
    char exp;
  };

  std::istream& operator>>(std::istream&, DelimiterIO&&);
}

#endif
