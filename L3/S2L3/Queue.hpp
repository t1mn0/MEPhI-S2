#pragma once

#include "../../../../L2/S2L2/Sequence.hpp"
#include "../../../../L2/S2L2/MutableListSequence.hpp"
#include "../../../../L2/S2L2/Exception.hpp"
#include "Pair.hpp"

template <typename T>
class Queue {
private:
	MutableListSequence<T> list;
public:
	Queue() : list() {}
	Queue(MutableListSequence<T> list) : list(list) {}
	Queue(const Queue<T>& other);
	~Queue();

    T front() const;
    void push(const T& item);
    T pop();
    size_t size() const;
    bool empty() const;
	void clear();

	Queue<T> map(T(*modifier)(const T&));
	Queue<T> where(bool (*predicate)(const T&)) const;
	T reduce(T accumulator, T(*reduceFunc)(const T&, const T&)) const;
	void concat(Queue<T> other);
	Queue<T> get_subqueue(int startIndex, int endIndex);
	bool contains_subqueue(const Queue<T>& subqueue);
	Pair<Queue<T>, Queue<T>> divide(bool (*predicate)(const T&));
};

#include "Queue.cpp"