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
  HashTable< Word, int, WordHash > dictionary(5);
  if (in.is_open())
  {
    while (!in.eof())
    {
      in >> curr;
      dictionary[curr] += 1;
    }
  }
  in.close();

  std::cout << dictionary.insert(Word{"cata"}, 0).second << '\n';

  for (Pair<Word, int>& pair : dictionary)
  {
    std::cout << pair.key_.str_ << '\n';
  }

  std::cout << dictionary[Word{"cata"}] << '\n' << dictionary[Word{"sergey"}];

  return 0;
}
