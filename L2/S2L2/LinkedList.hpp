#pragma once

template <typename T>
class DynamicArray;

template<typename T>
class LinkedList {
public:
	struct Node {
		T data;
		Node* next = nullptr;
		Node(const T& data) : data(data) {};
	};

	class Iterator {
	public:
		Node* current;
		Iterator(Node* node) : current(node) {};
		T operator*() const;
		void operator++();
		bool operator!=(const Iterator& other) const;
		bool operator==(const Iterator& other) const;
	};

	LinkedList();
	LinkedList(int size, const T& default_element);
	LinkedList(const LinkedList<T>& other);
	LinkedList(const DynamicArray<T>& other);
	~LinkedList();

	size_t get_size() const;
	bool empty() const;
	T front() const;
	T back() const;
	void push_back(const T& item);
	void push_front(const T& item);
	void pop_back();
	void pop_front();

	Iterator begin() const;
	Iterator end() const;
	T get(int index) const;
	void set(const T& item, int index);
	void insert(const T& item, const Iterator iter);
	void erase(Iterator& iter);

	void resize(int new_size);
	void resize(int new_size, const T& default_element);
	void clear();

	T operator[](int index) const;

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;
};



#include "LinkedList.cpp"