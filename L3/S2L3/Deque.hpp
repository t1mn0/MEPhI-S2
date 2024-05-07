#pragma once

#include "../../../../L2/S2L2/Sequence.hpp"
#include "../../../../L2/S2L2/MutableListSequence.hpp"
#include "../../../../L2/S2L2/Exception.hpp"

template <typename T>
class Deque {
private:
	MutableListSequence<T> list;
public:
	Deque() : list() {}
	Deque(MutableListSequence<T> list) : list(list) {}
	Deque(const Deque<T>& other);
	~Deque();

	T front() const;
	T back() const;
	void push_front(const T& item);
	void push_back(const T& item);
	T pop_front();
	T pop_back();
	size_t size() const;
	bool empty() const;
	void clear();

	Deque<T> map(T(*modifier)(const T&));
	Deque<T> where(bool (*predicate)(const T&)) const;
	T reduce(T accumulator, T(*reduceFunc)(const T&, const T&)) const;
	void concat(Deque<T> other);
	Deque<T> get_subdeque(int startIndex, int endIndex);
	bool contains_subdeque(const Deque<T>& subqueue);
};

#include "Deque.cpp"