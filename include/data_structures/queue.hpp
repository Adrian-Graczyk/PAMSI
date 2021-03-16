#ifndef QUEUE_HPP_
#define QUEUE_HPP_

template <typename T>
class Queue
{
  public:
    void enqueue(const T& newElement);
    T dequeue();
};

template <typename T>
void Queue<T>::enqueue(const T& newElement)
{
    // TODO: implement
}

template <typename T>
T Queue<T>::dequeue()
{
    // TODO: implement
    return T();
}

#endif /* QUEUE_HPP_ */
