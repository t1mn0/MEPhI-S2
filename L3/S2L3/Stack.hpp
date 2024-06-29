#pragma once

#include "../../L2/S2L2/Sequence.hpp"
#include "../../L2/S2L2/MutableArraySequence.hpp"
#include "../../L2/S2L2/Exception.hpp"

template <typename T>
class Stack {
private:
	MutableArraySequence<T> array;
public:
	Stack() : array() {}
	Stack(MutableArraySequence<T> array) : array(array) {}
	Stack(const Stack<T>& other);
	~Stack();


	T top() const;
	T pop();
	void push(const T& item);
	size_t size() const;
	bool empty() const;
	void clear();

	Stack<T> map(T (*modifier)(const T&));
	Stack<T> where(bool (*predicate)(const T&)) const;
	template <typename U>
	U reduce(U accumulator, U (*reduceFunc)(const U&, const T&)) const;
	void concat(Stack<T> other);
	Stack<T> get_substack(int startIndex, int endIndex);
	bool contains_substack(const Stack<T>& substack);
};

#include "Stack.cpp"