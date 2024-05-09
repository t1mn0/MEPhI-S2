#include <iostream>
#include "TestQueue.hpp"
#include "TestStack.hpp"
#include "TestDeque.hpp"
#include "TestDataTypes.hpp"
#include "view.hpp"

int main() {
	TestStack();
	TestQueue();
	TestDeque();
	TestDataTypes();
	run();
}