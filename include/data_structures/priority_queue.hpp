#ifndef PRIORITY_QUEUE_HPP_
#define PRIORITY_QUEUE_HPP_

template <typename T>
class PriorityQueue
{
  public:
    void enqueue(const T& newElement, int priority);
    T dequeue();
};


template <typename T>
void PriorityQueue<T>::enqueue(const T& newElement, int priority)
{
  // TODO: implement
}

template <typename T>
T PriorityQueue<T>::dequeue()
{
  // TODO: implement
  return T();
}

#endif /* PRIORITY_QUEUE_HPP_ */
