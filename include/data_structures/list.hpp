#ifndef LIST_HPP_
#define LIST_HPP_

#include <memory>

template <typename T>
class List
{  
  public:
    class Node
    {
    public:
    T value;
    std::shared_ptr<Node> previous=nullptr;
    std::shared_ptr<Node> next=nullptr;
    };

    int number = 0;
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;

    class Iterator
    {
      private:
      std::shared_ptr<Node> currentNode;
      public:
        using difference_type = long;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::random_access_iterator_tag;

        Iterator(std::shared_ptr<Node> node = nullptr):currentNode{node} {};

        Iterator operator++();
        Iterator operator--();
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        bool operator>(const Iterator& other) const;
        bool operator<(const Iterator& other) const;
        difference_type operator-(const Iterator& other) const;
        Iterator operator+(difference_type diff) const;
        Iterator operator-(difference_type diff) const;
        Iterator operator[](std::size_t i);
        T& operator*();
    };

    class ConstIterator
    {
      private:
      std::shared_ptr<Node> currentNode;
      public:
      using difference_type = long;
      using value_type = T;
      using pointer = const T*;
      using reference = const T&;
      using iterator_category = std::random_access_iterator_tag;

      ConstIterator(std::shared_ptr<Node> node = nullptr):currentNode{node} {};

      ConstIterator operator++();
      ConstIterator operator--();
      bool operator==(const ConstIterator& other) const;
      bool operator!=(const ConstIterator& other) const;
      bool operator>(const ConstIterator& other) const;
      bool operator<(const ConstIterator& other) const;
      difference_type operator-(const ConstIterator& other) const;
      ConstIterator operator+(difference_type diff) const;
      ConstIterator operator-(difference_type diff) const;
      ConstIterator operator[](std::size_t i);
      const T& operator*();
    };

