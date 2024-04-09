#include "command.h"

#include <fstream>
#include <stdexcept>
#include <algorithm>

#include "WorkType.h"

namespace
{
  size_t getCountOfWords(const std::string& str)
  {
    return std::count(str.begin(), str.end(), ' ') + 1;
  }
}

void cheshkovskiy::newTree(std::string commands, tree_t& dicts)
{
  if (getCountOfWords(commands) != 1)
  {
    throw std::logic_error("<INVALID_ARGUMENTS>");
  }
  std::string newDictName = getWord(commands, false);
  if (dicts.count(newDictName))
  {
    throw std::logic_error("<DICTIONARY_ALREADY_EXISTS>");
  }
  dicts[newDictName] = {};
  std::get< 1 >(dicts[newDictName]) = "";
  std::get< 2 >(dicts[newDictName]) = 0;
}

void cheshkovskiy::add(std::string commands, tree_t& dicts)
{
  if (getCountOfWords(commands) != 2)
  {
    throw std::logic_error("<INVALID_ARGUMENTS>");
  }
  std::string oldDictName = getWord(commands, false);
  std::string fileName = getWord(commands, true);
  std::ifstream file(fileName);
  if (!file.is_open())
  {
    throw std::logic_error("<ERROR_OPEN_FILE>");
  }
  word_t& dict = std::get< 0 >(dicts[oldDictName]);
  if ((!dict.empty()) && (std::get< 1 >(dicts[oldDictName]).empty()))
  {
    throw std::logic_error("<RECORDING_IS_NOT_POSSIBLE>");
  }
  std::string line;
  num_set_t newList;
  size_t numLine = std::get< 2 >(dicts[oldDictName]);
  while (!file.eof())
  {
    numLine++;
    std::getline(file, line);
    std::get< 1 >(dicts[oldDictName]) += line + '\n';
    std::get< 2 >(dicts[oldDictName]) += 1;
    while (!line.empty())
    {
      std::string word;
      while ((word == "") && (!line.empty()))
      {
        word = getWord(line, false);
      }
      if (word != "")
      {
        cheshkovskiy::word_t::iterator it = dict.find(word);
        if (it != dict.end())
        {
          dict[word].insert(numLine);
        }
        else
        {
          num_set_t numSet;
          numSet.insert(numLine);
          std::pair< const std::string, num_set_t > pair{ word, numSet };
          dict.insert(pair);
        }
      }
    }
  }
}

void cheshkovskiy::addT(std::string commands, tree_t& dicts)
{
  if (getCountOfWords(commands) != 2)
  {
    throw std::logic_error("<INVALID_ARGUMENTS>");
  }
  std::string oldDictName1 = getWord(commands, false);
  std::string oldDictName2 = getWord(commands, false);
  if (!dicts.count(oldDictName1) && !dicts.count(oldDictName2))
  {
    throw std::logic_error("<INVALID_NAME>\n");
  }
  std::tuple< word_t, std::string, size_t >& dict1 = dicts.at(oldDictName1);
  if ((!std::get< 0 >(dict1).empty()) && (std::get< 1 >(dict1).empty()))
  {
    throw std::logic_error("<RECORDING_IS_NOT_POSSIBLE>");
  }
  bool done = false;
  std::tuple< word_t, std::string, size_t >& dict2 = dicts.at(oldDictName2);
  word_t::iterator it1 = std::get< 0 >(dict1).begin();
  word_t::iterator it2 = std::get< 0 >(dict2).begin();
  word_t::iterator end1 = std::get< 0 >(dict1).end();
  word_t::iterator end2 = std::get< 0 >(dict2).end();
  word_t dict = std::get< 0 >(dict1);
  while (it1 != end1 || it2 != end2)
  {
    if (it1 == end1)
    {
      while (it2 != end2)
      {
        dict[it2->first] = it2->second;
        if (!done)
        {
          done = true;
        }
        it2++;
      }
      continue;
    }
    if (it2 == end2)
    {
      break;
    }
    std::string word1 = it1->first;
    std::string word2 = it2->first;
    if (word1 == word2)
    {
      it1++;
      it2++;
      continue;
    }
    if (word1 < word2)
    {
      it1++;
    }
    else
    {
      dict[it2->first] = it2->second;
      if (!done)
      {
        done = true;
      }
      it2++;
    }
  }
  if (done)
  {
    std::get< 0 >(dict1) = dict;
    std::get< 1 >(dict1) = "";
    std::get< 2 >(dict1) = 0;
  }
}

