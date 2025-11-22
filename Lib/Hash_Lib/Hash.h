#ifndef _HASH_H_
#define _HASH_H_

#include <cstdint>
#include <string>
#include <cstring>
#include <type_traits>

#define HASH_VERSION 101

class Hash
{
private:
    static const uint32_t FNV_32_INIT = 2166136261U;
    static const uint32_t FNV_32_PRIME = 16777619U;
    static const uint64_t FNV_64_INIT = 14695981039346656037ULL;
    static const uint64_t FNV_64_PRIME = 1099511628211ULL;

public:
    template <typename K>
    static uint32_t hash32_fnv(const K &key);
    template <typename K>
    static uint64_t hash64_fnv(const K &key);

    // 32
    static uint32_t hash32_fnv_byte(const void *key, size_t length); // base
    // 64
    static uint64_t hash64_fnv_byte(const void *key, size_t length); // base
    // 特化32
    static uint32_t hash32_fnv_string(const std::string &key);
    static uint32_t hash32_fnv_char(const char *key);
    static uint32_t hash32_fnv_pointer(const void *key);
    // 特化64
    static uint64_t hash64_fnv_string(const std::string &key);
    static uint64_t hash64_fnv_char(const char *key);
    static uint64_t hash64_fnv_pointer(const void *key);
};

#include "Hash.tpp"

#endif // _HASH_H_