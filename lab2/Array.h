#pragma once

template <typename T>
class Array final
{
public:
    Array();
    Array(int capacity);
    Array(const Array<T> &other);
    Array(Array<T> &&other) noexcept;
    ~Array();

    int insert(const T &value);
    int insert(int index, const T &value);
    int insert(T &&value);
    int insert(int index, T &&value);
    void remove(int index);
    int size() const;

    const T &operator[](int index) const;
    T &operator[](int index);
    Array<T> &operator=(const Array<T> &other);
    Array<T> &operator=(Array<T> &&other) noexcept;

    class ArrayIterator final
    {
    public:
        ArrayIterator(T *pointer, Array<T> &array, int direction);

        const T &get() const;
        void set(const T &value);
        void next();
        bool hasNext() const;

    private:
        T *pointer_;
        Array<T> &array_;
        int direction_;
    };

    class ConstArrayIterator final
    {
    public:
        ConstArrayIterator(T *pointer, Array<T> &array, int direction);

        const T &get() const;
        void next();
        bool hasNext() const;

    private:
        T *pointer_;
        Array<T> &array_;
        int direction_;
    };

    ArrayIterator iterator();
    ConstArrayIterator iterator() const;

    ArrayIterator reverseIterator();
    ConstArrayIterator reverseIterator() const;

private:
    T *array_;
    int capacity_;
    int size_;

    void clear();
    void extend();
    void destroy();
};

#include "Array.cpp"