void cheshkovskiy::addLine(std::string commands, tree_t& dicts)
{
  if (getCountOfWords(commands) < 2)
  {
    throw std::logic_error("<INVALID_ARGUMENTS>");
  }
  std::string oldDictName = getWord(commands, false);
  if (!dicts.count(oldDictName))
  {
    throw std::logic_error("<INVALID_NAME>");
  }
  word_t& dict = std::get< 0 >(dicts[oldDictName]);
  if ((!std::get< 0 >(dicts[oldDictName]).empty()) && (std::get< 1 >(dicts[oldDictName]).empty()))
  {
    throw std::logic_error("<RECORDING_IS_NOT_POSSIBLE>");
  }
  std::get< 1 >(dicts[oldDictName]) += commands + '\n';
  std::get< 2 >(dicts[oldDictName]) += 1;
  size_t numLine = std::get< 2 >(dicts[oldDictName]);
  while (!commands.empty())
  {
    std::string word = getWord(commands, false);
    if (word != "")
    {
      cheshkovskiy::word_t::iterator it = dict.find(word);
      if (it != dict.end())
      {
        dict[word].insert(numLine);
      }
      else
      {
        num_set_t numSet;
        numSet.insert(numLine);
        std::pair< const std::string, num_set_t > pair{ word, numSet };
        dict.insert(pair);
      }
    }
  }
}

void cheshkovskiy::intersection(std::string commands, tree_t& dicts)
{
  if (getCountOfWords(commands) != 3)
  {
    throw std::logic_error("<INVALID_ARGUMENTS>");
  }
  std::string newDictName = getWord(commands, false);
  std::string oldDictName = getWord(commands, false);
  std::string oldDictName2 = getWord(commands, false);
  if (!dicts.count(oldDictName) || !dicts.count(oldDictName2))
  {
    throw std::logic_error("<INVALID_NAME>");
  }
  word_t::iterator it1 = std::get< 0 >(dicts[oldDictName]).begin();
  word_t::iterator it2 = std::get< 0 >(dicts[oldDictName2]).begin();
  word_t::iterator end1 = std::get< 0 >(dicts[oldDictName]).end();
  word_t::iterator end2 = std::get< 0 >(dicts[oldDictName2]).end();
  word_t dict;
  while (it1 != end1 || it2 != end2)
  {
    if ((it1 == end1) || (it2 == end2))
    {
      break;
    }
    std::string word1 = it1->first;
    std::string word2 = it2->first;
    if (word1 == word2)
    {
      size_t maxLineNum;

      if (std::get< 2 >(dicts[oldDictName]) < std::get< 2 >(dicts[oldDictName2]))
      {
        maxLineNum = std::get< 2 >(dicts[oldDictName2]);
      }
      else
      {
        maxLineNum = std::get< 2 >(dicts[oldDictName]);
      }

      for (int i = 1; i <= maxLineNum; i++)
      {
        num_set_t::iterator itNum1 = it1->second.find(i);
        num_set_t::iterator itNum2 = it2->second.find(i);
        if ((itNum1 != it1->second.end()) && (itNum2 != it2->second.end()))
        {
          dict[word1].insert(i);
        }
      }
      it1++;
      it2++;
      continue;
    }
    if (word1 < word2)
    {
      it1++;
    }
    else
    {
      it2++;
    }
  }
  std::get< 0 >(dicts[newDictName]) = dict;
  std::get< 1 >(dicts[newDictName]) = "";
  std::get< 2 >(dicts[newDictName]) = 0;
}

