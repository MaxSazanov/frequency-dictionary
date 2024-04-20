#ifndef PAIR_H
#define PAIR_H

namespace Table
{
  template < class Key, class Value >
  struct Pair
  {
    Key key_;
    Value value_;

    bool operator==(const Pair& other) const;
  };

  template < class Key, class Value >
  bool Pair<Key, Value>::operator==(const Pair& other) const
  {
    return key_ == other.key_;
  }
}

#endif //PAIR_H