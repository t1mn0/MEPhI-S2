#include <cassert>
#include <iostream>
#include "ImmutableListSequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "MutableListSequence.hpp"
#include "MutableArraySequence.hpp"

void TestConstructorsAndDestructors_AS() {
	ArraySequence<int>* mas_1 = new MutableArraySequence<int>();
	ArraySequence<double>* mas_2 = new MutableArraySequence<double>();
	ArraySequence<char>* imas_3 = new ImmutableArraySequence<char>();
	ArraySequence<int*>* imas_4 = new ImmutableArraySequence<int*>();
	assert(mas_1->empty());
	assert(mas_2->empty());
	assert(imas_3->empty());
	assert(imas_4->empty());
	mas_1->~ArraySequence();
	mas_2->~ArraySequence();
	imas_3->~ArraySequence();
	imas_4->~ArraySequence();
	ArraySequence<int>* mas_5 = new MutableArraySequence<int>(10, 10);
	ArraySequence<int>* mas_6 = new MutableArraySequence<int>(*mas_5);
	ListSequence<int>* mls_0 = new MutableListSequence<int>(15, 10);
	ListSequence<int>* imls_0 = new ImmutableListSequence<int>(10, 0);
	ArraySequence<int>* mas_7 = new MutableArraySequence<int>(*mls_0);
	ArraySequence<int>* imas_8 = new ImmutableArraySequence<int>(*imls_0);
	assert(mas_5->get_size() == 10);
	assert(mas_6->get_size() == 10);
	assert(mas_7->get_size() == 15);
	assert(imas_8->get_size() == 10);

	for (int i = 0; i < 10; ++i) {
		assert((*mas_5)[i] == (*mas_6)[i]);
	}

	for (int i = 0; i < 15; ++i) {
		assert((*mas_7)[i] == (*mls_0)[i] && (*mas_7)[i] == 10);
	}

	for (int i = 0; i < 10; ++i) {
		assert((*imas_8)[i] == (*imls_0)[i] && (*imas_8)[i] == 0);
	}

	mas_5->~ArraySequence();
	mas_6->~ArraySequence();
	mas_7->~ArraySequence();
	imas_8->~ArraySequence();

	try {
		ImmutableArraySequence<int>* imas_9 = new ImmutableArraySequence<int>(-10, 0);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void TestIterators_AS() {
	MutableArraySequence<double>* mas = new MutableArraySequence<double>(5, 99);
	int i = 0;
	for (auto iter = mas->begin(); iter != mas->end(); ++iter) {
		//std::cout << (*iter) << " ";
		assert((*iter) == mas->get(i));
		i++;
	}
	auto iter = mas->begin(); ++iter; ++iter;
	mas->insert(100, iter);
	++iter;
	++iter;
	mas->insert(100, iter);
	mas->insert(100, iter);
	iter = mas->begin();
	mas->erase(iter);
	mas->erase(iter);
	i = 0;
	for (auto iter = mas->begin(); iter != mas->end(); ++iter) {
		assert(*iter == mas->get(i));
		i++;
	}

}

void TestBaseOperations_AS() {
	ArraySequence<int>* mas = new MutableArraySequence<int>(10, 10);

	for (int i = 0; i < 10; ++i) {
		mas->set(i + 1, i);
	}

	try {
		mas->get(15);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		mas->get(-1);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		mas->get(10);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	for (int i = 0; i < 10; ++i) {
		assert((*mas)[i] == mas->get(i) && mas->get(i) == i + 1);
	}

	try {
		mas->get(15);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	mas->pop_back();
	mas->pop_back();
	mas->pop_front();
	mas->pop_front();
	mas->pop_back();
	assert((*mas)[0] == mas->get(0) && mas->get(0) == mas->front());
	assert((*mas)[4] == mas->get(4) && mas->get(4) == mas->back());
	mas->push_front(-2);
	mas->push_front(-1);
	mas->push_back(-8);
	mas->push_back(-9);
	mas->push_back(-10);
	assert((*mas)[0] == mas->get(0) && mas->get(0) == -1);
	assert((*mas)[1] == mas->get(1) && mas->get(1) == -2);
	assert((*mas)[7] == mas->get(7) && mas->get(7) == -8);
	assert((*mas)[8] == mas->get(8) && mas->get(8) == -9);
	assert((*mas)[9] == mas->get(9) && mas->get(9) == -10);

	mas->clear();

	try {
		mas->get(15);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		mas->set(15, 0);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	// -----------------------------------------------------------------------------------------------------------------

	ArraySequence<int>* imas = new ImmutableArraySequence<int>(10, 10);

	for (int i = 0; i < 10; ++i) {
		imas->set(i + 1, i);
	}

	try {
		imas->get(15);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		imas->get(-1);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		imas->get(10);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	for (int i = 0; i < 10; ++i) {
		assert((*imas)[i] == imas->get(i) && imas->get(i) == 10);
	}

	try {
		mas->get(15);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	imas->pop_back();
	imas->pop_back();
	imas->pop_front();
	imas->pop_front();
	imas->pop_back();
	assert((*imas)[0] == imas->get(0) && imas->get(0) == imas->front());
	assert((*imas)[4] == imas->get(imas->get_size() - 1) && imas->get(imas->get_size() - 1) == imas->back());
	imas->push_front(-2);
	imas->push_front(-1);
	imas->push_back(-8);
	imas->push_back(-9);
	imas->push_back(-10);
	assert((*imas)[0] == imas->get(0) && imas->get(0) == 10);
	assert((*imas)[1] == imas->get(1) && imas->get(1) == 10);
	assert((*imas)[7] == imas->get(7) && imas->get(7) == 10);
	assert((*imas)[8] == imas->get(8) && imas->get(8) == 10);
	assert((*imas)[9] == imas->get(9) && imas->get(9) == 10);

	ArraySequence<int>* as = new MutableArraySequence<int>();
	try {
		as->pop_back();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	imas->clear();

	assert(!imas->empty());
}

void TestBorder—ases_BOAS() {
	ArraySequence<int>* as = new MutableArraySequence<int>();

	// Test empty list
	try {
		as->pop_back();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		as->pop_front();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		as->front();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		as->back();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		as->set(1, 1);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		as->get(5);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		as->get(0);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		(*as)[-1];
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		(*as)[0];
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		(*as)[50];
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	// Test filled list
	try {
		as->resize(50);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	as->resize(20, 0);

	try {
		for (int i = 0; i < 30; ++i) {
			as->pop_back();
		}
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	as->resize(20, 0);

	try {
		for (int i = 0; i < 30; ++i) {
			as->pop_front();
		}
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		as->resize(-10, 90);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		as->resize(-10);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	as->resize(20, 0);

	for (int i = 0; i < 30; ++i) {
		try {
			as->get(i);
		}
		catch (...) {
			if (i >= 20) assert(true);
			else assert(false);
		}
	}

	for (int i = 0; i < 30; ++i) {
		try {
			as->set(-(i + 1), i);
		}
		catch (...) {
			if (i >= 20) assert(true);
			else assert(false);
		}
	}
}

void TestMethods_AS() {
	MutableArraySequence<int>* mas_1 = new MutableArraySequence<int>(5, 100);
	MutableArraySequence<int>* mas_2 = new MutableArraySequence<int>(5, 200);
	mas_1->concat(*mas_2);
	assert(mas_1->get_size() == 10);
	for (int i = 0; i < 5; ++i) {
		assert(mas_1->get(i) == 100);
		assert(mas_1->get(i + 5) == 200);
	}
	assert(mas_2->get_size() == 5);
	for (int i = 0; i < 5; ++i) {
		assert(mas_2->get(i) == 200);
	}
	ImmutableArraySequence<int>* imas_1 = new ImmutableArraySequence<int>(5, 100);
	ImmutableArraySequence<int>* imas_2 = new ImmutableArraySequence<int>(5, 200);
	imas_1->concat(*imas_2);
	assert(imas_1->get_size() == 5);
	for (int i = 0; i < 5; ++i) {
		assert(imas_1->get(i) == 100);
	}
	assert(imas_2->get_size() == 5);
	for (int i = 0; i < 5; ++i) {
		assert(imas_2->get(i) == 200);
	}

	imas_1->map([](const auto& item) -> auto { return item * 2; });
	assert(imas_1->get_size() == 5);
	for (int i = 0; i < 5; ++i) {
		assert(imas_1->get(i) == 100);
	}

	mas_2->map([](const auto& item) -> auto { return item * 2; });
	assert(mas_2->get_size() == 5);
	for (int i = 0; i < 5; ++i) {
		assert(mas_2->get(i) == 400);
	}

	mas_1->resize(5, 5);
	assert(mas_1->get_size() == 5);
	for (int i = 0; i < 5; ++i) {
		assert(mas_1->get(i) == 100);
	}

	mas_2->resize(10, 15);
	assert(mas_2->get_size() == 10);
	for (int i = 0; i < 5; ++i) {
		assert(mas_2->get(i) == 400);
		assert(mas_2->get(i + 5) == 15);
	}

	assert(mas_2->find(15) == 5);
	assert(imas_2->count(200) == 5);

	ArraySequence<int>* seq = mas_2->where([](const int& item) -> bool { return item % 10 == 5; });
	assert(seq->get_size() == 5);
	for (int i = 0; i < 5; ++i) {
		assert(seq->get(i) == 15);
	}
}

void TestArraySequence() {
	TestConstructorsAndDestructors_AS();
	TestIterators_AS();
	TestBaseOperations_AS();
	TestBorder—ases_BOAS();
	TestMethods_AS();
}