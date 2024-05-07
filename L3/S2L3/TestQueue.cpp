#include <cassert>
#include "Queue.hpp"
#include <iostream>

void TestQueue() {
	ListSequence<int>* listseq = new MutableListSequence<int>(5, 0);
	Queue<int>* queue_1 = new Queue<int>();
	Queue<int>* queue_2 = new Queue<int>(*listseq);

	try {
		queue_1->dequeue();
		assert(false);
	}
	catch (Exception &e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	try {
		queue_1->front();
		assert(false);
	}
	catch (Exception &e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	assert(queue_1->size() == 0);
	assert(queue_2->size() == 5);
	assert(queue_2->front() == 0);

	for (int i = 1; i < 6; ++i) {
		queue_1->enqueue(i);
	}

	queue_1->concat(*queue_2);
	assert(queue_1->size() == 10);

	queue_2->clear();

	assert(queue_1->size() == 10);
	assert(queue_2->size() == 0);

	try {
		queue_2->dequeue();
		assert(false);
	}
	catch (Exception &e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	try {
		queue_2->front();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	for (int i = 0; i < 5; ++i) {
		assert(queue_1->dequeue() == i + 1);
	}
	for (int i = 0; i < 5; ++i) {
		assert(queue_1->dequeue() == 0);
	}

	assert(queue_1->empty());

	try {
		queue_1->dequeue();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	try {
		queue_1->front();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}


	for (int i = 0; i < 10; ++i) {
		queue_1->enqueue(i + 1);
	}

	queue_2->enqueue(2);
	queue_2->enqueue(4);
	
	assert(!queue_1->contains_subqueue(*queue_2));

	queue_2->dequeue();
	queue_2->dequeue();
	queue_2->enqueue(3);
	queue_2->enqueue(4);
	queue_2->enqueue(5);

	assert(queue_1->contains_subqueue(*queue_2));

	Queue<int> odd_queue = queue_1->where([](const int& number) -> bool {
		return number % 2 != 0;
		});

	for (int i = 0; i < 5; ++i) {
		assert(odd_queue.dequeue() % 2);
	}

	Queue<int> queue_3 = queue_1->get_subqueue(0, 4);

	queue_3.map([](const int& number) -> int {
		return number * 100;
		});
	for (int i = 0; i < 5; ++i) {
		assert(queue_3.dequeue() % 100 == 0);
	}

	for (int i = 1; i < 16; ++i) {
		queue_3.enqueue(-i);
	}

	int sum = queue_3.reduce(120, [](const int& a, const int& b) -> int {
		return a + b;
		});

	assert(sum == 0);
}