void cheshkovskiy::subtraction(std::string commands, tree_t& dicts)
{
  if (getCountOfWords(commands) != 2)
  {
    throw std::logic_error("<INVALID_ARGUMENTS>");
  }
  std::string oldDictName1 = getWord(commands, false);
  std::string oldDictName2 = getWord(commands, false);
  if (!dicts.count(oldDictName1) || !dicts.count(oldDictName2))
  {
    throw std::logic_error("<INVALID_NAME>");
  }
  bool done = false;
  std::tuple< word_t, std::string, size_t >& dict1 = dicts.at(oldDictName1);
  std::tuple< word_t, std::string, size_t >& dict2 = dicts.at(oldDictName2);
  word_t::iterator it1 = std::get< 0 >(dict1).begin();
  word_t::iterator it2 = std::get< 0 >(dict2).begin();
  word_t::iterator end1 = std::get< 0 >(dict1).end();
  word_t::iterator end2 = std::get< 0 >(dict2).end();
  word_t dict = std::get< 0 >(dicts[oldDictName1]);
  while (it1 != end1 || it2 != end2)
  {
    if ((it1 == end1) || (it2 == end2))
    {
      break;
    }
    std::string word1 = it1->first;
    std::string word2 = it2->first;
    if (word1 == word2)
    {
      it1++;
      it2++;
      std::get< 0 >(dict1).erase(word1);
      if (!done)
      {
        done = true;
      }
      continue;
    }
    if (word1 < word2)
    {
      it1++;
    }
    else
    {
      it2++;
    }
  }
  if (done)
  {
    std::get< 1 >(dict1) = "";
    std::get< 2 >(dict1) = 0;
  }
}

void cheshkovskiy::remove(std::string commands, tree_t& dicts)
{
  if (getCountOfWords(commands) != 1)
  {
    throw std::logic_error("<INVALID_ARGUMENTS>");
  }
  std::string oldDictName = getWord(commands, false);
  if (!dicts.count(oldDictName))
  {
    throw std::logic_error("<INVALID_NAME>");
  }
  dicts.erase(oldDictName);
}

void cheshkovskiy::deleteWord(std::string commands, tree_t& dicts)
{
  if (getCountOfWords(commands) != 2)
  {
    throw std::logic_error("<INVALID_ARGUMENTS>");
  }
  std::string oldDictName = getWord(commands, false);
  if (!dicts.count(oldDictName))
  {
    throw std::logic_error("<INVALID_NAME>");
  }
  std::string word = getWord(commands, false);
  if (std::get< 0 >(dicts[oldDictName]).find(word) == std::get< 0 >(dicts[oldDictName]).end())
  {
    throw std::logic_error("<INVALID_WORD>");
  }
  std::get< 0 >(dicts[oldDictName]).erase(word);
  std::get< 1 >(dicts[oldDictName]) = "";
  std::get< 2 >(dicts[oldDictName]) = 0;
}

void cheshkovskiy::copy(std::string commands, tree_t& dicts)
{
  if (getCountOfWords(commands) != 2)
  {
    throw std::logic_error("<INVALID_ARGUMENTS>");
  }
  std::string oldDictName1 = getWord(commands, false);
  std::string oldDictName2 = getWord(commands, false);
  if (!dicts.count(oldDictName1) || !dicts.count(oldDictName2))
  {
    throw std::logic_error("<INVALID_NAME>");
  }
  dicts.at(oldDictName1) = dicts.at(oldDictName2);
}

void cheshkovskiy::search(std::string commands, tree_t& dicts, std::ostream& out)
{
  if (getCountOfWords(commands) != 2)
  {
    throw std::logic_error("<INVALID_ARGUMENTS>");
  }
  std::string newDictName = getWord(commands, false);
  if (!dicts.count(newDictName))
  {
    throw std::logic_error("<INVALID_NAME>");
  }
  std::string word = getWord(commands, false);
  cheshkovskiy::word_t& dict = std::get< 0 >(dicts[newDictName]);
  cheshkovskiy::word_t::iterator it = dict.find(word);
  if (it == dict.end())
  {
    throw std::logic_error("<INVALID_WORD>");
  }
  else
  {
    outLink(*it, out);
  }
}

