#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <map>

#include "command.h"
#include "WorkType.h"

namespace mrgashik = cheshkovskiy;
using namespace std::placeholders;

int main(int argc, char**)
{
  if (argc != 1)
  {
    std::cerr << "<INVALID_ARGUMENTS>\n";
    return 1;
  }

  mrgashik::tree_t dicts;

  using func_t = std::function< void(std::string) >;
  std::map< std::string, func_t > commandsDict
  {
    {"new", std::bind(mrgashik::newTree, _1, std::ref(dicts))},
    {"add", std::bind(mrgashik::add, _1, std::ref(dicts))},
    {"addT", std::bind(mrgashik::addT, _1, std::ref(dicts))},
    {"addLine", std::bind(mrgashik::addLine, _1, std::ref(dicts))},
    {"intersection", std::bind(mrgashik::intersection, _1, std::ref(dicts))},
    {"subtraction", std::bind(mrgashik::subtraction, _1, std::ref(dicts))},
    {"remove", std::bind(mrgashik::remove, _1, std::ref(dicts))},
    {"deleteWord", std::bind(mrgashik::deleteWord, _1, std::ref(dicts))},
    {"copy", std::bind(mrgashik::copy, _1, std::ref(dicts))},
    {"search", std::bind(mrgashik::search, _1, std::ref(dicts), std::ref(std::cout))},
    {"erase", std::bind(mrgashik::erase, _1, std::ref(dicts))},
    {"clear", std::bind(mrgashik::clear, _1, std::ref(dicts))},
    {"print", std::bind(mrgashik::print, _1, std::ref(dicts), std::ref(std::cout))},
    {"split", std::bind(mrgashik::split, _1, std::ref(dicts), std::ref(std::cout))},
    {"create", std::bind(mrgashik::create, _1, std::ref(dicts))},
  };

  while (std::cin)
  {
    std::string command{ "" };
    std::getline(std::cin, command);
    if (command.empty())
    {
      continue;
    }
    std::string commandName = mrgashik::getWord(command, false);
    std::map< std::string, func_t >::iterator commandsDictIter = commandsDict.find(commandName);
    try
    {
      if (commandsDictIter == commandsDict.end())
      {
        throw std::logic_error("<INVALID_COMMAND>");
      }
      commandsDictIter->second(command);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  return 0;
}
