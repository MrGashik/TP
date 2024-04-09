#include "dicts.h"

#include <fstream>
#include <algorithm>
#include <iomanip>

#include "WorkType.h"

void cheshkovskiy::outText(const std::string& text, size_t lastLineNum, std::ostream& out)
{
  std::string line;
  size_t step;
  size_t beginPos = 0;
  for (size_t lineNum = 1; lineNum <= lastLineNum; lineNum++)
  {
    line = "";
    step = 0;
    while (text[beginPos + step] != '\n')
    {
      step++;
    }
    line = text.substr(beginPos, step);
    out << lineNum << ": " << line << '\n';
    beginPos += step + 1;
  }
}

void cheshkovskiy::outDict(const word_t& dict, std::ostream& out)
{
  for (auto&& translation : dict)
  {
    outLink(translation, out);
  }
}

void cheshkovskiy::outLink(const word_t::value_type& translation, std::ostream& out)
{
  out.fill('.');
  out << std::setiosflags(std::ios::left) << std::setw(40) << translation.first << std::resetiosflags(std::ios::left);
  outNumList(translation.second, out);
  out.fill(' ');
  out << '\n';
}

void cheshkovskiy::outNumList(const num_set_t& list, std::ostream& out)
{
  out << '[';
  bool isFirst = true;
  for (auto&& num : list)
  {
    if (!isFirst)
    {
      out << "; ";
    }
    else
    {
      isFirst = false;
    }
    out << num;
  }
  out << ']';
}

void cheshkovskiy::fileDict(const word_t& dict, std::ofstream& file)
{
  for (auto&& translation : dict)
  {
    fileLink(translation, file);
  }
}

void cheshkovskiy::fileLink(const word_t::value_type& translation, std::ofstream& file)
{
  file.fill('.');
  file << std::setiosflags(std::ios::left) << std::setw(40) << translation.first << std::resetiosflags(std::ios::left);
  fileNumList(translation.second, file);
  file.fill(' ');
  file << '\n';
}

void cheshkovskiy::fileNumList(const num_set_t& list, std::ofstream& file)
{
  file << '[';
  bool isFirst = true;
  for (auto&& num : list)
  {
    if (!isFirst)
    {
      file << " ";
    }
    else
    {
      isFirst = false;
    }
    file << num;
  }
  file << ']';
}
