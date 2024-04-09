#include "DataStruct.h"

#include <iostream>
#include <string>

#include "IODelimiter.h"
#include "IOKeys.h"
#include "StreamGuard.h"

namespace cheshkovskiy
{
  std::istream& operator>>(std::istream& in, DataStruct& data)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };
    for (int i = 0; i < 3; ++i)
    {
      std::string name = "";
      in >> name;
      if (name == "key1")
      {
        in >> SllLitIO{ input.key1 };
      }
      else if (name == "key2")
      {
        in >> UllOctIO{ input.key2 };
      }
      else if (name == "key3")
      {
        in >> StringIO{ input.key3 };
      }
      else
      {
        in.setstate(std::ios::failbit);
        return in;
      }
      in >> DelimiterIO{ ':' };
    }
    in >> DelimiterIO{ ')' };
    if (in)
    {
      data = input;
    }
    return in;
  };

  std::ostream& operator<<(std::ostream& out, const DataStruct& data)
  {
    {
      StreamGuard guard(out);
      out << "(:key1 " << std::dec << data.key1 << "ll";
    }
    {
      StreamGuard guard(out);
      out << ":key2 0" << std::oct << data.key2;
    }
    out << ":key3 \"" << data.key3 << "\":)";
    return out;
  };

  bool operator<(const DataStruct& left, const DataStruct& right)
  {
    if (left.key1 != right.key1)
    {
      return left.key1 < right.key1;
    }
    else if (left.key2 != right.key2)
    {
      return left.key2 < right.key2;
    }
    else
    {
      return left.key3.length() < right.key3.length();
    }
  };
}
