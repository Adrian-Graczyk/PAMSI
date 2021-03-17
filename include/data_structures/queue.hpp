#ifndef QUEUE_HPP_
#define QUEUE_HPP_
#include "list.hpp"

template <typename T>
class Queue
{
  public:
    List<T> list;
    void enqueue(const T& newElement);
    T dequeue();
};

template <typename T>
void Queue<T>::enqueue(const T& newElement)
{
    list.pushBack(newElement);
}

template <typename T>
T Queue<T>::dequeue()
{
    T value = list.head->value;
    list.remove(value);
    return value;
}

#endif /* QUEUE_HPP_ */
