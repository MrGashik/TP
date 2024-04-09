#include "StreamGuard.h"

#include <iomanip>

namespace cheshkovskiy
{
  StreamGuard::StreamGuard(std::ios& stream):
    stream_(stream),
    precision_(stream.precision()),
    flags_(stream.flags())
  {}

  StreamGuard::~StreamGuard()
  {
    stream_.precision(precision_);
    stream_.flags(flags_);
  }
}
