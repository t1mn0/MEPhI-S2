#include <cassert>
#include "Stack.hpp"
#include <iostream>
#include <string>


int reduceFunc(const int& a, const int& b) {
	return a + b;
}

void TestStack() {
	ArraySequence<int>* arseq = new MutableArraySequence<int>(5, 0);
	Stack<int>* stack_1 = new Stack<int>();
	Stack<int>* stack_2 = new Stack<int>(*arseq);

	try {
		stack_1->pop();
		assert(false);
	}
	catch (Exception &e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	try {
		stack_1->top();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	assert(stack_1->size() == 0);
	assert(stack_2->size() == 5);
	assert(stack_2->top() == 0);

	for (int i = 1; i < 6; ++i) {
		stack_1->push(i);
	}

	stack_1->concat(*stack_2);
	assert(stack_1->size() == 10);

	stack_2->clear();

	assert(stack_1->size() == 10);
	assert(stack_2->size() == 0);

	try {
		stack_2->pop();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	try {
		stack_2->top();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	for (int i = 0; i < 5; ++i) {
		assert(stack_1->pop() == 0);
	}

	for (int i = 0; i < 5; ++i) {
		assert(stack_1->pop() == 5 - i);
	}

	assert(stack_1->empty());

	try {
		stack_1->pop();
		assert(false);
	}
	catch (Exception& e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}

	try {
		stack_1->top();
		assert(false);
	}
	catch (Exception &e) {
		assert(e.getErrorMessage().compare("\033[0mout_of_range\033[1;31m"));
	}


	for (int i = 0; i < 10; ++i) {
		stack_1->push(i + 1);
	}

	stack_2->push(2);
	stack_2->push(4);

	assert(!stack_1->contains_substack(*stack_2));

	stack_2->pop();
	stack_2->push(3);
	stack_2->push(4);
	stack_2->push(5);
	
	assert(stack_1->contains_substack(*stack_2));

	Stack<int> odd_stack = stack_1->where([](const int& number) -> bool {
		return number % 2 != 0;
		});

	for (int i = 0; i < 5; ++i) {
		assert(odd_stack.pop() % 2);
	}

	Stack<int> stack_3 = stack_1->get_substack(0, 4);

	stack_3.map([](const int& number) -> int {
		return number * 100;
		});
	for (int i = 0; i < 5; ++i) {
		assert(stack_3.pop() % 100 == 0);
	}

	for (int i = 1; i < 16; ++i) {
		stack_3.push(-i);
	}

	int sum = stack_3.reduce(120, reduceFunc);

	assert(sum == 0);
}