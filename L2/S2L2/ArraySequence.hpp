#pragma once

#include "DynamicArray.hpp"
#include "Sequence.hpp"

template <typename T>
class ListSequence;

template <typename T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* core = new DynamicArray<T>;

    void push_back_Internal(const T& item) const;
    void push_front_Internal(const T& item) const;
    void pop_back_Internal() const;
    void pop_front_Internal() const;
    void set_Internal(const T& item, int index);
    void insert_Internal(const T& item, typename Sequence<T>::Iterator& iter);
    void erase_Internal(typename typename Sequence<T>::Iterator& iter);
    void resize_Internal(int new_size);
    void resize_Internal(int new_size, const T& default_element);
    void clear_Internal();

public:
    class ArraySequenceIterator : public Sequence<T>::Iterator {
    public:
        typename DynamicArray<T>::Iterator it;
        ArraySequenceIterator(typename DynamicArray<T>::Iterator iterator) : it(iterator) {}
        T operator*() const override;
        void operator++() override;
        bool operator!=(const typename ArraySequence<T>::ArraySequenceIterator& other) const;
        bool operator==(const typename ArraySequence<T>::ArraySequenceIterator& other) const;
    };

    ArraySequence();
    ArraySequence(int size, const T& item);
    ArraySequence(const DynamicArray<T>& core);
    ArraySequence(const ListSequence<T>& other);
    ArraySequence(const ArraySequence<T>& other);
    ~ArraySequence();

    size_t get_size() const override;

    ArraySequence<T>* push_back(const T& item) override;
    ArraySequence<T>* push_front(const T& item) override;
    ArraySequence<T>* pop_back() override;
    ArraySequence<T>* pop_front() override;

    T get(int index) const override;

    ArraySequence<T>* set(const T& item, int index) override;

    typename ArraySequence<T>::ArraySequenceIterator begin() const;
    typename ArraySequence<T>::ArraySequenceIterator end() const;

    ArraySequence<T>* insert(const T& item, typename Sequence<T>::Iterator& iter) override;
    ArraySequence<T>* erase(typename Sequence<T>::Iterator& iter) override;

    ArraySequence<T>* resize(int new_size) override;
    ArraySequence<T>* resize(int new_size, const T& default_element) override;
    ArraySequence<T>* sub_seq(int startIndex, int endIndex) const override;
    ArraySequence<T>* map(T(*func)(const T&)) override;
    ArraySequence<T>* where(bool (*predicate)(const T&)) const override;
    int find(T element) const override;
    int count(T element) const override;
    ArraySequence<T>* concat(Sequence<T>& other) override;
    ArraySequence<T>* clear() override;

    T operator[](int index) const override;

    virtual ArraySequence<T>* Instance() = 0;
    virtual ArraySequence<T>* Factory() const = 0;
};

#include "ArraySequence.cpp"