#include "TestLinkedList.hpp"

void TestConstructorsAndDestructors_LL() {
	LinkedList<int>* ll_1 = new LinkedList<int>();
	LinkedList<double>* ll_2 = new LinkedList<double>();
	LinkedList<char>* ll_3 = new LinkedList<char>();
	LinkedList<int*>* ll_4 = new LinkedList<int*>();
	LinkedList<double**>* ll_5 = new LinkedList<double**>();

	assert(ll_1->empty());
	assert(ll_2->empty());
	assert(ll_3->empty());
	assert(ll_4->empty());
	assert(ll_5->empty());

	ll_1->~LinkedList();
	ll_2->~LinkedList();
	ll_3->~LinkedList();
	ll_4->~LinkedList();
	ll_5->~LinkedList();

	LinkedList<int>* ll_6 = new LinkedList<int>(10, 10);
	LinkedList<int>* ll_7 = new LinkedList<int>(10, 15);
	LinkedList<int>* ll_8 = new LinkedList<int>(*ll_6);
	DynamicArray<int>* da_0 = new DynamicArray<int>(10, 25);
	LinkedList<int>* ll_9 = new LinkedList<int>(*da_0);

	assert(ll_6->get_size() == 10);
	assert(ll_7->get_size() == 10);
	assert(ll_8->get_size() == 10);
	assert(ll_9->get_size() == 10);

	for (int i = 0; i < 10; ++i) {
		assert((*ll_6)[i] == (*ll_8)[i]);
	}

	for (int i = 0; i < 10; ++i) {
		assert((*da_0)[i] == (*ll_9)[i]);
	}

	ll_6->~LinkedList();
	ll_7->~LinkedList();
	ll_8->~LinkedList();
	ll_9->~LinkedList();
}

void TestIterators_LL() {
	LinkedList<int>* ll = new LinkedList<int>(10, 45);
	int i = 0;
	for (auto it = ll->begin(); it != ll->end(); ++it) {
		assert(*it == ll->get(i));
		i++;
	}
	i = 0;
	for (auto it = ll->begin(); it != ll->end(); ++it) {
		ll->insert(i, it);
		i++;
	}
	i = -1;
	for (auto it = ll->begin(); it != ll->end(); ++it) {
		i += 2;
		++it;
		assert(ll->get(i) == *it);
	}
	auto it = ll->begin();
	int size = static_cast<int> (ll->get_size());
	for (int i = 0; i < size; ++i) {
		ll->erase(it);
	}
	assert(ll->empty());
	ll->~LinkedList();
}

void TestBaseOperations_LL() {
	LinkedList<double>* ll = new LinkedList<double>();
	assert(ll->empty());

	ll->push_back(100);
	ll->push_back(1000);
	ll->push_front(10);
	ll->push_front(1);
	ll->push_back(10000);

	assert(ll->get_size() == 5);
	assert(ll->get(0) == 1);
	assert(ll->get(1) == 10);
	assert(ll->get(2) == 100);
	assert(ll->get(3) == 1000);
	assert(ll->get(4) == 10000);

	assert(ll->front() == 1);
	assert(ll->back() == 10000);

	ll->pop_front();
	ll->pop_back();
	assert(ll->get_size() == 3);
	assert(ll->front() == 10);
	assert(ll->back() == 1000);

	ll->set(1, 0);
	ll->set(2, 1);
	ll->set(3, 2);
	assert((*ll)[0] == 1);
	assert((*ll)[1] == 2);
	assert((*ll)[2] == 3);
}

void TestBorder—ases_BOLL() {
	LinkedList<int>* ll = new LinkedList<int>();

	// Test empty list
	try {
		ll->pop_back();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ll->pop_front();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ll->front();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ll->back();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ll->set(1, 1);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ll->get(5);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ll->get(0);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		(*ll)[-1];
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		(*ll)[0];
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		(*ll)[50];
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	// Test filled list
	try {
		ll->resize(50);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	ll->resize(20, 0);

	try {
		for (int i = 0; i < 30; ++i) {
			ll->pop_back();
		}
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	ll->resize(20, 0);

	try {
		for (int i = 0; i < 30; ++i) {
			ll->pop_front();
		}
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ll->resize(-10, 90);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		ll->resize(-10);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	ll->resize(20, 0);

	for (int i = 0; i < 30; ++i) {
		try {
			ll->get(i);
		}
		catch (...) {
			if (i >= 20) assert(true);
			else assert(false);
		}
	}

	for (int i = 0; i < 30; ++i) {
		try {
			ll->set(-(i + 1), i);
		}
		catch (...) {
			if (i >= 20) assert(true);
			else assert(false);
		}
	}
}

void TestMethods_LL() {
	LinkedList<float>* ll_1 = new LinkedList<float>(10, 15);
	LinkedList<int>* ll_2 = new LinkedList<int>(50, 0);
	ll_1->resize(5);
	ll_2->resize(10, 10);
	assert(ll_1->get_size() == 5);
	assert(ll_2->get_size() == 10);
	ll_1->resize(10, 144);
	assert(ll_1->get_size() == 10);
}

void TestLinkedList() {
	TestConstructorsAndDestructors_LL();
	TestBaseOperations_LL();
	TestBorder—ases_BOLL();
	TestIterators_LL();
	TestMethods_LL();
}