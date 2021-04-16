#ifndef MAP_HPP_
#define MAP_HPP_

template <typename KeyType, typename ValueType>
class Map
{
  private:
    std::array<ValueType, 1000> tab;

  public:
    Map() {}
    Map(const Map& otherMap) { }

    void insert(const KeyType& key ,const ValueType& value);
    ValueType& operator[](const KeyType& key);
    void remove(const KeyType& key);
};


int hash(std::string str)
{
  int result=0;
  for(auto i=0; i<str.length(); i++)
    result +=static_cast<int>(str[i]);

  return result % 1000;  
}


template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
  auto index = hash(key);
  tab[index]=value;
}

template <typename KeyType, typename ValueType>
ValueType &Map<KeyType, ValueType>::operator[](const KeyType &key) {
  auto index = hash(key);
  return tab[index];
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::remove(const KeyType &key)
{
  auto index = hash(key);
  

}

#endif /* MAP_HPP_ */
