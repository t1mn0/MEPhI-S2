#include "LinkedList.hpp"
#include "Exception.hpp"



// -----------------------------------------------------------------------------------------------------------------
// Constructors and destructor

template<typename T>
LinkedList<T>::LinkedList() {
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;
};

template<typename T>
LinkedList<T>::LinkedList(int size, const T& default_element) :LinkedList() {
	if (size < 0) {
		throw Exception(ErrorCode::invalid_argument);
	}
	else {
		for (int i = 0; i < size; ++i) {
			this->push_back(default_element);
		}
	}
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) :LinkedList() {
	if (other.head != nullptr) {
		Node* current = other.head;

		while (current != nullptr) {
			this->push_back(current->data);
			current = current->next;
		}
	}
	else {
		throw Exception(ErrorCode::empty_container_error);
	}
}

template<typename T>
LinkedList<T>::LinkedList(const DynamicArray<T>& other) : LinkedList() {
	for (int i = 0; i < static_cast<int>(other.get_size()); ++i) {
		this->push_back(other.get(i));
	}
}

template<typename T>
LinkedList<T>::~LinkedList() {
	this->clear();
	this->head = nullptr;
	this->tail = nullptr;
}



// -----------------------------------------------------------------------------------------------------------------
// Basic methods

template<typename T>
size_t LinkedList<T>::get_size() const {
	return this->size;
}

template<typename T>
bool LinkedList<T>::empty() const {
	if (this->get_size() == 0) {
		return true;
	}
	return false;
}

template<typename T>
T LinkedList<T>::front() const {
	if (this->empty()) {
		throw Exception(ErrorCode::empty_container_error);
	}
	return this->head->data;
}

template<typename T>
T LinkedList<T>::back() const {
	if (this->empty()) {
		throw Exception(ErrorCode::empty_container_error);
	}
	return this->tail->data;
}

template<typename T>
void LinkedList<T>::push_back(const T& item) {
	Node* new_tail = new Node(item);
	if (this->head == nullptr) {
		this->head = new_tail;
		this->tail = this->head;
	}
	else {
		this->tail->next = new_tail;
		this->tail = new_tail;
	}
	this->size += 1;
}

template<typename T>
void LinkedList<T>::push_front(const T& item) {
	Node* new_head = new Node(item);
	if (this->head == nullptr) {
		this->head = new_head;
		this->tail = this->head;
	}
	else {
		new_head->next = this->head;
		this->head = new_head;
	}
	this->size += 1;
}

template<typename T>
void LinkedList<T>::pop_back() {
	if (this->empty()) {
		throw Exception(ErrorCode::empty_container_error);
	}
	else {
		if (this->get_size() == 1) {
			Node* tmp = this->head;
			this->head = nullptr;
			this->tail = nullptr;
			delete tmp;
			this->size--;
		}
		else if (this->get_size() == 2) {
			Node* tmp = this->head->next;
			this->head->next = nullptr;
			this->tail = this->head;
			delete tmp;
			this->size--;
		}
		else {
			Node* current = this->head;
			for (int i = 0; i < this->get_size() - 2; ++i) {
				current = current->next;
			}
			Node* tmp = current->next;
			current->next = nullptr;
			this->tail = current;
			delete tmp;
			this->size--;
		}
	}
}

template<typename T>
void LinkedList<T>::pop_front() {
	if (this->empty()) {
		throw Exception(ErrorCode::empty_container_error);
	}
	Node* tmp = this->head;
	this->head = this->head->next;
	delete tmp;
	this->size--;
}

template<typename T>
void LinkedList<T>::resize(int new_size) {
	if (new_size < 0) {
		throw Exception(ErrorCode::invalid_argument);
	}
	else if (new_size == 0) {
		this->clear();
	}
	else if (new_size < static_cast<int>(this->get_size())) {
		int diff = static_cast<int>(this->get_size()) - new_size;
		for (int i = 0; i < diff; ++i) {
			this->pop_back();
		}
	}
	else if (new_size > static_cast<int>(this->get_size())) {
		throw Exception(ErrorCode::insufficient_arguments_error);
	}
}

