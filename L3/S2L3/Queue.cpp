#include "Queue.hpp"


template <typename T>
Queue<T>::~Queue() {
    list.clear();
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) : Queue<T>() {
    ListSequence<T>* listseq = new MutableListSequence<T>();
    for (int i = 0; i < other.list.get_size(); ++i) {
        listseq->push_back(other.list[i]);
    }
    for (int i = 0; i < listseq->get_size(); ++i) {
        this->push((*listseq)[i]);
    }
}

template <typename T>
T Queue<T>::front() const {
    if (list.get_size() == 0) {
        throw Exception(ErrorCode::out_of_range);
    }
    return list[0];
}

template <typename T>
T Queue<T>::pop() {
    if (empty()) {
        throw Exception(ErrorCode::out_of_range);
    }
    T front = list[0];
    list.pop_front();
    return front;
}

template <typename T>
void Queue<T>::push(const T& item) {
    list.push_back(item);
}

template <typename T>
size_t Queue<T>::size() const {
    return list.get_size();
}

template <typename T>
bool Queue<T>::empty() const {
    return this->size() == 0;
}

template <typename T>
void Queue<T>::clear() {
    this->list.clear();
}


template <typename T>
Queue<T> Queue<T>::map(T(*modifier)(const T&)) {
    Queue<T> newQueue;
    ListSequence<T>* modified_list = list.map(modifier);
    for (int i = 0; i < modified_list->get_size(); ++i) {
        newQueue.push((*modified_list)[i]);
    }
    return newQueue;
}

template <typename T>
Queue<T> Queue<T>::where(bool (*predicate)(const T&)) const {
    Queue<T> newQueue;
    ListSequence<T>* modified_list = list.where(predicate);
    for (int i = 0; i < modified_list->get_size(); ++i) {
        newQueue.push((*modified_list)[i]);
    }
    return newQueue;
}

template <typename T>
T Queue<T>::reduce(T accumulator, T(*reduceFunc)(const T&, const T&)) const {
    T value = accumulator;
    for (int i = 0; i < list.get_size(); ++i) {
        value = reduceFunc(value, list[i]);
    }
    return value;
}

template <typename T>
void Queue<T>::concat(Queue<T> other) {
    for (int i = 0; i < other.list.get_size(); ++i) {
        this->push(other.list[i]);
    }
}

template <typename T>
Queue<T> Queue<T>::get_subqueue(int startIndex, int endIndex) {
    if (startIndex < 0 || endIndex >= list.get_size() || startIndex > endIndex) {
        throw Exception(ErrorCode::invalid_argument);
    }

    Queue<T> subqueue;
    for (int i = startIndex; i <= endIndex; ++i) {
        subqueue.push(list[i]);
    }
    return subqueue;
}

template <typename T>
bool Queue<T>::contains_subqueue(const Queue<T>& subqueue) {
    if (subqueue.empty() || subqueue.size() > this->size()) {
        return false;
    }
    int j = 0;
    for (int i = 0; i < this->size(); ++i) {
        if (j == subqueue.size()) {
            return true;
        }
        if (subqueue.list[j] == (this->list)[i]) {
            j++;
        }
        else {
            j = 0;
        }
    }
    return j == subqueue.size();
}

template <typename T>
Pair<Queue<T>, Queue<T>> Queue<T>::divide(bool (*predicate)(const T&)) {
    MutableListSequence<T> seq1; // true
    MutableListSequence<T> seq2; // false

    for (int i = 0; i < list.get_size(); ++i) {
        if (predicate(list[i])) {
            seq1.push_back(list[i]);
        }
        else {
            seq2.push_back(list[i]);
        }
    }

    return Pair<Queue<T>, Queue<T>>(Queue(seq1), Queue(seq2));
}