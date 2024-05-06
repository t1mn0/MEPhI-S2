#pragma once

#include "LinkedList.hpp"
#include "Sequence.hpp"

template <typename T>
class ArraySequence;

template <typename T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T>* core = new LinkedList<T>;

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
    class ListSequenceIterator : public Sequence<T>::Iterator {
    public:
        typename LinkedList<T>::Iterator it;
        ListSequenceIterator(typename LinkedList<T>::Iterator iterator) : it(iterator) {}
        T operator*() const override;
        void operator++() override;
        bool operator!=(const typename ListSequence<T>::ListSequenceIterator& other) const;
        bool operator==(const typename ListSequence<T>::ListSequenceIterator& other) const;
    };

    ListSequence();
    ListSequence(int size, const T& item);
    ListSequence(const LinkedList<T>& core);
    ListSequence(const ArraySequence<T>& other);
    ListSequence(const ListSequence<T>& other);
    ~ListSequence();

    size_t get_size() const override;

    ListSequence<T>* push_back(const T& item) override;
    ListSequence<T>* push_front(const T& item) override;
    ListSequence<T>* pop_back() override;
    ListSequence<T>* pop_front() override;

    T get(int index) const;

    ListSequence<T>* set(const T& item, int index);

    typename ListSequence<T>::ListSequenceIterator begin() const;
    typename ListSequence<T>::ListSequenceIterator end() const;

    ListSequence<T>* insert(const T& item, typename Sequence<T>::Iterator& iter) override;
    ListSequence<T>* erase(typename Sequence<T>::Iterator& iter) override;

    ListSequence<T>* resize(int new_size) override;
    ListSequence<T>* resize(int new_size, const T& default_element) override;
    ListSequence<T>* sub_seq(int startIndex, int endIndex) const override;
    ListSequence<T>* map(T(*func)(const T&)) override;
    ListSequence<T>* where(bool (*predicate)(const T&)) const override;
    int find(T element) const override;
    int count(T element) const override;
    ListSequence<T>* concat(Sequence<T>& other) override;
    ListSequence<T>* clear() override;

    T operator[](int index) const override;

    virtual ListSequence<T>* Instance() = 0;
    virtual ListSequence<T>* Factory() const = 0;
};

#include "ListSequence.cpp"