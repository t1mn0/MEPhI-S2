#include "Deque.hpp"



template <typename T>
Deque<T>::~Deque() {
    list.clear();
}

template <typename T>
Deque<T>::Deque(const Deque<T>& other) : Deque<T>() {
    ListSequence<T>* listseq = new MutableListSequence<T>();
    for (int i = 0; i < other.list.get_size(); ++i) {
        listseq->push_back(other.list[i]);
    }
    for (int i = 0; i < listseq->get_size(); ++i) {
        this->push_back((*listseq)[i]);
    }
}

template <typename T>
T Deque<T>::front() const {
    if (list.get_size() == 0) {
        throw Exception(ErrorCode::out_of_range);
    }
    return list[0];
}

template <typename T>
T Deque<T>::back() const {
    if (list.get_size() == 0) {
        throw Exception(ErrorCode::out_of_range);
    }
    return list[list.get_size() - 1];
}

template <typename T>
T Deque<T>::pop_front() {
    if (empty()) {
        throw Exception(ErrorCode::out_of_range);
    }
    T front = list[0];
    list.pop_front();
    return front;
}

template <typename T>
T Deque<T>::pop_back() {
    if (empty()) {
        throw Exception(ErrorCode::out_of_range);
    }
    T back = list[list.get_size() - 1];
    list.pop_back();
    return back;
}

template <typename T>
void Deque<T>::push_front(const T& item) {
    list.push_front(item);
}

template <typename T>
void Deque<T>::push_back(const T& item) {
    list.push_back(item);
}

template <typename T>
size_t Deque<T>::size() const {
    return list.get_size();
}

template <typename T>
bool Deque<T>::empty() const {
    return this->size() == 0;
}

template <typename T>
void Deque<T>::clear() {
    this->list.clear();
}


template <typename T>
Deque<T> Deque<T>::map(T(*modifier)(const T&)) {
    Deque<T> newDeque;
    ListSequence<T>* modified_list = list.map(modifier);
    for (int i = 0; i < modified_list->get_size(); ++i) {
        newDeque.push_back((*modified_list)[i]);
    }
    return newDeque;
}

template <typename T>
Deque<T> Deque<T>::where(bool (*predicate)(const T&)) const {
    Deque<T> newDeque;
    ListSequence<T>* modified_list = list.where(predicate);
    for (int i = 0; i < modified_list->get_size(); ++i) {
        newDeque.push_back((*modified_list)[i]);
    }
    return newDeque;
}

template <typename T>
T Deque<T>::reduce(T accumulator, T(*reduceFunc)(const T&, const T&)) const {
    T value = accumulator;
    for (int i = 0; i < list.get_size(); ++i) {
        value = reduceFunc(value, list[i]);
    }
    return value;
}

template <typename T>
void Deque<T>::concat(Deque<T> other) {
    for (int i = 0; i < other.list.get_size(); ++i) {
        this->push_back(other.list[i]);
    }
}

template <typename T>
Deque<T> Deque<T>::get_subdeque(int startIndex, int endIndex) {
    if (startIndex < 0 || endIndex >= list.get_size() || startIndex > endIndex) {
        throw Exception(ErrorCode::invalid_argument);
    }

    Deque<T> subdeque;
    for (int i = startIndex; i <= endIndex; ++i) {
        subdeque.push_back(list[i]);
    }
    return subdeque;
}

template <typename T>
bool Deque<T>::contains_subdeque(const Deque<T>& subdeque) {
    if (subdeque.empty() || subdeque.size() > this->size()) {
        return false;
    }
    int j = 0;
    for (int i = 0; i < this->size(); ++i) {
        if (j == subdeque.size()) {
            return true;
        }
        if (subdeque.list[j] == (this->list)[i]) {
            j++;
        }
        else {
            j = 0;
        }
    }
    return j == subdeque.size();
}