void cheshkovskiy::erase(std::string commands, tree_t& dicts)
{
  if (getCountOfWords(commands) != 2)
  {
    throw std::logic_error("<INVALID_ARGUMENTS>");
  }
  std::string dictName = getWord(commands, false);
  if (!dicts.count(dictName))
  {
    throw std::logic_error("<INVALID_NAME>");
  }
  size_t lineNum = getNumber(commands);
  cheshkovskiy::word_t& dict = std::get< 0 >(dicts[dictName]);
  if (!lineNum)
  {
    std::logic_error("<LINE_NUMBER_EQUAL_ZERO>");
  }
  std::string& text = std::get< 1 >(dicts[dictName]);
  std::string line;
  size_t step;
  size_t beginPos = 0;
  for (size_t i = 1; i < lineNum; i++)
  {
    step = 0;
    while (text[beginPos + step] != '\n')
    {
      step++;
    }
    beginPos += step + 1;
  }
  step = 0;
  while (text[beginPos + step] != '\n')
  {
    step++;
  }
  line = text.substr(beginPos, step);
  text.erase(beginPos, step + 1);
  size_t max = std::get< 2 >(dicts[dictName]);
  std::get< 2 >(dicts[dictName]) -= 1;
  std::string word;
  while (!line.empty())
  {
    word = getWord(line, false);
    dict[word].erase(lineNum);
    if (dict.at(word).empty())
    {
      dict.erase(word);
    }
  }
  word_t::iterator it = std::get< 0 >(dicts[dictName]).begin();
  word_t::iterator end = std::get< 0 >(dicts[dictName]).end();
  for (it; it != end; it++)
  {
    for (size_t l = 1; l <= max; l++)
    {
      num_set_t::iterator itNum = it->second.find(l);
      if ((itNum != it->second.end()) && (*itNum > lineNum))
      {
        it->second.erase(l);
        it->second.insert(l - 1);
      }
    }
  }
}

void cheshkovskiy::clear(std::string commands, tree_t& dicts)
{
  if (getCountOfWords(commands) != 1)
  {
    throw std::logic_error("<INVALID_ARGUMENTS>");
  }
  std::string dictName = getWord(commands, false);
  if (!dicts.count(dictName))
  {
    throw std::logic_error("<INVALID_NAME>");
  }
  std::get< 0 >(dicts[dictName]).clear();
  std::get< 1 >(dicts[dictName]) = "";
  std::get< 2 >(dicts[dictName]) = 0;
}

void cheshkovskiy::print(std::string commands, tree_t& dicts, std::ostream& out)
{
  std::string dictName = getWord(commands, false);
  if (!dicts.count(dictName))
  {
    throw std::logic_error("<INVALID_NAME>");
  }
  std::tuple< word_t, std::string, size_t >& dict = dicts.at(dictName);
  if (std::get< 0 >(dict).empty())
  {
    throw std::logic_error("<DICTIONARY_EMPTY>");
  }
  outDict(std::get< 0 >(dict), out);
}

void cheshkovskiy::split(std::string commands, tree_t& dicts, std::ostream& out)
{
  if (getCountOfWords(commands) != 1)
  {
    throw std::logic_error("<INVALID_ARGUMENTS>");
  }
  std::string dictName = getWord(commands, false);
  if (!dicts.count(dictName))
  {
    throw std::logic_error("<INVALID_NAME>");
  }
  if (std::get< 1 >(dicts.at(dictName)).empty())
  {
    throw std::logic_error("<NO_TEXT>");
  }
  outText(std::get< 1 >(dicts.at(dictName)), std::get< 2 >(dicts.at(dictName)), out);
}

void cheshkovskiy::create(std::string commands, tree_t& dicts)
{
  if (getCountOfWords(commands) != 2)
  {
    throw std::logic_error("<INVALID_ARGUMENTS>");
  }
  std::string dictName = getWord(commands, false);
  if (!dicts.count(dictName))
  {
    throw std::logic_error("<INVALID_NAME>");
  }
  if (std::get< 0 >(dicts.at(dictName)).empty())
  {
    throw std::logic_error("<DICTIONARY_EMPTY>");
  }
  std::string fileName = getWord(commands, true);
  std::ofstream file(fileName);
  fileDict(std::get< 0 >(dicts.at(dictName)), file);
}
