#ifndef PRIORITY_QUEUE_HPP_
#define PRIORITY_QUEUE_HPP_
#include "list.hpp"

template <typename T>
class PriorityQueue
{
  public:
    void enqueue(const T& newElement, int priority);
    T dequeue();
    int findIndex(int priority);
     void display();

  struct Priodata
  {
    int priority=0;
    T data;
  

       bool operator==(const Priodata& other) const {return this->data==other.data;};
  };

  List<Priodata> list;

};

template <typename T>
void PriorityQueue<T>::display()
{
  auto temp = list.head;

  std::cout<<"lista:"<<std::endl;
  while (temp->previous)
  {
  std::cout<<temp->value.data<<std::endl;
  temp=temp->previous;
  }
  std::cout<<temp->value.data<<std::endl;
}



template <typename T>
void PriorityQueue<T>::enqueue(const T& newElement, int priority)
{
  int index = findIndex(priority);
  list.insert(Priodata{priority , newElement},index);
}

template <typename T>
T PriorityQueue<T>::dequeue()
{
  auto temp = list.head->value;
  list.remove(temp);
  return temp.data;
}

template <typename T>
int PriorityQueue<T>::findIndex(int priority)
{
  int i = 0;
  auto temp = list.head;
  if(list.number==0)
  return 0;
  else
  {
    for(i;temp->value.priority>priority;i++)
    {
    if(temp->previous!=nullptr)
    {
    temp=temp->previous;
    }
    else
    return ++i;
    }
  }
  return i;
}

#endif /* PRIORITY_QUEUE_HPP_ */
