#include "Stack.hpp"


template <typename T>
Stack<T>::~Stack() {
    array.clear();
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) : Stack<T>() {
    ArraySequence<T>* arseq = new MutableArraySequence<T>();
    for (int i = 0; i < other.array.get_size(); ++i) {
        arseq->push_back(other.array[i]);
    }
    for (int i = 0; i < arseq->get_size(); ++i) {
        this->push((*arseq)[i]);
    }
}


template <typename T>
T Stack<T>::top() const {
    if (array.get_size() == 0) {
        throw Exception(ErrorCode::out_of_range);
    }
    return array[array.get_size() - 1];
}

template <typename T>
T Stack<T>::pop() {
    if (array.get_size() == 0) {
        throw Exception(ErrorCode::out_of_range);
    }
    T top = array[array.get_size() - 1];
    array.pop_back();
    return top;
}

template <typename T>
void Stack<T>::push(const T& item) {
    array.push_back(item);
}

template <typename T>
size_t Stack<T>::size() const {
    return array.get_size();
}

template <typename T>
bool Stack<T>::empty() const {
    return this->size() == 0;
}

template <typename T>
void Stack<T>::clear() {
    this->array.clear();
}



template <typename T>
Stack<T> Stack<T>::map(T(*modifier)(const T&)) {
    Stack<T> newStack;
    ArraySequence<T>* modified_array = array.map(modifier);
    for (int i = 0; i < modified_array->get_size(); ++i) {
        newStack.push((*modified_array)[i]);
    }
    return newStack;
}

template <typename T>
Stack<T> Stack<T>::where(bool (*predicate)(const T&)) const {
    Stack<T> newStack;
    ArraySequence<T>* modified_array = array.where(predicate);
    for (int i = 0; i < modified_array->get_size(); ++i) {
        newStack.push((*modified_array)[i]);
    }
    return newStack;
}

template <typename T>
template <typename U>
U Stack<T>::reduce(U accumulator, U (*reduceFunc)(const U&, const T&)) const {
    U value = accumulator;
    for (int i = 0; i < array.get_size(); ++i) {
        value = reduceFunc(value, array[i]);
    }
    return value;
}

template <typename T>
void Stack<T>::concat(Stack<T> other) {
    for (int i = 0; i < other.array.get_size(); ++i) {
        this->push(other.array[i]);
    }
}

template <typename T>
Stack<T> Stack<T>::get_substack(int startIndex, int endIndex) {
    if (startIndex < 0 || endIndex >= array.get_size() || startIndex > endIndex) {
        throw Exception(ErrorCode::invalid_argument);
    }

    Stack<T> substack;
    for (int i = startIndex; i <= endIndex; ++i) {
        substack.push(array[i]);
    }
    return substack;
}

template <typename T>
bool Stack<T>::contains_substack(const Stack<T>& substack) {
    if (substack.empty() || substack.size() > this->size()) {
        return false;
    }
    int j = 0;
    for (int i = 0; i < this->size(); ++i) {
        if (j == substack.size()) {
            return true;
        }
        if (substack.array[j] == (this->array)[i]){
            j++;
        }
        else {
            j = 0;
        }
    }
    return j == substack.size();
}
