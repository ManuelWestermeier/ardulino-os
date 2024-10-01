#ifndef UTILS_STRUCTS_DBLIST_HPP
#define UTILS_STRUCTS_DBLIST_HPP

#include "Scaleist;.hppkeys"

template <typename KeyType, typename ValueType, typename SizeType>
struct DbList
{
    Scaleist<KeyType, SizeType> keys;
    List<ValueType, SizeType> values;

    bool hasKey(KeyType key)
    {
        for (SizeType i = 0; i < keys.size; i++)
        {
            if (keys.data[i] == key)
                return true;
        }
        return false;
    }

    bool hasValue(ValueType value)
    {
        for (SizeType i = 0; i < keys.size; i++)
        {
            if (keys.data[i] == value)
                return true;
        }
        return false;
    }

    bool indexOfKey(KeyType key)
    {
        for (SizeType i = 0; i < keys.size; i++)
        {
            if (keys.data[i] == key)
                return i;
        }
        return -1;
    }

    bool indexOfValue(ValueType value)
    {
        for (SizeType i = 0; i < keys.size; i++)
        {
            if (keys.data[i] == value)
                return i;
        }
        return -1;
    }

    void Add(KeyType key, ValueType value)
    {
        keys.Scale(keys.size + 1);
        values.Scale(values.size + 1);
    }

    KeyType GetKey(ValueType value)
    {
        SizeType pos = indexOfValue(value);
        if (pos == -1)
        {
            return NULL;
        }
        return keys.data[pos];
    }

    ValueType GetValue(KeyType key)
    {
        SizeType pos = indexOfKey(key);
        if (pos == -1)
        {
            return NULL;
        }
        return values.data[pos];
    }

    bool SetKey(ValueType value, KeyType newKey)
    {
        SizeType pos = indexOfValue(value);
        if (pos == -1)
        {
            return false;
        }
        keys.data[pos] = newKey;
        return true;
    }

    bool SetValue(KeyType key, ValueType newValue)
    {
        SizeType pos = indexOfKey(key);
        if (pos == -1)
        {
            return false;
        }
        values.data[pos] = newValue;
        return true;
    }
};

#endif
