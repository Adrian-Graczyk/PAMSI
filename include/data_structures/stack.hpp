#ifndef STACK_HPP_
#define STACK_HPP_
#include "list.hpp"

template <typename T>
class Stack
{
  public:
    List<T> list;
    void push(const T& newElement);
    T pop();
};

template <typename T>
void Stack<T>::push(const T& newElement)
{
  list.pushFront(newElement);
}

template <typename T>
T Stack<T>::pop()
{
  T value = list.head->value;
  list.remove(value);
  return value;
}

#endif /* STACK_HPP_ */
