#include "TestDynamicArray.hpp"

void TestConstructorsAndDestructors_DA() {
	DynamicArray<int>* da_1 = new DynamicArray<int>();
	DynamicArray<double>* da_2 = new DynamicArray<double>();
	DynamicArray<char>* da_3 = new DynamicArray<char>();
	DynamicArray<int*>* da_4 = new DynamicArray<int*>();
	DynamicArray<double**>* da_5 = new DynamicArray<double**>();
	assert(da_1->empty());
	assert(da_2->empty());
	assert(da_3->empty());
	assert(da_4->empty());
	assert(da_5->empty());
	da_1->~DynamicArray();
	da_2->~DynamicArray();
	da_3->~DynamicArray();
	da_4->~DynamicArray();
	da_5->~DynamicArray();
	DynamicArray<int>* da_6 = new DynamicArray<int>(10, 10);
	DynamicArray<int>* da_7 = new DynamicArray<int>(10, 0);
	LinkedList<int>* ll_0 = new LinkedList<int>(10, 25);
	DynamicArray<int>* da_8 = new DynamicArray<int>(*ll_0);
	for (int i = 0; i <= 9; ++i) {
		da_7->set(i, i);
	}
	for (int i = 0; i < 10; ++i) {
		assert((*da_8)[i] == (*ll_0)[i]);
	}
	assert(da_6->get_size() == 10);
	assert(da_7->get_size() == 10);
	assert(da_8->get_size() == 10);
	da_6->~DynamicArray();
	da_7->~DynamicArray();
	da_8->~DynamicArray();

	try {
		DynamicArray<int>* da_8 = new DynamicArray<int>(-10, 0);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void TestIterators_DA() {
	DynamicArray<int>* da = new DynamicArray<int>(10, 0);
	for (int i = 0; i <= 9; ++i) {
		da->set(i, i);
	}
	int i = 0;
	for (auto it = da->begin(); it != da->end(); ++it) {
		assert(*it == da->get(i));
		i++;
	}
	auto it = da->begin();
	int f = 255;
	da->insert(f, it);
	++it;
	++it;
	++it;
	da->insert(f, it);
	++it;
	++it;
	++it;
	da->insert(f, it);
	++it;
	++it;
	++it;
	da->insert(f, it);
	++it;
	++it;
	++it;
	da->insert(f, it);
	++it;
	++it;
	++it;
	da->insert(f, it);

	for (int i = 0; i < static_cast<int> (da->get_size()); i += 3) {
		assert(da->get(i) == 255);
	}

	auto iter = da->begin();
	int size = static_cast<int> (da->get_size());


	for (int i = 0; i < size; i++) {
		da->erase(iter);
	}

	assert(da->empty());
	da->~DynamicArray();
}

void TestBaseOperations_DA() {
	DynamicArray<double>* da = new DynamicArray<double>();
	assert(da->empty());
	try {
		da->front();
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	try {
		da->back();
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	da->push_back(100);
	da->push_back(1000);
	da->push_front(10);
	da->push_front(1);
	da->push_back(10000);
	assert(da->get_size() == 5);
	assert(da->get(0) == 1);
	assert(da->get(1) == 10);
	assert(da->get(2) == 100);
	assert(da->get(3) == 1000);
	assert(da->get(4) == 10000);
	try {
		da->get(5);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	try {
		da->get(10);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	try {
		da->get(-5);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	assert(da->front() == 1);
	assert(da->back() == 10000);
	da->pop_front();
	da->pop_back();
	assert(da->get_size() == 3);
	assert(da->front() == 10);
	assert(da->back() == 1000);
	double f = 1;
	da->set(f, 0);
	f = 2;
	da->set(f, 1);
	f = 3;
	da->set(f, 2);
	assert((*da)[0] == 1);
	assert((*da)[1] == 2);
	assert((*da)[2] == 3);
}

void TestBorder—ases_BODA() {
	DynamicArray<int>* da = new DynamicArray<int>();

	// Test empty list
	try {
		da->pop_back();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		da->pop_front();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		da->front();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		da->back();
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		da->set(1, 1);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		da->get(5);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		da->get(0);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		(*da)[-1];
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		(*da)[0];
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		(*da)[50];
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	// Test filled list
	try {
		da->resize(50);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	da->resize(20, 0);

	try {
		for (int i = 0; i < 30; ++i) {
			da->pop_back();
		}
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	da->resize(20, 0);

	try {
		for (int i = 0; i < 30; ++i) {
			da->pop_front();
		}
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		da->resize(-10, 90);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	try {
		da->resize(-10);
		assert(false);
	}
	catch (...) {
		assert(true);
	}

	da->resize(20, 0);

	for (int i = 0; i < 30; ++i) {
		try {
			da->get(i);
		}
		catch (...) {
			if (i >= 20) assert(true);
			else assert(false);
		}
	}

	for (int i = 0; i < 30; ++i) {
		try {
			da->set(-(i + 1), i);
		}
		catch (...) {
			if (i >= 20) assert(true);
			else assert(false);
		}
	}
}

void TestMethods_DA() {
	DynamicArray<float>* da_1 = new DynamicArray<float>(10, 15);
	DynamicArray<int>* da_2 = new DynamicArray<int>(50, 0);
	da_1->resize(5);
	da_2->resize(10, 10);

	assert(da_1->get_size() == 5);
	assert(da_2->get_size() == 10);
	da_1->resize(10, 144);
	assert(da_1->get_size() == 10);
}

void TestDynamicArray() {
	TestConstructorsAndDestructors_DA();
	TestBaseOperations_DA();
	TestBorder—ases_BODA();
	TestIterators_DA();
	TestMethods_DA();
}