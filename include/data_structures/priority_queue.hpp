#ifndef PRIORITY_QUEUE_HPP_
#define PRIORITY_QUEUE_HPP_

template <typename T>
class PriorityQueue
{
  public:
    List<T> list;
    void enqueue(const T& newElement, int priority);
    T dequeue();
};


template <typename T>
void PriorityQueue<T>::enqueue(const T& newElement, int priority)
{
  list.insert_priority(newElement,priority);
}

template <typename T>
T PriorityQueue<T>::dequeue()
{
  T value = list.head->value;
  list.remove(value);
  return value;
}

#endif /* PRIORITY_QUEUE_HPP_ */
