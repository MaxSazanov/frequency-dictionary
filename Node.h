#ifndef NODE_H
#define NODE_H

namespace List
{
  template < class T >
  struct Node
  {
    T data_;
    Node* next_;

    explicit Node(const T& newData) :
      data_(newData),
      next_(nullptr)
    {}
  };
}

#endif //NODE_H
