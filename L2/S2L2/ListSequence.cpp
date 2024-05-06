#include "ListSequence.hpp"



// -----------------------------------------------------------------------------------------------------------------
// Constructors and destructor

template <typename T>
ListSequence<T>::ListSequence() {
    core = new LinkedList<T>();
}

template <typename T>
ListSequence<T>::ListSequence(int size, const T& item) : ListSequence() {
    core = new LinkedList<T>(size, item);
}

template <typename T>
ListSequence<T>::ListSequence(const LinkedList<T>& other) : ListSequence() {
    for (int i = 0; i < other.get_size(); ++i) {
        core->push_back(other.get(i));
    }
}

template <typename T>
ListSequence<T>::ListSequence(const ArraySequence<T>& other) : ListSequence() {
    for (int i = 0; i < other.get_size(); ++i) {
        core->push_back(other.get(i));
    }
}

template <typename T>
ListSequence<T>::ListSequence(const ListSequence<T>& other) : ListSequence() {
    for (int i = 0; i < other.get_size(); ++i) {
        core->push_back(other.get(i));
    }
}

template <typename T>
ListSequence<T>::~ListSequence() {
    core->~LinkedList<T>();
}


// -----------------------------------------------------------------------------------------------------------------
// Iterators

template <typename T>
T ListSequence<T>::ListSequenceIterator::operator*() const {
    T t = it.operator*();
    return t;
}

template <typename T>
typename void ListSequence<T>::ListSequenceIterator::operator++() {
    it.operator++();
}

template <typename T>
bool ListSequence<T>::ListSequenceIterator::operator!=(const typename ListSequence<T>::ListSequenceIterator& other) const {
    return it != other.it;
}

template <typename T>
bool ListSequence<T>::ListSequenceIterator::operator==(const typename ListSequence<T>::ListSequenceIterator& other) const {
    return it == other.it;
}

// -----------------------------------------------------------------------------------------------------------------
// Basics methods + private internal methods

template <typename T>
size_t ListSequence<T>::get_size() const {
    return core->get_size();
}

template <typename T>
ListSequence<T>* ListSequence<T>::push_back(const T& item) {
    ListSequence<T>* instance = Instance();
    instance->push_back_Internal(item);
    return instance;
}

template <typename T>
void ListSequence<T>::push_back_Internal(const T& item) const {
    core->push_back(item);
}

template <typename T>
ListSequence<T>* ListSequence<T>::push_front(const T& item) {
    ListSequence<T>* instance = Instance();
    instance->push_front_Internal(item);
    return instance;
}

template <typename T>
void ListSequence<T>::push_front_Internal(const T& item) const {
    core->push_front(item);
}

template <typename T>
ListSequence<T>* ListSequence<T>::pop_back() {
    ListSequence<T>* instance = Instance();
    instance->pop_back_Internal();
    return instance;
}

template <typename T>
void ListSequence<T>::pop_back_Internal() const {
    core->pop_back();
}

template <typename T>
ListSequence<T>* ListSequence<T>::pop_front() {
    ListSequence<T>* instance = Instance();
    instance->pop_front_Internal();
    return instance;
}

template <typename T>
void ListSequence<T>::pop_front_Internal() const {
    core->pop_front();
}

template <typename T>
T ListSequence<T>::get(int index) const {
    return core->get(index);
}

template <typename T>
ListSequence<T>* ListSequence<T>::set(const T& item, int index) {
    ListSequence<T>* instance = Instance();
    instance->set_Internal(item, index);
    return instance;
}

template <typename T>
void ListSequence<T>::set_Internal(const T& item, int index) {
    return core->set(item, index);
}

// -----------------------------------------------------------------------------------------------------------------
// Operations with iterators

template <typename T>
typename ListSequence<T>::ListSequenceIterator ListSequence<T>::begin() const {
    ListSequenceIterator iter(core->begin());
    return iter;
}

template <typename T>
typename ListSequence<T>::ListSequenceIterator ListSequence<T>::end() const {
    ListSequenceIterator iter(nullptr);
    return iter;
}

