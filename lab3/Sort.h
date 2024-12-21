#pragma once
template <typename T, typename Compare>
void swap(T* a, T* b) ;

template <typename T, typename Compare>
void qsort(T *first, T *last, Compare compare, int length_to_insertion_sort = 0);

template <typename T, typename Compare>
void insertionSort(T *first, T *last, Compare compare);

#include "Sort.cpp"
