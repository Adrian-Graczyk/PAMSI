#ifndef LIST_HPP_
#define LIST_HPP_

#include <memory>

template <typename T>
class List
{ //////
  
  public:
    class Node
    {
    public:
    T value;
    std::shared_ptr<Node> next=nullptr;
    std::shared_ptr<Node> previous=nullptr;
    };

    int number = 0;
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;


    class Iterator
    {
      public:
        using difference_type = long;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::random_access_iterator_tag;

        Iterator(Node* node = nullptr);

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
    public:
      using difference_type = long;
      using value_type = T;
      using pointer = const T*;
      using reference = const T&;
      using iterator_category = std::random_access_iterator_tag;

      ConstIterator(Node* node = nullptr);

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
    void remove(const T& element);
    void display();

    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;
    T& operator[](int index);


};

template <typename T>
List<T>::Iterator::Iterator(typename List<T>::Node* node)
{
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++()
{
  // TODO: implement
  return Iterator();
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--()
{
  // TODO: implement
  return Iterator();
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
bool List<T>::Iterator::operator>(const Iterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
bool List<T>::Iterator::operator<(const Iterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
typename List<T>::Iterator::difference_type List<T>::Iterator::operator-(const Iterator& other) const
{
  // TODO: implement
  return 0;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator+(difference_type diff) const
{
  // TODO: implement
  return Iterator();
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator-(difference_type diff) const
{
  // TODO: implement
  return Iterator();
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator[](std::size_t i)
{
  // TODO: implement
  return Iterator();
}

template <typename T>
T& List<T>::Iterator::operator*()
{
    // TODO: implement
    static T element;
    return element;
}





template <typename T>
List<T>::ConstIterator::ConstIterator(typename List<T>::Node* node)
{
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++()
{
  // TODO: implement
  return ConstIterator();
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--()
{
  // TODO: implement
  return ConstIterator();
}

template <typename T>
bool List<T>::ConstIterator::operator==(const ConstIterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
bool List<T>::ConstIterator::operator!=(const ConstIterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
bool List<T>::ConstIterator::operator>(const ConstIterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
bool List<T>::ConstIterator::operator<(const ConstIterator& other) const
{
  // TODO: implement
  return true;
}

template <typename T>
typename List<T>::ConstIterator::difference_type List<T>::ConstIterator::operator-(const ConstIterator& other) const
{
  // TODO: implement
  return 0;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator+(difference_type diff) const
{
  // TODO: implement
  return Iterator();
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator-(difference_type diff) const
{
  // TODO: implement
  return ConstIterator();
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator[](std::size_t i)
{
  // TODO: implement
  return Iterator();
}

template <typename T>
const T& List<T>::ConstIterator::operator*()
{
    // TODO: implement
    static T element;
    return element;
}





template <typename T>
void List<T>::display()
{
  auto temp = head;

  std::cout<<"lista:"<<std::endl;
  while (temp->previous)
  {
  std::cout<<temp->value<<std::endl;
  temp=temp->previous;
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
    number++;
  }
  else if(number==1)
  {
    tail=new_node;
    tail->next=head;
    head->previous=tail;
    number++;
  }
  else
  {
    auto temp= tail;

    new_node->previous=nullptr;
    new_node->next=temp;
    temp->previous=new_node;
    tail=new_node;
    number++;
    display();
  }
 
}

template <typename T>
void List<T>::pushFront(const T& newElement)
{
  std::shared_ptr<Node> new_node{new Node};
  new_node->value=newElement;

  if(number==0)
  {
    head=new_node;
    number++;
  }
  else if(number==1)
  {
    tail=head;
    head=new_node;
    tail->next=head;
    head->previous=tail;
    number++;
  }
  else
  {
    auto temp= head;

  
    new_node->previous=temp;
    new_node->next=nullptr;
    temp->next=new_node;
    head=new_node;
    number++;
    display();

  }

  
}
  



template <typename T>
void List<T>::insert(const T& newElement, int index)
{

    // TODO: implement
}

template <typename T>
void List<T>::remove(const T& element)
{
    // TODO: implement
}

template <typename T>
typename List<T>::Iterator List<T>::begin()
{
    // TODO: implement
    return Iterator();
}

template <typename T>
typename List<T>::Iterator List<T>::end()
{
    // TODO: implement
    return Iterator();
}

template <typename T>
typename List<T>::ConstIterator List<T>::cbegin() const
{

    // TODO: implement
    return ConstIterator();
}

template <typename T>
typename List<T>::ConstIterator List<T>::cend() const
{
    return ConstIterator();
    // TODO: implement
}

template <typename T>
T& List<T>::operator[](int index)
{
    // TODO: implement
    static T element;
    return element;
}

#endif /* LIST_HPP_ */
