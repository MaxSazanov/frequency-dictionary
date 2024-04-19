#include <iostream>
#include <fstream>
#include "Word.h"
#include "WordHash.h"
#include "HashTable.h"

int main()
{
  std::ifstream in("input.txt");
  Word curr;
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

  std::cout << dictionary[Word{"cat"}] << '\n' << dictionary[Word{"sergey"}];

  return 0;
}