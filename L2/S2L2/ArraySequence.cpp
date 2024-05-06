#include "ArraySequence.hpp"



// -----------------------------------------------------------------------------------------------------------------
// Constructors and destructor

template <typename T>
ArraySequence<T>::ArraySequence() {
    core = new DynamicArray<T>();
}

template <typename T>
ArraySequence<T>::ArraySequence(int size, const T& item) : ArraySequence() {
    core = new DynamicArray<T>(size, item);
}

template <typename T>
ArraySequence<T>::ArraySequence(const DynamicArray<T>& other) : ArraySequence() {
    for (int i = 0; i < other.get_size(); ++i) {
        core->push_back(other.get(i));
    }
}

template <typename T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other) : ArraySequence() {
    for (int i = 0; i < other.get_size(); ++i) {
        core->push_back(other.get(i));
    }
}

template <typename T>
ArraySequence<T>::ArraySequence(const ListSequence<T>& other) : ArraySequence() {
    for (int i = 0; i < other.get_size(); ++i) {
        core->push_back(other.get(i));
    }
}

template <typename T>
ArraySequence<T>::~ArraySequence() {
    core->~DynamicArray<T>();
}



// -----------------------------------------------------------------------------------------------------------------
// Iterators

template <typename T>
T ArraySequence<T>::ArraySequenceIterator::operator*() const {
    T t = it.operator*();
    return t;
}

template <typename T>
void ArraySequence<T>::ArraySequenceIterator::operator++() {
    it.operator++();
}

template <typename T>
bool ArraySequence<T>::ArraySequenceIterator::operator!=(const typename ArraySequence<T>::ArraySequenceIterator& other) const {
    return it != other.it;
}

template <typename T>
bool ArraySequence<T>::ArraySequenceIterator::operator==(const typename ArraySequence<T>::ArraySequenceIterator& other) const {
    return it == other.it;
}

// -----------------------------------------------------------------------------------------------------------------
// Basics methods + private internal methods

template <typename T>
size_t ArraySequence<T>::get_size() const {
    return core->get_size();
}

template <typename T>
ArraySequence<T>* ArraySequence<T>::push_back(const T& item) {
    ArraySequence<T>* instance = Instance();
    instance->push_back_Internal(item);
    return instance;
}

template <typename T>
void ArraySequence<T>::push_back_Internal(const T& item) const {
    core->push_back(item);
}

template <typename T>
ArraySequence<T>* ArraySequence<T>::push_front(const T& item) {
    ArraySequence<T>* instance = Instance();
    instance->push_front_Internal(item);
    return instance;
}

template <typename T>
void ArraySequence<T>::push_front_Internal(const T& item) const {
    core->push_front(item);
}

template <typename T>
ArraySequence<T>* ArraySequence<T>::pop_back() {
    ArraySequence<T>* instance = Instance();
    instance->pop_back_Internal();
    return instance;
}

template <typename T>
void ArraySequence<T>::pop_back_Internal() const {
    core->pop_back();
}

template <typename T>
ArraySequence<T>* ArraySequence<T>::pop_front() {
    ArraySequence<T>* instance = Instance();
    instance->pop_front_Internal();
    return instance;
}

template <typename T>
void ArraySequence<T>::pop_front_Internal() const {
    core->pop_front();
}

template <typename T>
T ArraySequence<T>::get(int index) const {
    return core->get(index);
}

template <typename T>
ArraySequence<T>* ArraySequence<T>::set(const T& item, int index) {
    ArraySequence<T>* instance = Instance();
    instance->set_Internal(item, index);
    return instance;
}

template <typename T>
void ArraySequence<T>::set_Internal(const T& item, int index) {
    core->set(item, index);
}

// -----------------------------------------------------------------------------------------------------------------
// Operations with iterators

template <typename T>
typename ArraySequence<T>::ArraySequenceIterator ArraySequence<T>::begin() const {
    return ArraySequenceIterator(core->begin());
}

template <typename T>
typename ArraySequence<T>::ArraySequenceIterator ArraySequence<T>::end() const {
    return ArraySequenceIterator(core->end());
}

