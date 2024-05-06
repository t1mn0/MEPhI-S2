#pragma once

#include "ArraySequence.hpp"

template <typename T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
	ImmutableArraySequence(int size, const T& item) : ArraySequence<T>(size, item) {}
	ImmutableArraySequence() : ArraySequence<T>() {}
	ImmutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {}
	ImmutableArraySequence(const ListSequence<T>& other) : ArraySequence<T>(other) {}

	ArraySequence<T>* Instance() override {
		return new ImmutableArraySequence(*this);
	}
	ArraySequence<T>* Factory() const override {
		return new ImmutableArraySequence();
	}
	ArraySequence<T>* Factory(int size, const T& item) const {
		return new ImmutableArraySequence(size, item);
	}
};