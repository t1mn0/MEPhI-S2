#pragma once

#include "ArraySequence.hpp"

template <typename T>
class MutableArraySequence : public ArraySequence<T> {
private:
	DynamicArray<T>* core = new DynamicArray<T>;
public:
	MutableArraySequence(int size, const T& item) : ArraySequence<T>(size, item) {}
	MutableArraySequence() : ArraySequence<T>() {}
	MutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {}
	MutableArraySequence(const ListSequence<T>& other) : ArraySequence<T>(other) {}
	ArraySequence<T>* Instance() override {
		return this;
	}
	ArraySequence<T>* Factory() const override {
		return new MutableArraySequence();
	}
	ArraySequence<T>* Factory(int size, const T& item) const {
		return new MutableArraySequence(size, item);
	}
};