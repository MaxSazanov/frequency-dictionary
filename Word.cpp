#include "Word.h"
#include <cctype>
#include <iostream>
#include "SimpleString.h"

bool Word::operator==(const Word& other) const
{
  std::size_t i = 0;
  for (i; str_[i] != '\0'; ++i)
  {
    if (str_[i] != other.str_[i])
    {
      return false;
    }
  }
  return other.str_[i] == '\0';
}


std::ostream& operator<<(std::ostream& out, Word& word)
{
  out << word.str_;
  return out;
}

std::istream& operator>>(std::istream& in, Word& value)
{
  char c = ' ';
  while (!in.eof() && std::isspace(c))
  {
    c = in.get();
  }

  constexpr std::size_t DEFAULT_CAPACITY = 4;
  SimpleString word(new char[DEFAULT_CAPACITY]{'\0'}, DEFAULT_CAPACITY);
  while (!in.eof() && !std::isspace(c))
  {
    if (std::isalpha(c))
    {
      word.insert(c);
    }
    c = in.get();
  }
  value.str_ = word.str_;
  return in;
}