template <typename T>
ArraySequence<T>* ArraySequence<T>::insert(const T& item, typename Sequence<T>::Iterator& iter) {
    ArraySequence<T>* instance = Instance();
    instance->insert_Internal(item, iter);
    return instance;
}

template <typename T>
void ArraySequence<T>::insert_Internal(const T& item, typename Sequence<T>::Iterator& iter) {
    ArraySequence<T>::ArraySequenceIterator& arrIterator = static_cast<ArraySequence<T>::ArraySequenceIterator&>(iter);
    core->insert(item, arrIterator.it);
}

template <typename T>
ArraySequence<T>* ArraySequence<T>::erase(typename typename Sequence<T>::Iterator& iter) {
    ArraySequence<T>* instance = Instance();
    instance->erase_Internal(iter);
    return instance;
}

template <typename T>
void ArraySequence<T>::erase_Internal(typename typename Sequence<T>::Iterator& iter) {
    ArraySequence<T>::ArraySequenceIterator& arrIterator = static_cast<ArraySequence<T>::ArraySequenceIterator&>(iter);
    core->erase(arrIterator.it);
}

// -----------------------------------------------------------------------------------------------------------------
// Functions

template <typename T>
ArraySequence<T>* ArraySequence<T>::resize(int new_size, const T& default_element) {
    ArraySequence<T>* instance = Instance();
    instance->resize_Internal(new_size, default_element);
    return instance;
}

template <typename T>
void ArraySequence<T>::resize_Internal(int new_size, const T& default_element) {
    core->resize(new_size, default_element);
}

template <typename T>
ArraySequence<T>* ArraySequence<T>::resize(int new_size) {
    ArraySequence<T>* instance = Instance();
    instance->resize_Internal(new_size);
    return instance;
}

template <typename T>
void ArraySequence<T>::resize_Internal(int new_size) {
    core->resize(new_size);
}

template <typename T>
ArraySequence<T>* ArraySequence<T>::concat(Sequence<T>& other) {
    ArraySequence<T>* instance = Instance();
    for (int i = 0; i < other.get_size(); ++i) {
        instance->push_back(other.get(i));
    }
    return instance;
}

template <typename T>
ArraySequence<T>* ArraySequence<T>::sub_seq(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex > static_cast<int>(this->get_size()) || endIndex > startIndex) {
        throw Exception(ErrorCode::invalid_argument);
    }
    ArraySequence<T>* newArraySeq = Factory();
    for (int i = startIndex; i <= endIndex; ++i) {
        newArraySeq->push_back(this->get(i));
    }
    return newArraySeq;
}

template <typename T>
ArraySequence<T>* ArraySequence<T>::map(T(*func)(const T&)) {
    ArraySequence<T>* seq = Instance();

    for (size_t i = 0; i < this->get_size(); ++i) {
        seq->set(func((*core)[i]), i);
    }

    return seq;
}

template <typename T>
ArraySequence<T>* ArraySequence<T>::where(bool (*predicate)(const T&)) const {
    ArraySequence<T>* seq = Factory();
    for (size_t i = 0; i < this->get_size(); ++i) {
        if (predicate((*core)[i])) {
            seq->push_back((*core)[i]);
        }
    }

    return seq;
}

template <typename T>
int ArraySequence<T>::find(T element) const {
    for (int i = 0; i < this->get_size(); ++i) {
        if (element == this->get(i)) {
            return i;
        }
    }
    return -1;
}

template <typename T>
int ArraySequence<T>::count(T element) const {
    int count = 0;
    for (int i = 0; i < this->get_size(); ++i) {
        if (element == this->get(i)) {
            count++;
        }
    }
    return count;
}

template <typename T>
ArraySequence<T>* ArraySequence<T>::clear() {
    ArraySequence<T>* instance = Instance();
    instance->clear_Internal();
    return instance;
}

template <typename T>
void ArraySequence<T>::clear_Internal() {
    core->clear();
}

template <typename T>
T ArraySequence<T>::operator[](int index) const {
    return core->operator[](index);
}