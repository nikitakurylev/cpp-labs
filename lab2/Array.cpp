#pragma once

#include "Array.h"
#include <utility>
#include <type_traits>

template <typename T>
Array<T>::Array() : capacity_(16), size_(0)
{
	array_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
}

template <typename T>
Array<T>::Array(int capacity) : capacity_(capacity), size_(0)
{
	array_ = static_cast<T *>(malloc(sizeof(T) * capacity_));
}

template <typename T>
Array<T>::Array(const Array<T> &other) : size_(other.size_), capacity_(other.capacity_)
{
	array_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
	for (int i = 0; i < size_; i++)
		new(&array_[i]) T(other.array_[i]);
}

template <typename T>
Array<T>::Array(Array<T> &&other) noexcept : array_(other.array_), size_(other.size_), capacity_(other.capacity_)
{
	other.clear();
}

template <typename T>
Array<T>::~Array()
{
	destroy();
}

template <typename T>
int Array<T>::insert(const T &value)
{
	if (size_ >= capacity_)
		extend();
	new (&array_[size_]) T(value);
	return size_++;
}

template <typename T>
int Array<T>::insert(int index, const T &value)
{
	if (size_ >= capacity_)
		extend();
	for (int i = size_; i > index; i--)
		new (&array_[i]) T(array_[i - 1]);
	new (&array_[index]) T(value);
	size_++;
	return index;
}

template <typename T>
int Array<T>::insert(T &&value)
{
	if (size_ >= capacity_)
		extend();
	new (&array_[size_]) T(std::move(value));
	return size_++;
}

template <typename T>
int Array<T>::insert(int index, T &&value)
{
	if (size_ >= capacity_)
		extend();
	for (int i = size_; i > index; i--)
		new (&array_[i]) T(std::move(array_[i - 1]));
	new (&array_[index]) T(std::move(value));
	size_++;
	return index;
}

template <typename T>
void Array<T>::remove(int index)
{
	for (int i = index; i < size_ - 1; i++)
		array_[i] = std::move(array_[i + 1]);
	size_--;
	array_[size_].~T();
}

template <typename T>
int Array<T>::size() const
{
	return size_;
}

template <typename T>
const T &Array<T>::operator[](int index) const
{
	return array_[index];
}

template <typename T>
T &Array<T>::operator[](int index)
{
	return array_[index];
}

template <typename T>
Array<T> &Array<T>::operator=(const Array<T> &other)
{
	if (this == &other)
		return *this;
	destroy();
	capacity_ = other.capacity_;
	size_ = other.size_;
	array_ = static_cast<T *>(malloc(sizeof(T) * capacity_));
	for (int i = 0; i < size_; i++)
		new (&array_[i]) T(other.array_[i]);
	return *this;
}

template <typename T>
Array<T> &Array<T>::operator=(Array<T> &&other) noexcept
{
	if (this == &other)
		return *this;
	destroy();
	array_ = other.array_;
	size_ = other.size_;
	capacity_ = other.capacity_;
	other.clear();
	return *this;
}

template <typename T>
void Array<T>::clear()
{
	array_ = nullptr;
	capacity_ = 0;
	size_ = 0;
}

template <typename T>
void Array<T>::extend()
{
	capacity_ *= 2;
	if (capacity_ == 0)
		capacity_ = 1;
	T *new_array = static_cast<T *>(malloc(sizeof(T) * capacity_));
	for (int i = 0; i < size_; i++)
		new (&new_array[i]) T(std::move(array_[i]));
	destroy();
	array_ = new_array;
}

template <typename T>
void Array<T>::destroy()
{
	if (!std::is_destructible<T>::value)
		for (int i = 0; i < size_; i++)
			array_[i].~T();
	free(array_);
}

template <typename T>
Array<T>::ArrayIterator::ArrayIterator(T *pointer, Array<T> &array, int direction) : pointer_(pointer), array_(array), direction_(direction) {}

template <typename T>
typename Array<T>::ArrayIterator Array<T>::iterator()
{
	return Array<T>::ArrayIterator(array_, *this, 1);
}

template <typename T>
typename Array<T>::ArrayIterator Array<T>::reverseIterator()
{
	return Array<T>::ArrayIterator(array_ + size_ - 1, *this, -1);
}

template <typename T>
const T &Array<T>::ArrayIterator::get() const
{
	return *pointer_;
}

template <typename T>
void Array<T>::ArrayIterator::set(const T &value)
{
	*pointer_ = value;
}

template <typename T>
void Array<T>::ArrayIterator::next()
{
	pointer_ += direction_;
}

template <typename T>
bool Array<T>::ArrayIterator::hasNext() const
{
	return pointer_ <= &array_.array_[array_.size_ - 1] && pointer_ >= &array_.array_[0];
}

template <typename T>
Array<T>::ConstArrayIterator::ConstArrayIterator(T *pointer, const Array<T> &array, int direction) : pointer_(pointer), array_(array), direction_(direction) {}

template <typename T>
typename Array<T>::ConstArrayIterator Array<T>::iterator() const
{
	return Array<T>::ConstArrayIterator(array_, *this, 1);
}

template <typename T>
typename Array<T>::ConstArrayIterator Array<T>::reverseIterator() const
{
	return Array<T>::ConstArrayIterator(array_ + size_ - 1, *this, -1);
}

template <typename T>
const T &Array<T>::ConstArrayIterator::get() const
{
	return *pointer_;
}

template <typename T>
void Array<T>::ConstArrayIterator::next()
{
	pointer_ += direction_;
}

template <typename T>
bool Array<T>::ConstArrayIterator::hasNext() const
{
	return pointer_ <= &array_.array_[array_.size_ - 1] && pointer_ >= &array_.array_[0];
}