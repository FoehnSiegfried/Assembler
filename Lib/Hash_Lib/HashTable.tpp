#ifndef _HASHTABLE_TPP_
#define _HASHTABLE_TPP_

#include "HashTable.h"

template <typename K, typename V>
HashTable<K, V>::HashTable(){
    table_size = 97;
    node_count = 0;
    auto_load_factor = true;
    table = new struct HashNode<K, V> *[table_size];
    for (unsigned int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }
}

template <typename K, typename V>
HashTable<K, V>::HashTable(unsigned int size, bool autoLoadFactor)
{
    table_size = size;
    node_count = 0;
    auto_load_factor = autoLoadFactor;
    table = new struct HashNode<K, V> *[table_size];
    for (unsigned int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }
}

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
    clear();
    delete[] table;
}

template <typename K, typename V>
unsigned int HashTable<K, V>::getHashIndex(const K &key)
{
    return Hash::hash32_fnv<K>(key) % table_size;
}

template <typename K, typename V>
void HashTable<K, V>::insert(const K &key, const V &value)
{
    if (auto_load_factor && (node_count >= table_size * AUTO_LOADFACTOR))
    {
        redoubleTable();
    }
    unsigned int index = getHashIndex(key);
    struct HashNode<K, V> *current = table[index];
    while (current != nullptr)
    {
        if (compareKey(current->key, key))
        {
            current->value = value;
            return;
        }
        current = current->next;
    }
    struct HashNode<K, V> *newNode = new struct HashNode<K, V>;
    newNode->key = key;
    newNode->value = value;
    newNode->next = table[index];
    table[index] = newNode;
    node_count++;
}

template <typename K, typename V>
V HashTable<K, V>::search(const K &key)
{
    unsigned int index = getHashIndex(key);
    struct HashNode<K, V> *current = table[index];
    while (current != nullptr)
    {
        if (compareKey(current->key, key))
        {
            return current->value;
        }
        current = current->next;
    }
    return V();
}

template <typename K, typename V>
void HashTable<K, V>::remove(const K &key)
{
    unsigned int index = getHashIndex(key);
    struct HashNode<K, V> *current = table[index];
    struct HashNode<K, V> *prev = nullptr;
    while (current != nullptr)
    {
        if (compareKey(current->key, key))
        {
            if (prev == nullptr)
            {
                table[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            delete current;
            node_count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

template <typename K, typename V>
bool HashTable<K, V>::ownKey(const K &key)
{
    unsigned int index = getHashIndex(key);
    struct HashNode<K, V> *current = table[index];
    while (current != nullptr)
    {
        if (compareKey(current->key, key))
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename K, typename V>
bool HashTable<K, V>::compare(const K &keyA, const K &keyB)
{
    return search(keyA) == search(keyB);
}

template <typename K, typename V>
void HashTable<K, V>::clear()
{
    for (unsigned int i = 0; i < table_size; i++)
    {
        struct HashNode<K, V> *current = table[i];
        while (current != nullptr)
        {
            struct HashNode<K, V> *next = current->next;
            delete current;
            current = next;
        }
        table[i] = nullptr;
    }
    node_count = 0;
}

template <typename K, typename V>
bool HashTable<K, V>::resetTable(unsigned int size)
{
    if (size == table_size)
        return true;
    if (size == 0)
        return false;
    try
    {
        struct HashNode<K, V> **newTable = new struct HashNode<K, V> *[size];
        for (unsigned int i = 0; i < size; i++)
        {
            newTable[i] = nullptr;
        }

        for (unsigned int i = 0; i < table_size; i++)
        {
            HashNode<K, V> *current = table[i];
            while (current != nullptr)
            {
                HashNode<K, V> *next = current->next;
                unsigned int index = Hash::hash32_fnv<K>(current->key) % size;
                current->next = newTable[index];
                newTable[index] = current;
                current = next;
            }
            table[i] = nullptr;
        }
        delete[] table;
        table = newTable;
        table_size = size;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

template <typename K, typename V>
void HashTable<K, V>::redoubleTable()
{
    resetTable(table_size * 2);
}

#ifdef HASHTABLE_DEBUG
template <typename K, typename V>
void HashTable<K, V>::printTable()
{
    for (unsigned int i = 0; i < table_size; i++)
    {
        struct HashNode<K, V> *current = table[i];
        if (current != nullptr)
        {
            std::cout << "Index " << i << ": ";
            while (current != nullptr)
            {
                std::cout << "(" << current->key << ", " << current->value << ") -> ";
                current = current->next;
            }
            std::cout << "nullptr" << std::endl;
        }
    }
}
#endif // HASHTABLE_DEBUG

template <typename K, typename V>
unsigned int HashTable<K, V>::getTableSize()
{
    return table_size;
}

template <typename K, typename V>
unsigned int HashTable<K, V>::getNodeCount()
{
    return node_count;
}

template <typename K, typename V>
float HashTable<K, V>::getLoadFactor()
{
    return (float)node_count / (float)table_size;
}

template <typename K, typename V>
bool HashTable<K, V>::compareKey(const K &keyA, const K &keyB)
{
    if constexpr (std::is_same_v<K, char *> || std::is_same_v<K, const char *>)
    {
        return strcmp(keyA, keyB) == 0;
    }
    else
    {
        return keyA == keyB;
    }
}

#endif // _HASHTABLE_TPP_