template<typename T>
void LinkedList<T>::resize(int new_size, const T& default_element) {
	if (new_size < 0) {
		throw Exception(ErrorCode::invalid_argument);
	}
	else if (new_size == 0) {
		this->clear();
	}
	else if (new_size < static_cast<int>(this->get_size())) {
		int diff = static_cast<int>(this->get_size()) - new_size;
		for (int i = 0; i < diff; ++i) {
			this->pop_back();
		}
	}
	else if (new_size > static_cast<int>(this->get_size())) {
		int diff = new_size - static_cast<int>(this->get_size());
		for (int i = 0; i < diff; ++i) {
			this->push_back(default_element);
		}
	}
}

template<typename T>
T LinkedList<T>::get(int index) const {
	if (index < 0 || index >= static_cast<int>(this->get_size())) {
		throw Exception(ErrorCode::invalid_argument);
	}
	return (*this)[index];
}

template<typename T>
void LinkedList<T>::set(const T& item, int index) {
	if (index < 0 || index >= static_cast<int>(this->get_size())) {
		throw Exception(ErrorCode::invalid_argument);
	}
	Node* current = this->head;
	for (int i = 0; i < index; ++i) {
		current = current->next;
	}
	current->data = item;
}



// -----------------------------------------------------------------------------------------------------------------
// Iterators

template<typename T>
typename T LinkedList<T>::Iterator::operator*() const {
	if (current == nullptr) {
		throw Exception(ErrorCode::dereference_nullptr);
	}
	return current->data;
}

template<typename T>
void LinkedList<T>::Iterator::operator++() {
	if (current == nullptr) {
		throw Exception(ErrorCode::dereference_nullptr);
	}
	current = current->next;
}

template<typename T>
bool LinkedList<T>::Iterator::operator!=(const typename LinkedList<T>::Iterator& other) const {
	return (current != other.current);
}

template<typename T>
bool LinkedList<T>::Iterator::operator==(const typename LinkedList<T>::Iterator& other) const {
	return (this->current == other.current);
};



// -----------------------------------------------------------------------------------------------------------------
// Operations with iterators

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() const {
	return Iterator(head);
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() const {
	return Iterator(nullptr);
}

template<typename T>
void LinkedList<T>::insert(const T& item, const Iterator iter) {
	if (head == nullptr) {
		throw Exception(ErrorCode::empty_container_error);
	}
	if (iter.current == nullptr) {
		throw Exception(ErrorCode::invalid_argument);
	}
	Node* curr = new Node(item);
	if (iter.current == this->head) {
		curr->next = this->head;
		this->head = curr;
		if (size == 0) {
			this->tail = curr;
		}
	}
	else {
		Node* prev = this->head;
		while (prev->next != iter.current) {
			prev = prev->next;
		}
		curr->next = iter.current;
		prev->next = curr;
	}
	size++;
}

template<typename T>
void LinkedList<T>::erase(Iterator& iter) {
	if (head == nullptr) {
		throw Exception(ErrorCode::empty_container_error);
	}
	if (iter.current == nullptr) {
		throw Exception(ErrorCode::invalid_argument);
	}

	if (iter.current == head) {
		Node* tmp = head;
		iter.current = head->next;
		head = head->next;
		delete tmp;
		if (head == nullptr) {
			tail = nullptr;
		}
	}
	else {
		Node* prev = head;
		while (prev != nullptr && prev->next != iter.current) {
			prev = prev->next;
		}

		Node* tmp = prev->next;
		prev->next = tmp->next;
		iter.current = tmp->next;

		if (tmp == tail) {
			tail = prev;
		}

		delete tmp;
	}
	size--;
}



// -----------------------------------------------------------------------------------------------------------------
// Other

template<typename T>
void LinkedList<T>::clear() {
	Node* curr = this->head;
	int size = static_cast<int>(this->size);
	for (int i = 0; i < size; ++i) {
		this->pop_front();
	}
}


template<typename T>
T LinkedList<T>::operator[](int index) const {
	if (index < 0 || index >= static_cast<int>(this->get_size())) {
		throw Exception(ErrorCode::invalid_argument);
	}
	auto curr = this->begin();
	for (int i = 0; i < index; ++i) {
		++curr;
	}
	return *curr;
}