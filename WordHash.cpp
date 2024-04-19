#include "Word.h"
#include "WordHash.h"

std::size_t WordHash::operator()(const Word& word) const noexcept
{
  std::size_t hash = 0;
  for (int i = 0; i < word.str_[i] != '\0'; ++i)
  {
    hash += word.str_[i];
  }
  return hash;
}