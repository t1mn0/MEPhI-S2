#pragma once

#include "ListSequence.hpp"

template <typename T>
class MutableListSequence : public ListSequence<T> {
public:
	MutableListSequence(int size, const T& item) : ListSequence<T>(size, item) {}
	MutableListSequence() : ListSequence<T>() {}
	MutableListSequence(const ListSequence<T>& other) : ListSequence<T>(other) {}
	MutableListSequence(const ArraySequence<T>& other) : ListSequence<T>(other) {}
	ListSequence<T>* Instance() override {
		return this;
	}
	ListSequence<T>* Factory() const override {
		return new MutableListSequence();
	}
	ListSequence<T>* Factory(int size, const T& item) const override {
		return new MutableListSequence(size, item);
	}
};