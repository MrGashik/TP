#ifndef COMMAND_H
#define COMMAND_H

#include <iosfwd>

#include "dicts.h"

namespace cheshkovskiy
{
  void newTree(std::string, tree_t&);
  void add(std::string, tree_t&);
  void addT(std::string, tree_t&);
  void addLine(std::string, tree_t&);
  void intersection(std::string, tree_t&);
  void subtraction(std::string, tree_t&);
  void remove(std::string, tree_t&);
  void deleteWord(std::string, tree_t&);
  void copy(std::string, tree_t&);
  void search(std::string, tree_t&, std::ostream&);
  void erase(std::string, tree_t&);
  void clear(std::string, tree_t&);
  void print(std::string, tree_t&, std::ostream&);
  void split(std::string, tree_t&, std::ostream&);
  void create(std::string, tree_t&);
}

#endif
