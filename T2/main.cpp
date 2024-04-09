#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "DataStruct.h"

namespace mrgashik = cheshkovskiy;

int main()
{
  using inIter = std::istream_iterator< mrgashik::DataStruct >;
  using outIter = std::ostream_iterator< mrgashik::DataStruct >;
  std::vector< mrgashik::DataStruct > data;
  while (!std::cin.eof()) {
    std::copy(inIter(std::cin), inIter(), std::back_inserter(data));
    if (std::cin.rdstate() == std::ios::failbit) {
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cin.clear();
    }
  }
  std::sort(data.begin(), data.end());
  std::copy(data.begin(), data.end(), outIter(std::cout, "\n"));
  return 0;
}
