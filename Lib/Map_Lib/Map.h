#ifndef _MAP_H_
#define _MAP_H_

#include "..\Hash_Lib\HashTable.h"

template <typename K, typename V>
class Map
{
private:
    HashTable<K, V> *hashTable;

public:
    Map();
    Map(std ::initializer_list<std ::pair<K, V>> init_list);
    ~Map();
    V operator[](const K &key) const;
    bool find(const K &key);
};

#include "Map.tpp"

#endif // _MAP_O_H_
