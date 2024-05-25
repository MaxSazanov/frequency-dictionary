#include <iostream>
#include "FrequencyDictionary.h"
#include "Pair.h"

void FrequencyDictionary::getThreeMostFrequent(std::ostream& out)
{
  Pair<Word, int> first{"", -1};
  Pair<Word, int> second{"", -1};
  Pair<Word, int> third{"", -1};

  for (Pair< Word, int >& pair : table_)
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

FrequencyDictionary::FrequencyDictionary(std::size_t capacity):
  table_(capacity)
{}

void FrequencyDictionary::insert(const Word& word)
{
  table_[word] += 1;
}

int& FrequencyDictionary::operator[](const Word& word)
{
  return table_[word];
}

FrequencyDictionary::iterator FrequencyDictionary::begin()
{
  return table_.begin();
}

FrequencyDictionary::iterator FrequencyDictionary::end()
{
  return table_.end();
}

bool FrequencyDictionary::erase(const Word& word)
{
  return table_.erase(word);
}

FrequencyDictionary::FrequencyDictionary(const FrequencyDictionary& other):
  table_()
{
  HashTable< Word, int, WordHash > temp(other.table_);
  std::swap(table_, temp);
}

FrequencyDictionary::FrequencyDictionary(FrequencyDictionary&& other) noexcept:
  table_(std::move(other.table_))
{}

FrequencyDictionary& FrequencyDictionary::operator=(const FrequencyDictionary& other)
{
  if (this != &other)
  {
    HashTable< Word, int, WordHash > temp(other.table_);
    std::swap(table_, temp);
  }
  return *this;
}

FrequencyDictionary& FrequencyDictionary::operator=(FrequencyDictionary&& other) noexcept
{
  if (this != &other)
  {
    table_ = std::move(other.table_);
  }
  return *this;
}