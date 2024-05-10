#include <iostream>
#include "TestQueue.hpp"
#include "TestStack.hpp"
#include "TestDeque.hpp"
#include "TestDataTypes.hpp"
#include "TestCompatibility.hpp"
#include "view.hpp"

int main() {
	TestStack();
	TestQueue();
	TestDeque();
	TestDataTypes();
	//TestCompatibility();
	//run();
}