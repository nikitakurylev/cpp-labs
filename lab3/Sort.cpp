#include "Sort.h"

template<typename T>
void swap(T* a, T* b) 
{
    T tmp(std::move(*a));
    *a = std::move(*b);
    *b = std::move(tmp);
}


template <typename T, typename Compare>
void qsort(T *first, T *last, Compare compare, int length_to_insertion_sort)
{
    if (last <= first)
        return;
    if (last - first < length_to_insertion_sort)
    {
        insertionSort(first, last, compare);
        return;
    }

    T *pivot = partition(first, last, compare);

    qsort(first, pivot - 1, compare, length_to_insertion_sort);
    qsort(pivot + 1, last, compare, length_to_insertion_sort);
}

template<typename T, typename Comparator>
void insertionSort(T* first, T* last, Comparator cmp) 
{
    for (T* i = first + 1; i <= last; i++)
    {
        T* j = i;
        while (j > first && cmp(*j, *(j - 1))) 
        {
            swap(j, (j - 1));
            j--;
        }
    }
}

template <typename T, typename Compare>
T *partition(T *first, T *last, Compare compare)
{
    T *center = first + (last - first) / 2;
    T *pivot;

    if (compare(*first, *center))
    {
        if (compare(*center, *first))
            pivot = center;
        else
            pivot = first;
    }
    else
    {
        if (compare(*center, *first))
            pivot = first;
        else
            pivot = center;
    }

    swap(last, pivot);
    pivot = last;
    last--;
    do
    {
        while (compare(*first, *pivot))
            first++;

        while (compare(*pivot, *last))
            last--;

        if (first < last)
            swap(first, last);
    } while (first < last);

    swap(first, pivot);

    return first;
}