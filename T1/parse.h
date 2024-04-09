#ifndef PARSE_H
#define PARSE_H

#include <string>

#include "base-types.h"

namespace cheshkovskiy
{
  point_t convertStrToPoint(std::string& str);
  std::string getSubstring(std::string& str);
}

#endif
