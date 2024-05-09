#include "TestArraySequence.hpp"
#include "TestDynamicArray.hpp"
#include "TestLinkedList.hpp"
#include "TestListSequence.hpp"
#include "view.hpp"

int main() {
	// ADD CAST FROM ADAPTERS TO ADAPTERS
	TestLinkedList();
	TestDynamicArray();
	TestListSequence();
	TestArraySequence();
	run();
	return 0;
}