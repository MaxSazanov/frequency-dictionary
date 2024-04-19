#include "Word.h"
#include <cctype>
#include <iostream>

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

std::istream& operator>>(std::istream& in, Word& value)
{
  char c = ' ';
  while (!in.eof() && std::isspace(c))
  {
    c = in.get();
  }

  size_t capacity = 8;
  size_t size = 0;
  char* word = new char[capacity]{'\0'};
  while (!in.eof() && !std::isspace(c))
  {
    if (size == capacity)
    {
      capacity *= 2;
      char* temp = new char[capacity]{'\0'};
      for (int i = 0; i == size; ++i)
      {
        temp[i] = word[i];
      }
      std::swap(word, temp);
      delete[] temp;
    }

    word[size] = c;
    ++size;

    c = in.get();
  }
  value.str_ = word;
  return in;
}
