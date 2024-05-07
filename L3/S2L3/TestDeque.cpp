#include <cassert>
#include "Deque.hpp"
#include <iostream>

void TestDeque() {
	ListSequence<int>* listseq = new MutableListSequence<int>(5, 0);
	Deque<int>* deq_1 = new Deque<int>();
	Deque<int>* deq_2 = new Deque<int>(*listseq);

	try {
		deq_1->pop_back();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	try {
		deq_1->pop_front();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	try {
		deq_1->front();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	try {
		deq_1->back();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	assert(deq_1->size() == 0);
	assert(deq_2->size() == 5);
	assert(deq_2->front() == 0);

	for (int i = 3; i < 6; ++i) {
		deq_1->push_back(i);
	}

	for (int i = 2; i > 0; --i) {
		deq_1->push_front(i);
	}
	
	deq_1->concat(*deq_2);
	assert(deq_1->size() == 10);

	deq_2->clear();

	assert(deq_1->size() == 10);
	assert(deq_2->size() == 0);

	try {
		deq_2->pop_back();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	try {
		deq_2->pop_front();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	try {
		deq_2->front();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}


	for (int i = 0; i < 5; ++i) {
		assert(deq_1->pop_front() == i + 1);
	}
	for (int i = 0; i < 5; ++i) {
		assert(deq_1->pop_back() == 0);
	}

	assert(deq_1->empty());

	try {
		deq_1->pop_back();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	for (int i = 0; i < 10; ++i) {
		deq_1->push_back(i + 1);
	}

	deq_2->push_back(2);
	deq_2->push_back(4);

	assert(!deq_1->contains_subdeque(*deq_2));

	deq_2->pop_back();
	deq_2->push_front(1);
	deq_2->push_back(3);

	
	assert(deq_1->contains_subdeque(*deq_2));
	Deque<int> odd_deq = deq_1->where([](const int& number) -> bool {
		return number % 2 != 0;
		});

	for (int i = 0; i < 5; ++i) {
		assert(odd_deq.pop_back() % 2);
	}

	Deque<int> deq_3 = deq_1->get_subdeque(0, 4);

	deq_3.map([](const int& number) -> int {
		return number * 100;
		});
	for (int i = 0; i < 5; ++i) {
		assert(deq_3.pop_front() % 100 == 0);
	}

	for (int i = 1; i < 16; ++i) {
		deq_3.push_front(-i);
	}

	int sum = deq_3.reduce(120, [](const int& a, const int& b) -> int {
		return a + b;
		});

	assert(sum == 0);
}