    void pushBack(const T& newElement);
    void pushFront(const T& newElement);
    void insert(const T& newElement, int index);
    void insert_priority(const T& newElement, int priority);
    void remove(const T& element);
    void display();
    ~List();

    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;
    T& operator[](int index);
    
};

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++()
{
  currentNode=currentNode->next;
  return currentNode;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--()
{
  currentNode=currentNode->previous;
  return currentNode;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const
{
  return this->currentNode==other.currentNode;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const
{
  return !(*this==other);
}

template <typename T>
bool List<T>::Iterator::operator>(const Iterator& other) const
{
  Iterator temp{this->currentNode};
  for(; temp.currentNode != nullptr; ++temp)
  {
    if(temp.currentNode == other.currentNode)
    return false;
  }
  return true;
}

template <typename T>
bool List<T>::Iterator::operator<(const Iterator& other) const
{
  Iterator temp{this->currentNode};
  for(; temp.currentNode != nullptr; ++temp)
  {
    if(temp.currentNode == other.currentNode)
    return true;
  }
  return false;
}

template <typename T>
typename List<T>::Iterator::difference_type List<T>::Iterator::operator-(const Iterator& other) const
{
  int i=0;
  Iterator temp{this->currentNode};
  for(; temp.currentNode != nullptr; ++temp)
  {
    if(temp.currentNode == other.currentNode)
    return i;
    i++;
  }
  return i;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator+(difference_type diff) const
{
  Iterator temp{this->currentNode};
  for(int i=0; i<diff; ++i)
  {
    temp.currentNode=temp.currentNode->next;
  }
  return temp;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator-(difference_type diff) const
{
  Iterator temp{this->currentNode};
  for(int i=0; i<diff; ++i)
  {
    temp.currentNode=temp.currentNode->previous;
  }
  return temp;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator[](std::size_t i)
{  
  Iterator temp{this->currentNode};
  for(int j=0; j<i; ++j)
  {
    temp.currentNode=temp.currentNode->next;
  }
  return temp;
}

template <typename T>
T& List<T>::Iterator::operator*()
{
  return currentNode->value;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++()
{
  currentNode=currentNode->next;
  return currentNode;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--()
{
  currentNode=currentNode->previous;
  return currentNode;
}

template <typename T>
bool List<T>::ConstIterator::operator==(const ConstIterator& other) const
{
  return this->currentNode==other.currentNode;
}

template <typename T>
bool List<T>::ConstIterator::operator!=(const ConstIterator& other) const
{
  return !(*this==other);
}

template <typename T>
bool List<T>::ConstIterator::operator>(const ConstIterator& other) const
{
  ConstIterator temp{this->currentNode};
  for(; temp.currentNode != nullptr; ++temp)
  {
    if(temp.currentNode == other.currentNode)
    return false;
  }
  return true;
}

template <typename T>
bool List<T>::ConstIterator::operator<(const ConstIterator& other) const
{
  ConstIterator temp{this->currentNode};
  for(; temp.currentNode != nullptr; ++temp)
  {
    if(temp.currentNode == other.currentNode)
    return true;
  }
  return false;
}

template <typename T>
typename List<T>::ConstIterator::difference_type List<T>::ConstIterator::operator-(const ConstIterator& other) const
{
  int i=0;
  ConstIterator temp{this->currentNode};
  for(; temp.currentNode != nullptr; ++temp)
  {
    if(temp.currentNode == other.currentNode)
    return i;
    i++;
  }
  return i;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator+(difference_type diff) const
{
  ConstIterator temp{this->currentNode};
  for(int i=0; i<diff; ++i)
  {
    temp.currentNode=temp.currentNode->next;
  }
  return temp;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator-(difference_type diff) const
{
  ConstIterator temp{this->currentNode};
  for(int i=0; i<diff; ++i)
  {
    temp.currentNode=temp.currentNode->previous;
  }
  return temp;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator[](std::size_t i)
{
  ConstIterator temp{this->currentNode};
  for(int j=0; j<i; ++j)
  {
    temp.currentNode=temp.currentNode->next;
  }
  return temp;
}

template <typename T>
const T& List<T>::ConstIterator::operator*()
{
  return currentNode->value;
}

template <typename T>
void List<T>::display()
{
  auto temp = head;

  std::cout<<"lista:"<<std::endl;
  while (temp->next)
  {
  std::cout<<temp->value<<std::endl;
  temp=temp->next;
  }
  std::cout<<temp->value<<std::endl;
}

template <typename T>
void List<T>::pushBack(const T& newElement)
{
  std::shared_ptr<Node> new_node{new Node};
  new_node->value=newElement;

  if(number==0)
  {
    head=new_node;
    tail=new_node;
  }
  else
  {
    new_node->next=nullptr;
    new_node->previous=tail;
    tail->next=new_node;
    tail=new_node;
  }
  number++;
}

template <typename T>
void List<T>::pushFront(const T& newElement)
{
  std::shared_ptr<Node> new_node{new Node};
  new_node->value=newElement;

  if(number==0)
  {
    head=new_node;
    tail=new_node;
  }
  else
  {
    new_node->next=head;
    new_node->previous=nullptr;
    head->previous=new_node;
    head=new_node;
  }
  number++;
}
  
template <typename T>
void List<T>::insert(const T& newElement, int index)
{
  if(index == 0) {pushFront(newElement);}

  else if(index == number){pushBack(newElement);}
  
  else
  {
    std::shared_ptr<Node> new_node{new Node};
    new_node->value=newElement;
    auto temp = head;

    for(int i=0; i<index; i++)
    {
      if(temp->next!=nullptr)
      temp=temp->next;
    }
  
    new_node->next=temp;
    temp->previous->next=new_node;
    new_node->previous=temp->previous;
    temp->previous=new_node;

    number++;
  }
}

template <typename T>
void List<T>::remove(const T& element)
{
  auto temp = head;

  if(number==0 ||number==1)
  {
    head=nullptr;
    tail=nullptr;
    number=0;
  }
  else
  {
   while(temp->next)
    {
      if(temp->value==element)
      {
        if(temp->next==nullptr)
        {
          temp->previous->next=nullptr;
          tail=temp->previous;
        }
        else if(temp->previous==nullptr)
        {
          temp->next->previous=nullptr;
          head=temp->next;
        }
        else
        {
          temp->next->previous=temp->previous;
          temp->previous->next=temp->next;
        }
        number--;
      }
      temp=temp->next;
    }
    if(temp->value==element)
    {
      head->next=nullptr;
      tail=temp->previous;
      number--;
    }
  }
}

template <typename T>
typename List<T>::Iterator List<T>::begin()
{
  return Iterator{head};
}

template <typename T>
typename List<T>::Iterator List<T>::end()
{
  return Iterator{nullptr};
}

template <typename T>
typename List<T>::ConstIterator List<T>::cbegin() const
{
  return ConstIterator{head};
} 

template <typename T>
typename List<T>::ConstIterator List<T>::cend() const
{
  return ConstIterator(tail);
}

template <typename T>
T& List<T>::operator[](int index)
{
  static T element;
  auto temp = head;
  if(index >= number)
  throw "za duży index - brak tylu elementów na liście";
  else 
  {
    for(int i=0;i<index;i++)
    {
    temp=temp->next;
    }
  
    element=temp->value;
    return element;
  }
}

template <typename T>
List<T>::~List()
{
auto temp = head;
      while(temp)
      {
        temp->previous=nullptr;
        temp=temp->next;
      }
}
#endif /* LIST_HPP_ */
