#include <iostream>
#include "FrequencyDictionary.h"
#include "Pair.h"

void FrequencyDictionary::getThreeMostFrequent(std::ostream& out)
{
  auto begin = this->begin();
  Pair<Word, int> first{"", -1};
  Pair<Word, int> second{"", -1};
  Pair<Word, int> third{"", -1};

  for (Pair< Word, int >& pair : *this)
  {
    if (pair.value_ > first.value_)
    {
      third = second;
      second = first;
      first = pair;
    }
    else if (pair.value_ > second.value_)
    {
      third = second;
      second = pair;
    }
    else if (pair.value_ > third.value_)
    {
      third = pair;
    }
  }

  if (first.value_ < 0 || second.value_ < 0 || third.value_ < 0)
  {
    throw std::logic_error("INSUFFICIENT_DICTIONARY_SIZE");
  }
  out << first.key_ << ' ' << second.key_ << ' ' << third.key_;
}

FrequencyDictionary::FrequencyDictionary(std::size_t capacity) :
  HashTable(capacity)
{}