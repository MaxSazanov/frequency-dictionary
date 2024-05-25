#ifndef FREQUENCY_DICTIONARY_HPP
#define FREQUENCY_DICTIONARY_HPP

#include "HashTable.h"
#include "Word.h"
#include "WordHash.h"

using namespace Table;

class FrequencyDictionary
{
public:
  explicit FrequencyDictionary(std::size_t capacity);
  FrequencyDictionary(const FrequencyDictionary& other);
  FrequencyDictionary(FrequencyDictionary&& other) noexcept;
  ~FrequencyDictionary() = default;

  FrequencyDictionary& operator=(const FrequencyDictionary& other);
  FrequencyDictionary& operator=(FrequencyDictionary&& other) noexcept;

  void getThreeMostFrequent(std::ostream& out = std::cout);
  void insert(const Word& word);
  bool erase(const Word& word);
  int& operator[](const Word& word);

  using iterator = HashTableIterator< Word, int, WordHash >;
  using const_iterator = HashTableIterator< Word, const int, WordHash >;

  iterator begin();
  iterator end();

  const_iterator cbegin() const;
  const_iterator cend() const;

private:
  HashTable< Word, int, WordHash > table_;
};

#endif //FREQUENCY_DICTIONARY_HPP