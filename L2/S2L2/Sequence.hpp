#pragma once

template<typename T>
class Sequence {
public:
	class Iterator {
	public:
		virtual T operator*() const = 0;
		virtual void operator++() = 0;
	};

	virtual size_t get_size() const = 0;

	bool empty() const;
	T front() const;
	T back() const;

	virtual Sequence<T>* push_back(const T& item) = 0;
	virtual Sequence<T>* push_front(const T& item) = 0;
	virtual Sequence<T>* pop_back() = 0;
	virtual Sequence<T>* pop_front() = 0;

	virtual T get(int index) const = 0;

	virtual Sequence<T>* set(const T& item, int index) = 0;

	//virtual typename Iterator& begin() const = 0;
	//virtual typename Iterator& end() const = 0;

	virtual Sequence<T>* insert(const T& item, Iterator& iter) = 0;
	virtual Sequence<T>* erase(Iterator& iter) = 0;

	virtual Sequence<T>* resize(int new_size) = 0;
	virtual Sequence<T>* resize(int new_size, const T& default_element) = 0;
	virtual Sequence<T>* sub_seq(int startIndex, int endIndex) const = 0;
	virtual Sequence<T>* map(T(*func)(const T&)) = 0;
	virtual Sequence<T>* where(bool (*predicate)(const T&)) const = 0;
	virtual int find(T element) const = 0;
	virtual int count(T element) const = 0;
	virtual Sequence<T>* concat(Sequence<T>& other) = 0;
	virtual Sequence<T>* clear() = 0;

	virtual T operator[](int index) const = 0;
	virtual Sequence<T>* Instance() = 0;
	virtual Sequence<T>* Factory() const = 0;
	virtual Sequence<T>* Factory(int size, const T& item) const = 0;
};



#include "Sequence.cpp"