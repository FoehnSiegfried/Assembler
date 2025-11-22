#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#define HASHTABLE_VERSION 102

#define HASHTABLE_DEBUG
#define AUTO_LOADFACTOR 0.75F

#ifdef HASHTABLE_DEBUG
#include <iostream>
#endif // HASHTABLE_DEBUG

#include "Hash.h"

template <typename K, typename V>
struct HashNode
{
    K key;
    V value;
    struct HashNode<K, V> *next;
};

template <typename K, typename V>
class HashTable
{
private:
    unsigned int table_size;
    unsigned int node_count;
    struct HashNode<K, V> **table;
    bool auto_load_factor;
    bool compareKey(const K &keyA, const K &keyB);

public:
    HashTable();
    HashTable(unsigned int size = 101, bool autoLoadFactor = true);
    ~HashTable();
    unsigned int getHashIndex(const K &key);
    void insert(const K &key, const V &value);
    V search(const K &key);
    void remove(const K &key);
    bool ownKey(const K &key);
    bool compare(const K &keyA, const K &keyB);
    void clear();
    bool resetTable(unsigned int size);
    void redoubleTable();

#ifdef HASHTABLE_DEBUG
    void printTable();
#endif // HASHTABLE_DEBUG

    unsigned int getTableSize();
    unsigned int getNodeCount();
    float getLoadFactor();
};

#include "HashTable.tpp"

#endif // _HASHTABLE_H_
