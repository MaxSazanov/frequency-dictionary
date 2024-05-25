#ifndef HASHTABLE_ITERATOR_H
#define HASHTABLE_ITERATOR_H

#include <iterator>
#include "LinkedListIterator.h"

using namespace List;

namespace Table
{
  template < class Key, class Value, class Hash >
  class HashTable;

  template< class Key, class Value, class Hash = std::hash< Key > >
  class HashTableIterator: public std::iterator< std::forward_iterator_tag, Value >
  {
    friend class HashTable< Key, Value, Hash >;
  public:
    HashTableIterator(const HashTableIterator& other);
    HashTableIterator& operator=(const HashTableIterator& other);

    bool operator!=(const HashTableIterator& other) const;
    bool operator==(const HashTableIterator& other) const;

    using Value_type =  Pair< Key, Value >;
    using Reference = Value_type&;
    using Pointer = Value_type*;

    Reference operator*() const;
    Pointer operator->() const;
    HashTableIterator& operator++();
    HashTableIterator operator++(int);
  private:
    using Bucket = LinkedList< Pair< Key, Value > >;

    Bucket* bucket_;
    Bucket* end_;
    Bucket::iterator listIterator_ = bucket_->begin();

    explicit HashTableIterator(Bucket* bucket, Bucket* end);
    explicit HashTableIterator(Bucket* bucket, Bucket* end, LinkedListIterator< Pair< Key, Value > > iterator);
  };

  template<class Key, class Value, class Hash>
  HashTableIterator<Key, Value, Hash>::HashTableIterator(Bucket* bucket, Bucket* end, LinkedListIterator< Pair< Key, Value > > iterator):
    bucket_(bucket),
    end_(end),
    listIterator_(iterator)
  {
    if (listIterator_ == bucket_->end() && bucket_ != end_)
    {
      ++(*this);
    }
  }

  template<class Key, class Value, class Hash>
  HashTableIterator<Key, Value, Hash> HashTableIterator<Key, Value, Hash>::operator++(int)
  {
    HashTableIterator<Key, Value, Hash> temp(*this);
    ++(*this);
    return temp;
  }

  template<class Key, class Value, class Hash>
  HashTableIterator<Key, Value, Hash>::Pointer HashTableIterator<Key, Value, Hash>::operator->() const
  {
    return listIterator_.operator->();
  }

  template<class Key, class Value, class Hash>
  HashTableIterator< Key, Value, Hash >& HashTableIterator<Key, Value, Hash>::operator=(const HashTableIterator& other)
  {
    if (this != &other)
    {
      bucket_ = other.bucket_,
      end_ = other.end_;
      listIterator_ = other.listIterator_;
    }
    return *this;
  }

  template< class Key, class Value, class Hash >
  HashTableIterator< Key, Value, Hash >::HashTableIterator(Bucket* bucket, Bucket* end) :
    bucket_(bucket),
    end_(end)
  {
    listIterator_ = bucket->begin();
    if (listIterator_ == bucket_->end() && bucket_ != end_)
    {
      ++(*this);
    }
  }

  template< class Key, class Value, class Hash >
  HashTableIterator< Key, Value, Hash >::HashTableIterator(const HashTableIterator& other) :
    bucket_(other.bucket_),
    end_(other.end_),
    listIterator_(other.listIterator_)
  {}

  template< class Key, class Value, class Hash >
  bool HashTableIterator< Key, Value, Hash >::operator==(const HashTableIterator& other) const
  {
    return bucket_ == other.bucket_ && listIterator_ == other.listIterator_;
  }

  template< class Key, class Value, class Hash >
  bool HashTableIterator< Key, Value, Hash >::operator!=(const HashTableIterator& other) const
  {
    return !(*this == other);
  }

  template< class Key, class Value, class Hash >
  Pair< Key, Value >& HashTableIterator< Key, Value, Hash >::operator*() const
  {
    return *listIterator_;
  }

  template< class Key, class Value, class Hash >
  HashTableIterator< Key, Value, Hash >& HashTableIterator< Key, Value, Hash >::operator++()
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