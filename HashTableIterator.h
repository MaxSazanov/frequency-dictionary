#ifndef HASHTABLE_ITERATOR_H
#define HASHTABLE_ITERATOR_H

#include <iterator>
#include "LinkedListIterator.h"

using namespace List;

namespace Table
{
  template < class Key, class Value, class Hash>
  class HashTable;

  template< class Key, class Value, class Hash = std::hash< Key > >
  class HashTableIterator: public std::iterator<std::forward_iterator_tag, Value>
  {
    friend class HashTable< Key, Value, Hash >;
  public:
    HashTableIterator(const HashTableIterator& it);

    bool operator!=(const HashTableIterator& other) const;
    bool operator==(const HashTableIterator& other) const;
    Pair<Key, Value>& operator*() const;

    HashTableIterator& operator++();
  private:
    using Bucket = LinkedList<Pair<Key, Value>>;

    Bucket* bucket_;
    Bucket* end_;
    Bucket::iterator listIterator_ = bucket_->begin();

    explicit HashTableIterator(Bucket* bucket, Bucket* end);
  };

  template< class Key, class Value, class Hash>
  HashTableIterator<Key, Value, Hash>::HashTableIterator(Bucket* bucket, Bucket* end) :
    bucket_(bucket),
    end_(end)
  {
    listIterator_ = bucket->begin();
    if (listIterator_ == bucket_->end() && bucket_ != end_)
    {
      ++(*this);
    }
  }

  template< class Key, class Value, class Hash>
  HashTableIterator<Key, Value, Hash>::HashTableIterator(const HashTableIterator& it) :
    bucket_(it.bucket_),
    listIterator_(it.listIterator_)
  {}

  template<class Key, class Value, class Hash>
  bool HashTableIterator<Key, Value, Hash>::operator==(const HashTableIterator& other) const
  {
    return bucket_ == other.bucket_ && listIterator_ == other.listIterator_;
  }

  template< class Key, class Value, class Hash>
  bool HashTableIterator<Key, Value, Hash>::operator!=(const HashTableIterator& other) const
  {
    return !(*this == other);
  }

  template< class Key, class Value, class Hash>
  Pair<Key, Value>& HashTableIterator<Key, Value, Hash>::operator*() const
  {
    return *listIterator_;
  }

  template< class Key, class Value, class Hash>
  HashTableIterator<Key, Value, Hash>& HashTableIterator<Key, Value, Hash>::operator++()
  {
    if (listIterator_ != bucket_->end())
    {
      ++listIterator_;
    }
    while (listIterator_ == bucket_->end() && bucket_ != end_)
    {
      ++bucket_;
      listIterator_ = bucket_->begin();
    }
    return *this;
  }
}

#endif //HASHTABLE_ITERATOR_H