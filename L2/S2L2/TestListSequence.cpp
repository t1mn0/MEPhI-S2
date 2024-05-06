#include <cassert>
#include <iostream>
#include "ImmutableListSequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "MutableListSequence.hpp"
#include "MutableArraySequence.hpp"

void TestConstructorsAndDestructors_LS() {
	ListSequence<int>* mls_1 = new MutableListSequence<int>();
	ListSequence<double>* mls_2 = new MutableListSequence<double>();
	ListSequence<char>* imls_3 = new ImmutableListSequence<char>();
	ListSequence<int*>* imls_4 = new ImmutableListSequence<int*>();
	assert(mls_1->empty());
	assert(mls_2->empty());
	assert(imls_3->empty());
	assert(imls_4->empty());
	mls_1->~ListSequence();
	mls_2->~ListSequence();
	imls_3->~ListSequence();
	imls_4->~ListSequence();
	ListSequence<int>* mls_5 = new MutableListSequence<int>(10, 10);
	ListSequence<int>* mls_6 = new MutableListSequence<int>(*mls_5);
	ArraySequence<int>* mas_0 = new MutableArraySequence<int>(15, 10);
	ArraySequence<int>* imas_0 = new ImmutableArraySequence<int>(10, 0);
	ListSequence<int>* mls_7 = new MutableListSequence<int>(*mas_0);
	ListSequence<int>* imls_8 = new ImmutableListSequence<int>(*imas_0);
	assert(mls_5->get_size() == 10);
	assert(mls_6->get_size() == 10);
	assert(mls_7->get_size() == 15);
	assert(imls_8->get_size() == 10);

	for (int i = 0; i < 10; ++i) {
		assert((*mls_5)[i] == (*mls_6)[i]);
	}

	for (int i = 0; i < 15; ++i) {
		assert((*mls_7)[i] == (*mas_0)[i] && (*mls_7)[i] == 10);
	}

	for (int i = 0; i < 10; ++i) {
		assert((*imls_8)[i] == (*imas_0)[i] && (*imls_8)[i] == 0);
	}

	mls_5->~ListSequence();
	mls_6->~ListSequence();
	mls_7->~ListSequence();
	imls_8->~ListSequence();

	try {
		ImmutableListSequence<int>* imls_7 = new ImmutableListSequence<int>(-10, 0);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void TestIterators_LS() {
	MutableListSequence<double>* mls = new MutableListSequence<double>(5, 99);
	int i = 0;
	for (auto iter = mls->begin(); iter != mls->end(); ++iter) {
		assert(*iter == mls->get(i));
		i++;
	}
	auto iter = mls->begin(); ++iter; ++iter;
	mls->insert(100, iter);
	++iter;
	++iter;
	mls->insert(100, iter);
	mls->insert(100, iter);
	iter = mls->begin();
	mls->erase(iter);
	mls->erase(iter);
	i = 0;
	for (auto iter = mls->begin(); iter != mls->end(); ++iter) {
		assert(*iter == mls->get(i));
		i++;
	}
}

void TestBaseOperations_LS() {
	ListSequence<int>* mls = new MutableListSequence<int>(10, 10);

	for (int i = 0; i < 10; ++i) {
		mls->set(i + 1, i);
	}


	for (int i = 0; i < 10; ++i) {
		assert((*mls)[i] == mls->get(i) && mls->get(i) == i + 1);
	}

	mls->pop_back();
	mls->pop_back();
	mls->pop_front();
	mls->pop_front();
	mls->pop_back();
	assert((*mls)[0] == mls->get(0) && mls->get(0) == mls->front());
	assert((*mls)[4] == mls->get(4) && mls->get(4) == mls->back());
	mls->push_front(-2);
	mls->push_front(-1);
	mls->push_back(-8);
	mls->push_back(-9);
	mls->push_back(-10);
	assert((*mls)[0] == mls->get(0) && mls->get(0) == -1);
	assert((*mls)[1] == mls->get(1) && mls->get(1) == -2);
	assert((*mls)[7] == mls->get(7) && mls->get(7) == -8);
	assert((*mls)[8] == mls->get(8) && mls->get(8) == -9);
	assert((*mls)[9] == mls->get(9) && mls->get(9) == -10);

	mls->clear();

	// -----------------------------------------------------------------------------------------------------------------

	ListSequence<int>* imls = new ImmutableListSequence<int>(10, 10);

	for (int i = 0; i < 10; ++i) {
		imls->set(i + 1, i);
	}

	for (int i = 0; i < 10; ++i) {
		assert((*imls)[i] == imls->get(i) && imls->get(i) == 10);
	}

	imls->pop_back();
	imls->pop_back();
	imls->pop_front();
	imls->pop_front();
	imls->pop_back();
	assert((*imls)[0] == imls->get(0) && imls->get(0) == imls->front());
	assert((*imls)[4] == imls->get(imls->get_size() - 1) && imls->get(imls->get_size() - 1) == imls->back());
	imls->push_front(-2);
	imls->push_front(-1);
	imls->push_back(-8);
	imls->push_back(-9);
	imls->push_back(-10);
	assert((*imls)[0] == imls->get(0) && imls->get(0) == 10);
	assert((*imls)[1] == imls->get(1) && imls->get(1) == 10);
	assert((*imls)[7] == imls->get(7) && imls->get(7) == 10);
	assert((*imls)[8] == imls->get(8) && imls->get(8) == 10);
	assert((*imls)[9] == imls->get(9) && imls->get(9) == 10);

	imls->clear();

	assert(!imls->empty());
}

void TestBorder—ases_BOLS() {
	ListSequence<int>* ls = new MutableListSequence<int>();

	// Test empty list
	try {
		ls->pop_back();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ls->pop_front();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ls->front();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ls->back();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ls->set(1, 1);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ls->get(5);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ls->get(0);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		(*ls)[-1];
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		(*ls)[0];
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		(*ls)[50];
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	// Test filled list
	try {
		ls->resize(50);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	ls->resize(20, 0);

	try {
		for (int i = 0; i < 30; ++i) {
			ls->pop_back();
		}
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	ls->resize(20, 0);

	try {
		for (int i = 0; i < 30; ++i) {
			ls->pop_front();
		}
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ls->resize(-10, 90);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ls->resize(-10);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	ls->resize(20, 0);

	for (int i = 0; i < 30; ++i) {
		try {
			ls->get(i);
		}
		catch (...) {
			if (i >= 20) assert(true);
			else assert(false);
		}
	}

	for (int i = 0; i < 30; ++i) {
		try {
			ls->set(-(i + 1), i);
		}
		catch (...) {
			if (i >= 20) assert(true);
			else assert(false);
		}
	}
}

void TestMethods_LS() {
	MutableListSequence<int>* mls_1 = new MutableListSequence<int>(5, 100);
	MutableListSequence<int>* mls_2 = new MutableListSequence<int>(5, 200);
	mls_1->concat(*mls_2);
	assert(mls_1->get_size() == 10);
	for (int i = 0; i < 5; ++i) {
		assert(mls_1->get(i) == 100);
		assert(mls_1->get(i + 5) == 200);
	}
	assert(mls_2->get_size() == 5);
	for (int i = 0; i < 5; ++i) {
		assert(mls_2->get(i) == 200);
	}
	ImmutableListSequence<int>* imls_1 = new ImmutableListSequence<int>(5, 100);
	ImmutableListSequence<int>* imls_2 = new ImmutableListSequence<int>(5, 200);
	imls_1->concat(*imls_2);
	assert(imls_1->get_size() == 5);
	for (int i = 0; i < 5; ++i) {
		assert(imls_1->get(i) == 100);
	}
	assert(imls_2->get_size() == 5);
	for (int i = 0; i < 5; ++i) {
		assert(imls_2->get(i) == 200);
	}

	imls_1->map([](const auto& item) -> auto { return item * 2; });
	assert(imls_1->get_size() == 5);
	for (int i = 0; i < 5; ++i) {
		assert(imls_1->get(i) == 100);
	}

	mls_2->map([](const auto& item) -> auto { return item * 2; });
	assert(mls_2->get_size() == 5);
	for (int i = 0; i < 5; ++i) {
		assert(mls_2->get(i) == 400);
	}

	mls_1->resize(5, 5);
	assert(mls_1->get_size() == 5);
	for (int i = 0; i < 5; ++i) {
		assert(mls_1->get(i) == 100);
	}

	mls_2->resize(10, 15);
	assert(mls_2->get_size() == 10);
	for (int i = 0; i < 5; ++i) {
		assert(mls_2->get(i) == 400);
		assert(mls_2->get(i + 5) == 15);
	}

	assert(mls_2->find(15) == 5);
	assert(imls_2->count(200) == 5);

	ListSequence<int>* seq = mls_2->where([](const int& item) -> bool { return item % 10 == 5; });
	assert(seq->get_size() == 5);
	for (int i = 0; i < 5; ++i) {
		assert(seq->get(i) == 15);
	}
}

void TestListSequence() {
	TestConstructorsAndDestructors_LS();
	TestIterators_LS();
	TestBaseOperations_LS();
	TestBorder—ases_BOLS();
	TestMethods_LS();
}