#include <iostream>
#include <fstream>
#include "Word.h"
#include "WordHash.h"
#include "HashTable.h"

using namespace Table;

int main()
{
  std::ifstream in("input.txt");
  Word curr{};
  HashTable< Word, int, WordHash > frequencyDictionary(100);

  if (in.is_open())
  {
    while (!in.eof())
    {
      in >> curr;
      frequencyDictionary[curr] += 1;
    }
  }

  HashTable< Word, int, WordHash > frequencyDictionary2(frequencyDictionary);
  in.close();

  std::cout << frequencyDictionary.insert(Word{"cata"}, 0).second << '\n';

  for (Pair< Word, int >& pair : frequencyDictionary)
  {
    std::cout << pair.key_.str_ << '\n';
  }

  std::cout << frequencyDictionary2[Word{"cata"}] << '\n' << frequencyDictionary[Word{"sergey"}];

  return 0;
}
