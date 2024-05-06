#include "DynamicArray.hpp"
#include "Exception.hpp"



// -----------------------------------------------------------------------------------------------------------------
// Reallocation

template<typename T>
void DynamicArray<T>::reallocation() {
	if (this->size == this->capacity) {
		size_t new_capacity = this->capacity == 0 ? 1 : this->capacity *= 2;
		T* new_array = new T[new_capacity];
		for (size_t i = 0; i < this->size; ++i) {
			new_array[i] = this->array[i];
		}
		delete[] array;
		this->array = new_array;
		this->capacity = new_capacity;
	}
}



// -----------------------------------------------------------------------------------------------------------------
// Constructors and destructor

template<typename T>
DynamicArray<T>::DynamicArray() {
	this->array = nullptr;
	this->size = 0;
	this->capacity = 0;
};

template<typename T>
DynamicArray<T>::DynamicArray(int size, const T& default_element) : DynamicArray() {
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
DynamicArray<T>::DynamicArray(const LinkedList<T>& other) : DynamicArray() {
	for (int i = 0; i < static_cast<int>(other.get_size()); ++i) {
		this->push_back(other.get(i));
	}
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) : DynamicArray() {
	for (int i = 0; i < static_cast<int>(other.get_size()); ++i) {
		this->push_back(other.get(i));
	}
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
	delete[] this->array;
}



// -----------------------------------------------------------------------------------------------------------------
// Iterators

template<typename T>
T DynamicArray<T>::Iterator::operator*() const {
	if (current == nullptr) {
		throw Exception(ErrorCode::dereference_nullptr);
	}
	else {
		return *current;
	}
}

template<typename T>
void DynamicArray<T>::Iterator::operator++() {
	if (current == nullptr) {
		throw Exception(ErrorCode::dereference_nullptr);
	}
	else {
		current++;
	}
}

template<typename T>
bool DynamicArray<T>::Iterator::operator!=(const typename DynamicArray<T>::Iterator::Iterator& other) const {
	return (current != other.current);
}

template<typename T>
bool DynamicArray<T>::Iterator::operator==(const typename DynamicArray<T>::Iterator::Iterator& other) const {
	return (current == other.current);
}



// -----------------------------------------------------------------------------------------------------------------
// Basic methods

template<typename T>
size_t DynamicArray<T>::get_size() const {
	return this->size;
}

template<typename T>
bool DynamicArray<T>::empty() const {
	if (this->get_size() == 0) {
		return true;
	}
	return false;
}


template<typename T>
T DynamicArray<T>::front() const {
	if (this->empty()) {
		throw Exception(ErrorCode::empty_container_error);
	}
	return *array;
}

template<typename T>
T DynamicArray<T>::back() const {
	if (this->empty()) {
		throw Exception(ErrorCode::empty_container_error);
	}
	return *(array + size - 1);
}

template<typename T>
void DynamicArray<T>::push_back(const T& item) {
	reallocation();
	this->array[this->size] = item;
	this->size++;
}

template<typename T>
void DynamicArray<T>::push_front(const T& item) {
	if (this->size >= this->capacity) {
		this->capacity *= 2;
		T* new_array = new T[this->capacity];
		new_array[0] = item;
		for (size_t i = 0; i < this->size; ++i) {
			new_array[i + 1] = this->array[i];
		}
		delete[] this->array;
		this->array = new_array;
	}
	else {
		for (size_t i = this->size; i > 0; --i) {
			this->array[i] = this->array[i - 1];
		}
		this->array[0] = item;
	}
	this->size++;
}


template<typename T>
void DynamicArray<T>::pop_back() {
	if (this->empty()) {
		throw Exception(ErrorCode::empty_container_error);
	}
	else {
		this->capacity--;
		T* new_array = new T[this->capacity];
		for (size_t i = 0; i < this->size - 1; ++i) {
			new_array[i] = this->array[i];
		}
		delete[] this->array;
		this->size--;
		this->array = new_array;
	}
}

template<typename T>
void DynamicArray<T>::pop_front() {
	if (this->empty()) {
		throw Exception(ErrorCode::empty_container_error);
	}
	else {
		this->capacity--;
		T* new_array = new T[this->capacity];
		for (size_t i = 1; i < this->size; ++i) {
			new_array[i - 1] = this->array[i];
		}
		delete[] this->array;
		this->size--;
		this->array = new_array;
	}
}

template<typename T>
void DynamicArray<T>::resize(int new_size) {
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
void DynamicArray<T>::resize(int new_size, const T& default_element) {
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
T DynamicArray<T>::get(int index) const {
	if (index < 0 || index >= static_cast<int>(this->get_size())) {
		throw Exception(ErrorCode::invalid_argument);
	}
	return (*this)[index];
}

template<typename T>
void DynamicArray<T>::set(const T& item, int index) {
	if (index < 0 || index >= static_cast<int>(this->get_size())) {
		throw Exception(ErrorCode::invalid_argument);
	}
	*(this->array + index) = item;
}



// -----------------------------------------------------------------------------------------------------------------
// Operations with iterators

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::begin() const {
	if (this->empty()) {
		throw Exception(ErrorCode::empty_container_error);
	}
	else {
		return Iterator(this->array);
	}
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::end() const {
	if (this->empty()) {
		throw Exception(ErrorCode::empty_container_error);
	}
	else {
		return Iterator(this->array + size);
	}
}

template<typename T>
void DynamicArray<T>::insert(const T& item, Iterator iter) {
	if (this->empty()) {
		throw Exception(ErrorCode::empty_container_error);
	}
	if (iter.current == nullptr) {
		throw Exception(ErrorCode::invalid_argument);
	}
	reallocation();
	T* insert_position = iter.current;
	for (T* i = this->array + this->size; i != insert_position; --i) {
		*i = *(i - 1);
	}
	*insert_position = item;
	this->size++;
}

template<typename T>
void DynamicArray<T>::erase(Iterator& iter) {
	if (this->empty()) {
		throw Exception(ErrorCode::empty_container_error);
	}
	if (iter.current == nullptr) {
		throw Exception(ErrorCode::invalid_argument);
	}

	T* erase_position = iter.current;
	for (T* i = erase_position; i != this->array + this->size - 1; ++i) {
		*i = *(i + 1);
	}

	this->size--;
}



// -----------------------------------------------------------------------------------------------------------------
// Other

template<typename T>
void DynamicArray<T>::clear() {
	delete[] this->array;
	this->array = nullptr;
	this->size = 0;
	this->capacity = 0;
}

template<typename T>
T DynamicArray<T>::operator[](int index) const {
	if (index < 0 || index >= static_cast<int>(this->get_size())) {
		throw Exception(ErrorCode::invalid_argument);
	}
	auto curr = this->begin();
	for (int i = 0; i < index; ++i) {
		++curr;
	}
	return *curr;
}