template <typename T>
ListSequence<T>* ListSequence<T>::insert(const T& item, typename Sequence<T>::Iterator& iter) {
    ListSequence<T>* instance = Instance();
    instance->insert_Internal(item, iter);
    return instance;
}

template <typename T>
void ListSequence<T>::insert_Internal(const T& item, typename Sequence<T>::Iterator& iter) {
    ListSequence<T>::ListSequenceIterator& listIterator = static_cast<ListSequence<T>::ListSequenceIterator&>(iter);
    core->insert(item, listIterator.it);
}

template <typename T>
ListSequence<T>* ListSequence<T>::erase(typename typename Sequence<T>::Iterator& iter) {
    ListSequence<T>* instance = Instance();
    instance->erase_Internal(iter);
    return instance;
}

template <typename T>
void ListSequence<T>::erase_Internal(typename typename Sequence<T>::Iterator& iter) {
    ListSequence<T>::ListSequenceIterator& listIterator = static_cast<ListSequence<T>::ListSequenceIterator&>(iter);
    core->erase(listIterator.it);
}

// -----------------------------------------------------------------------------------------------------------------
// Functions

template <typename T>
ListSequence<T>* ListSequence<T>::resize(int new_size, const T& default_element) {
    ListSequence<T>* instance = Instance();
    instance->resize_Internal(new_size, default_element);
    return instance;
}

template <typename T>
void ListSequence<T>::resize_Internal(int new_size, const T& default_element) {
    core->resize(new_size, default_element);
}

template <typename T>
ListSequence<T>* ListSequence<T>::resize(int new_size) {
    ListSequence<T>* instance = Instance();
    instance->resize_Internal(new_size);
    return instance;
}

template <typename T>
void ListSequence<T>::resize_Internal(int new_size) {
    core->resize(new_size);
}

template <typename T>
ListSequence<T>* ListSequence<T>::concat(Sequence<T>& other) {
    ListSequence<T>* instance = Instance();
    for (int i = 0; i < other.get_size(); ++i) {
        instance->push_back(other.get(i));
    }
    return instance;
}

template <typename T>
ListSequence<T>* ListSequence<T>::sub_seq(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex > static_cast<int>(this->get_size()) || endIndex > startIndex) {
        throw Exception(ErrorCode::invalid_argument);
    }
    ListSequence<T>* newListSeq = Factory();
    for (int i = startIndex; i <= endIndex; ++i) {
        newListSeq->push_back(this->get(i));
    }
    return newListSeq;
}

template <typename T>
ListSequence<T>* ListSequence<T>::map(T(*func)(const T&)) {
    ListSequence<T>* seq = Instance();

    for (size_t i = 0; i < this->get_size(); ++i) {
        seq->set(func((*core)[i]), i);
    }

    return seq;
}

template <typename T>
ListSequence<T>* ListSequence<T>::where(bool (*predicate)(const T&)) const {
    ListSequence<T>* seq = Factory();
    for (size_t i = 0; i < this->get_size(); ++i) {
        if (predicate((*core)[i])) {
            seq->push_back((*core)[i]);
        }
    }

    return seq;
}

template <typename T>
int ListSequence<T>::find(T element) const {
    for (int i = 0; i < this->get_size(); ++i) {
        if (element == this->get(i)) {
            return i;
        }
    }
    return -1;
}

template <typename T>
int ListSequence<T>::count(T element) const {
    int count = 0;
    for (int i = 0; i < this->get_size(); ++i) {
        if (element == this->get(i)) {
            count++;
        }
    }
    return count;
}

template <typename T>
ListSequence<T>* ListSequence<T>::clear() {
    ListSequence<T>* instance = Instance();
    instance->clear_Internal();
    return instance;
}

template <typename T>
void ListSequence<T>::clear_Internal() {
    core->clear();
}

template <typename T>
T ListSequence<T>::operator[](int index) const {
    return core->operator[](index);
}

