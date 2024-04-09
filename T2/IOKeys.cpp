#include "IOKeys.h"

#include <iostream>

#include "StreamGuard.h"
#include "IODelimiter.h"

std::istream& cheshkovskiy::operator>>(std::istream& in, SllLitIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  StreamGuard guard(in);
  in >> std::dec >> dest.ref;
  in >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
  return in;
}

std::istream& cheshkovskiy::operator>>(std::istream& in, UllOctIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  StreamGuard guard(in);
  in >> std::oct >> dest.ref;
  return in;
}

std::istream& cheshkovskiy::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}
