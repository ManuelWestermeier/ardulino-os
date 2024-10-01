#ifndef UTILS_STRUCTS_LIST_HPP
#define UTILS_STRUCTS_LIST_HPP

#include <new>  // Include for placement new

template <typename T, typename SizeType>
struct List
{
    SizeType size = 0;
    T *data = nullptr;

    List(SizeType length)
    {
        Scale(length);  // Initialize the list with the specified length
    }

    List(T *_data)
    {
        data = _data;
    }

    ~List()
    {
        if (data != nullptr)
        {
            // Call the destructor for each element in the array
            for (SizeType i = 0; i < size; i++)
            {
                data[i].~T();
            }
            delete[] reinterpret_cast<char*>(data);  // Free allocated memory
        }
    }

    void Scale(SizeType itemCount)
    {
        // Allocate memory for the array without calling constructors
        T *newData = reinterpret_cast<T*>(new char[itemCount * sizeof(T)]);
        SizeType writeLength = size > itemCount ? itemCount : size;

        // Copy existing data to the new array
        for (SizeType i = 0; i < writeLength; i++)
        {
            new (&newData[i]) T(data[i]);  // Placement new to copy construct
            data[i].~T();  // Destroy old object
        }

        // Free the old memory
        if (data != nullptr)
        {
            delete[] reinterpret_cast<char*>(data);  // Cast back to char for deletion
        }

        // Update the size and data pointer
        size = itemCount;
        data = newData;
    }
};

#endif
