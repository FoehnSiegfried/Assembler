#ifndef _HASH_TPP_
#define _HASH_TPP_

#include "Hash.h"

template <typename K>
uint32_t Hash::hash32_fnv(const K &key)
{
    if constexpr (std::is_same_v<K, std::string>)
    {
        return hash32_fnv_string(key);
    }
    else if constexpr (std::is_same_v<K, char *> || std::is_same_v<K, const char *>)
    {
        return hash32_fnv_char(key);
    }
    else if constexpr (std::is_pointer_v<K>)
    {
        return hash32_fnv_pointer(key);
    }
    else
    {
        return hash32_fnv_byte(&key, sizeof(K));
    }
}

template <typename K>
uint64_t Hash::hash64_fnv(const K &key)
{
    if constexpr (std::is_same_v<K, std::string>)
    {
        return hash64_fnv_string(key);
    }
    else if constexpr (std::is_same_v<K, char *> || std::is_same_v<K, const char *>)
    {
        return hash64_fnv_char(key);
    }
    else if constexpr (std::is_pointer_v<K>)
    {
        return hash64_fnv_pointer(key);
    }
    else
    {
        return hash64_fnv_byte(&key, sizeof(K));
    }
}

uint32_t Hash::hash32_fnv_byte(const void *key, size_t length)
{
    const uint8_t *bytes = static_cast<const uint8_t *>(key);
    uint32_t hash = FNV_32_INIT;
    for (size_t i = 0; i < length; ++i)
    {
        hash ^= bytes[i];
        hash *= FNV_32_PRIME;
    }
    return hash;
}

uint64_t Hash::hash64_fnv_byte(const void *key, size_t length)
{
    const uint8_t *bytes = static_cast<const uint8_t *>(key);
    uint64_t hash = FNV_64_INIT;
    for (size_t i = 0; i < length; ++i)
    {
        hash ^= bytes[i];
        hash *= FNV_64_PRIME;
    }
    return hash;
}

uint32_t Hash::hash32_fnv_string(const std::string &key)
{
    return hash32_fnv_byte(key.data(), key.length());
}

uint32_t Hash::hash32_fnv_char(const char *key)
{
    return hash32_fnv_byte(key, strlen(key));
}

uint32_t Hash::hash32_fnv_pointer(const void *key)
{
    uintptr_t int_ptr = reinterpret_cast<uintptr_t>(key);
    return hash32_fnv_byte(&int_ptr, sizeof(uintptr_t));
}

uint64_t Hash::hash64_fnv_string(const std::string &key)
{
    return hash64_fnv_byte(key.data(), key.length());
}

uint64_t Hash::hash64_fnv_char(const char *key)
{
    return hash64_fnv_byte(key, strlen(key));
}

uint64_t Hash::hash64_fnv_pointer(const void *key)
{
    uintptr_t int_ptr = reinterpret_cast<uintptr_t>(key);
    return hash64_fnv_byte(&int_ptr, sizeof(uintptr_t));
}

#endif // _HASH_TPP_
