#ifndef DICTS_H
#define DICTS_H

#include <map>
#include <set>
#include <tuple>
#include <string>
#include <iosfwd>

namespace cheshkovskiy
{
  using number_t = size_t;
  using num_set_t = std::set< number_t >;
  using word_t = std::map< std::string, num_set_t >;
  using tree_t = std::map< std::string, std::tuple< word_t, std::string, size_t > >;

  void outText(const std::string&, size_t, std::ostream&);
  void outDict(const word_t&, std::ostream&);
  void outLink(const word_t::value_type&, std::ostream& out);
  void outNumList(const num_set_t&, std::ostream&);
  void fileDict(const word_t&, std::ofstream&);
  void fileLink(const word_t::value_type&, std::ofstream& out);
  void fileNumList(const num_set_t&, std::ofstream&);
}

#endif
