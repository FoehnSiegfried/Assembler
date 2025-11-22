#ifndef _MAP_TPP_
#define _MAP_TPP_

#include "Map.h"

template <typename K, typename V>
Map<K, V>::Map(){
    hashTable = new HashTable<K, V>(199);
}

template <typename K, typename V>
Map<K, V>::Map(std::initializer_list<std::pair<K, V>> init_list)
{
    hashTable = new HashTable<K, V>(init_list.size(), false);
    for (auto &pair : init_list)
    {
        hashTable->insert(pair.first, pair.second);
    }
}

template <typename K, typename V>
Map<K, V>::~Map()
{
    delete hashTable;
}

template <typename K, typename V>
V Map<K, V>::operator[](const K &key) const
{
    return hashTable->search(key);
}

template <typename K, typename V>
bool Map<K, V>::find(const K &key)
{
    return hashTable->ownKey(key);
}

#endif // _MAP_TPP_
