#pragma once

#include "ListSequence.hpp"

template <typename T>
class ImmutableListSequence : public ListSequence<T> {
public:
	ImmutableListSequence(int size, const T& item) : ListSequence<T>(size, item) {}
	ImmutableListSequence() : ListSequence<T>() {}
	ImmutableListSequence(const ArraySequence<T>& other) : ListSequence<T>(other) {}
	ImmutableListSequence(const ListSequence<T>& other) : ListSequence<T>(other) {}

	ListSequence<T>* Instance() override {
		return new ImmutableListSequence(*this);
	}
	ListSequence<T>* Factory() const override {
		return new ImmutableListSequence();
	}
	ListSequence<T>* Factory(int size, const T& item) const override {
		return new ImmutableListSequence(size, item);
	}

};