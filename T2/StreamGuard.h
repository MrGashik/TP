#ifndef STREAMGUARD_H
#define STREAMGUARD_H

#include <iomanip>

namespace cheshkovskiy
{
  class StreamGuard
  {
  public:
    StreamGuard(std::ios& stream);
    ~StreamGuard();
  private:
    std::ios& stream_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}

#endif
