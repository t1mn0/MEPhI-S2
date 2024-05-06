#pragma once

template <typename T>
class LinkedList;



template <typename T>
class DynamicArray {
private:
    T* array;
    size_t size = 0;
    size_t capacity = 0;

    void reallocation();

public:

    class Iterator {
    public:
        T* current;
        Iterator(T* item) : current(item) {}
        T operator*() const;
        void operator++();
        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
    };

    DynamicArray();
    DynamicArray(int size, const T& default_element);
    DynamicArray(const LinkedList<T>& other);
    DynamicArray(const DynamicArray<T>& other);
    ~DynamicArray();

    size_t get_size() const;
    bool empty() const;
    T front() const;
    T back() const;
    void push_back(const T& item);
    void push_front(const T& item);
    void pop_back();
    void pop_front();

    Iterator begin() const;
    Iterator end() const;
    T get(int index) const;
    void set(const T& item, int index);
    void insert(const T& item, Iterator iter);
    void erase(Iterator& iter);

    void resize(int new_size);
    void resize(int new_size, const T& default_element);
    void clear();

    T operator[](int index) const;
};

#include "DynamicArray.cpp"
