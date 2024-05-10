#include "Stack.hpp"
#include "Deque.hpp"
#include "Queue.hpp"
#include "Student.hpp"
#include "Teacher.hpp"

#define RESET	"\033[0m"
#define RED		"\033[1;31m"
#define YELLOW	"\033[1;33m"
#define GREEN	"\033[1;32m"
#define BLUE	"\033[1;34m"
#define LINE "============================================================================================================================================================\n"
#define LANE "------------------------------------------------------------------------------------------------------------------------------------------------------------\n"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "../../../../L2/S2L2/MutableListSequence.hpp"

// -----------------------------------------------------------------------------------------------------------------
// Lists

std::vector<Stack<int>> stackList;

std::vector<Queue<int>> queueList;

std::vector<Deque<int>> dequeList;

// -----------------------------------------------------------------------------------------------------------------
// Declaration

void menu();
void run();
int create_adapter();
int check_state();
int printAdapter();
int get();
int push();
int pop();

// -----------------------------------------------------------------------------------------------------------------
// Base

void menu() {
	std::cout << LINE;
	std::cout << std::setw(80) << "MENU\n";
	std::cout << LINE;
	std::cout << std::setw(75) << GREEN << "Available Commands:\n" << RESET;
	std::cout << GREEN << "> 0) exit \n" << RESET;														// YES			
	std::cout << GREEN << "> 1) menu\n" << RESET;														// YES
	std::cout << GREEN << "> 2) create adapter\n" << RESET;												// YES
	std::cout << GREEN << "> 3) check state\n" << RESET;												// YES
	std::cout << GREEN << "> 4) print adapter\n" << RESET;												// YES
	std::cout << GREEN << "> 5) get\n" << RESET;														// YES
	std::cout << GREEN << "> 6) push\n" << RESET;														// 
	std::cout << GREEN << "> 7) pop\n" << RESET;														// YES
	std::cout << LINE;
	std::cout << RED << "Warning" << RESET << ": the program will finished automatically after 10 consecutive unsuccessful input attempts\n";
	std::cout << LINE;
}

void run() {
	menu();
	int bad_count = 10;
	int state = 1;
	std::string command;
	while (bad_count) {
		state = 1;
		std::cout << ">>> ";
		std::cin >> command;
		if (command == "0") {
			std::cout << YELLOW << "Are you sure? (y / n)\n" << RESET;
			std::cout << ">>> ";
			std::cin >> command;
			if (command == "yes" || command == "y" || command == "YES") {
				exit(0);
			}
		}
		else if (command == "1") { // menu
			system("cls");
			menu();
			bad_count = 10;
		}
		else if (command == "2") { // create adapter
			system("cls");
			state = create_adapter();
			if (state) {
				system("cls");
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			else {
				std::cout << ">>> ";
				std::cin >> command;
				system("cls");
			}
			menu();
			bad_count = 10;
		}
		else if (command == "3") { // check state
			system("cls");
			check_state();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			menu();
		}
		else if (command == "4") { // print adapter
			system("cls");
			state = printAdapter();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "5") { // get 
			system("cls");
			state = get();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "6") { // push 
			system("cls");
			state = push();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "7") { // pop 
			system("cls");
			state = pop();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else {
			std::cout << command << '\n';
			bad_count--;
		}
	}
}

// -----------------------------------------------------------------------------------------------------------------
// Support functions

void promptAbort() {
	std::cout << LANE;
	std::cout << "Enter '" << RED << "abort" << RESET << "' to finish the operation prematurely (the operation will not be executed)\n";
	std::cout << LANE;
}

// -----------------------------------------------------------------------------------------------------------------
// Support functions for create adapter

bool isValidSizeAdapter(const std::string& s_size) {
	size_t pos;
	try {
		int size = std::stoi(s_size, &pos);

		if (pos != s_size.length()) {
			return false;
		}
		if (size < 0 || size > 1000) {
			return false;
		}
	}
	catch (...) {
		return false;
	}

	return true;
}

bool isValidIndex(const std::string& s_index, size_t size) {
	size_t pos;
	try {
		int index = std::stoi(s_index, &pos);

		if (pos != s_index.length()) {
			return false;
		}
		if (index < 0 || index >= size) {
			return false;
		}
	}
	catch (...) {
		return false;
	}

	return true;
}

bool isValidInt(std::string s_defaultElement) {
	size_t pos;
	try {
		int defaultElement = std::stoi(s_defaultElement, &pos);

		if (pos != s_defaultElement.length()) {
			return false;
		}
	}
	catch (...) {
		return false;
	}

	return true;
}

std::string getTypeAdapter() {
	std::cout << GREEN << "\n> 1) stack\n" << RESET;
	std::cout << GREEN << "> 2) queue\n" << RESET;
	std::cout << GREEN << "> 3) deque\n" << RESET;
	std::cout << "\nInput the " << GREEN << "type" << RESET << " of adapter:\n";

	std::string type_adapter;
	int bad_count = 10;

	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> type_adapter;

		if (type_adapter == "1" || type_adapter == "stack" || type_adapter == "Stack") {
			type_adapter = "1";
			break;
		}
		else if (type_adapter == "2" || type_adapter == "queue" || type_adapter == "Queue") {
			type_adapter = "2";
			break;
		}
		else if (type_adapter == "3" || type_adapter == "deque" || type_adapter == "Deque") {
			type_adapter = "3";
			break;
		}
		else if (type_adapter == "abort") {
			break;
		}
		else {
			std::cout << RED << "TypeAdapter = '" << type_adapter << "' is not valid type of adapter\n" << RESET;
			bad_count--;
		}
	}

	std::cout << '\n';

	if (bad_count == 0) {
		return "ERR-0001-ATTEXP"; // attempts expired
	}
	else if (type_adapter == "abort") {
		return "ERR-1111-FUNCINTERR"; // function interrupted
	}
	return type_adapter;
}

int getSizeAdapter() {
	std::string s_sizeadapter;
	int sizeadapter = -1;
	int bad_count = 10;

	std::cout << "Input the " << GREEN << "size" << RESET << " of adapter (0 <= size <= 1000)\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_sizeadapter;
		if (isValidSizeAdapter(s_sizeadapter)) {
			size_t pos;
			sizeadapter = std::stoi(s_sizeadapter, &pos);
			break;
		}
		else if (s_sizeadapter == "abort") {
			break;
		}
		else {
			std::cout << RED << "SizeAdapter = '" << s_sizeadapter << "' is not valid size for adapter\n" << RESET;
			bad_count--;
		}
	}

	if (s_sizeadapter == "abort") {
		return -1;
	}
	else if (bad_count == 0) {
		return -1;
	}

	return sizeadapter;
}

// -----------------------------------------------------------------------------------------------------------------
// Create adapter

int fillStack(Stack<int>& stack, int size) {

	int bad_count = 10;
	std::string element;
	std::string forERR = "NONE";

	int i = 0;
	while (bad_count && i < size) {
		std::cout << "Input the " << GREEN << "new element" << RESET << " for pushing in stack (added " << i << "/" << size << ")\n";
		std::cout << ">>> ";
		std::cin >> element;

		if (isValidInt(element)) {
			size_t pos;
			int el = std::stoi(element, &pos);
			try {
				stack.push(el);
			}
			catch (const Exception& e) {
				forERR = e.getErrorMessage();
				break;
			}
			i++;
		}
		else if (element == "abort") {
			forERR = "ERR-1111-FUNCINTERR";
			break;
		}
		else {
			std::cout << RED << "Element = '" << element << "' is not valid element for stack\n" << RESET;
			bad_count--;
		}
	}

	if (forERR.substr(0, 3) == "ERR") {
		return -1;
	}
	else if (forERR != "NONE") {
		std::cout << forERR << '\n';
		return -1;
	}

	return 0;
}

int fillQueue(Queue<int>& queue, int size) {

	int bad_count = 10;
	std::string element;
	std::string forERR = "NONE";

	int i = 0;
	while (bad_count && i < size) {
		std::cout << "Input the " << GREEN << "new element" << RESET << " for pushing in queue (added " << i << "/" << size << ")\n";
		std::cout << ">>> ";
		std::cin >> element;

		if (isValidInt(element)) {
			size_t pos;
			int el = std::stoi(element, &pos);
			try {
				queue.push(el);
			}
			catch (const Exception& e) {
				forERR = e.getErrorMessage();
				break;
			}
			i++;
		}
		else if (element == "abort") {
			forERR = "ERR-1111-FUNCINTERR";
			break;
		}
		else {
			std::cout << RED << "Element = '" << element << "' is not valid element for queue\n" << RESET;
			bad_count--;
		}
	}

	if (forERR.substr(0, 3) == "ERR") {
		return -1;
	}
	else if (forERR != "NONE") {
		std::cout << forERR << '\n';
		return -1;
	}

	return 0;
}

int fillDeque(Deque<int>& deque, int size) {

	int bad_count = 10;
	std::string element;
	std::string typepush;
	std::string forERR = "NONE";

	int i = 0;
	while (bad_count && i < size) {
		std::cout << "Input the " << GREEN << "type of push" << RESET << " (1 = push_front / 2 = push_back)\n";
		std::cout << ">>> ";
		std::cin >> typepush;
		if (typepush == "1" || typepush == "2") {
			std::cout << "Input the " << GREEN << "new element" << RESET << " for pushing in deque (added " << i << "/" << size << ")\n";
			std::cout << ">>> ";
			std::cin >> element;

			if (isValidInt(element)) {
				size_t pos;
				int el = std::stoi(element, &pos);
				try {
					if (typepush == "1") {
						deque.push_front(el);
					}
					else if (typepush == "2") {
						deque.push_back(el);
					}
				}
				catch (const Exception& e) {
					forERR = e.getErrorMessage();
					break;
				}
				i++;
			}
			else if (element == "abort") {
				forERR = "ERR-1111-FUNCINTERR";
				break;
			}
			else {
				std::cout << RED << "Element = '" << element << "' is not valid element for queue\n" << RESET;
				bad_count--;
			}
		}
		else if (typepush == "abort") {
			return -1;
		}
		else {
			std::cout << RED << "TypePush = '" << typepush << "' is not type of pushing element\n" << RESET;
			bad_count--;
		}
	}

	if (forERR.substr(0, 3) == "ERR") {
		return -1;
	}
	else if (forERR != "NONE") {
		std::cout << forERR << '\n';
		return -1;
	}

	return 0;
}

int create_adapter() {
	promptAbort();

	std::string type_adapter = getTypeAdapter();
	if (type_adapter.substr(0, 3) == "ERR") {
		return -1;
	}

	int sizeadapter = getSizeAdapter();
	if (sizeadapter < 0) {
		return -1;
	}

	if (type_adapter == "1") {
		stackList.push_back(Stack<int>());
		fillStack(stackList[stackList.size() - 1], sizeadapter);
	}
	else if (type_adapter == "2") {
		queueList.push_back(Queue<int>());
		fillQueue(queueList[queueList.size() - 1], sizeadapter);
	}
	else if (type_adapter == "3") {
		dequeList.push_back(Deque<int>());
		fillDeque(dequeList[dequeList.size() - 1], sizeadapter);
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------------------
// Print state 

void infoAdapter(int typeadapter, int index) {
	if (typeadapter == 1) {
		if (index >= 0 && index < stackList.size()) {
			std::cout << LINE;
			std::cout << std::setw(83) << "Adapter - " << BLUE << "Stack " << RESET << "[" << index << "]" << '\n';
			std::cout << LINE;

			std::cout << "Type of adapter: " << BLUE << "stack" << '\n' << RESET;
			std::cout << "The size of adapter: " << BLUE << stackList[index].size() << '\n' << RESET;
			std::cout << LANE << '\n';
		}
		else {
			std::cout << RED << "Index is out of range\n" << RESET;
		}
	}
	else if (typeadapter == 2) {
		if (index >= 0 && index < queueList.size()) {
			std::cout << LINE;
			std::cout << std::setw(83) << "Adapter - " << BLUE << "Queue " << RESET << "[" << index << "]" << '\n';
			std::cout << LINE;

			std::cout << "Type of adapter: " << BLUE << "queue" << '\n' << RESET;
			std::cout << "The size of adapter: " << BLUE << queueList[index].size() << '\n' << RESET;
			std::cout << LANE << '\n';
		}
		else {
			std::cout << RED << "Index is out of range\n" << RESET;
		}
	}
	else if (typeadapter == 3) {
		if (index >= 0 && index < dequeList.size()) {
			std::cout << LINE;
			std::cout << std::setw(83) << "Adapter - " << BLUE << "Deque " << RESET << "[" << index << "]" << '\n';
			std::cout << LINE;

			std::cout << "Type of adapter: " << BLUE << "deque" << '\n' << RESET;
			std::cout << "The size of adapter: " << BLUE << dequeList[index].size() << '\n' << RESET;
			std::cout << LANE << '\n';
		}
		else {
			std::cout << RED << "Index is out of range\n" << RESET;
		}
	}
}

int check_state() {
	if (stackList.size() == 0) {
		std::cout << "\n" << LINE;
		std::cout << RED << "There are no one stack\n" << RESET;
		std::cout << LINE;
	}
	else {
		for (int i = 0; i < stackList.size(); ++i) {
			infoAdapter(1, i);
		}
	}

	if (queueList.size() == 0) {
		std::cout << "\n" << LINE;
		std::cout << RED << "There are no one queue\n" << RESET;
		std::cout << LINE;
	}
	else {
		for (int i = 0; i < queueList.size(); ++i) {
			infoAdapter(2, i);
		}
	}

	if (dequeList.size() == 0) {
		std::cout << "\n" << LINE;
		std::cout << RED << "There are no one deque\n" << RESET;
		std::cout << LINE;
	}
	else {
		for (int i = 0; i < dequeList.size(); ++i) {
			infoAdapter(3, i);
		}
	}

	return 0;
}

int select() {
	promptAbort();
	check_state();

	std::string type_adapter = getTypeAdapter();
	if (type_adapter.substr(0, 3) == "ERR") {
		return -1;
	}

	int bad_count = 10;
	std::string s_index;

	std::cout << "Input the " << GREEN << "index" << RESET << " of adapter\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_index;
		if (s_index == "abort") {
			return -1;
		}
		if (type_adapter == "1") {
			if (isValidIndex(s_index, stackList.size())) {
				int index = stoi(s_index);
				return index;
			}
			else {
				std::cout << RED << "Invalid index for stack-list: " << s_index << " is not found\n" << RESET;
				bad_count--;
			}
		}
		else if (type_adapter == "2") {
			if (isValidIndex(s_index, queueList.size())) {
				int index = stoi(s_index);
				return index + stackList.size();
			}
			else {
				std::cout << RED << "Invalid index for queue-list: " << s_index << " is not found\n" << RESET;
				bad_count--;
			}
		}
		else if (type_adapter == "3") {
			if (isValidIndex(s_index, dequeList.size())) {
				int index = stoi(s_index);
				return index + stackList.size() + queueList.size();
			}
			else {
				std::cout << RED << "Invalid index for deque-list: " << s_index << " is not found\n" << RESET;
				bad_count--;
			}
		}
	}

	if (!bad_count) {
		return -1;
	}
}

int printAdapter() {
	int index = select();

	if (index < 0) {
		return -1;
	}

	if (index < stackList.size()) {
		std::cout << BLUE << "Stack content:\n" << RESET;
		Stack<int> copystack = *(new Stack<int>(stackList[index]));
		MutableListSequence<int> list;
		for (int i = 0; i < stackList[index].size(); ++i) {
			list.push_back(copystack.pop());
		}
		for (int i = list.get_size() - 1; i >= 0; --i) {
			std::cout << list[i] << " ";
		}
		std::cout << "\n";
	}
	else if (index < stackList.size() + queueList.size()) {
		index -= stackList.size();
		std::cout << BLUE << "Queue content:\n" << RESET;
		Queue<int> copyqueue = *(new Queue<int>(queueList[index]));
		MutableListSequence<int> list;
		for (int i = 0; i < queueList[index].size(); ++i) {
			list.push_back(copyqueue.pop());
		}
		for (size_t i = 0; i < list.get_size(); ++i) {
			std::cout << list[i] << " ";
		}
		std::cout << "\n";
	}
	else if (index < stackList.size() + queueList.size() + dequeList.size()) {
		index -= stackList.size();
		index -= queueList.size();
		std::cout << BLUE << "Deque content:\n" << RESET;
		Deque<int> copydeque = *(new Deque<int>(dequeList[index]));
		MutableListSequence<int> list;
		for (int i = 0; i < dequeList[index].size(); ++i) {
			list.push_back(copydeque.pop_front());
		}
		for (size_t i = 0; i < list.get_size(); ++i) {
			std::cout << list[i] << " ";
		}
		std::cout << "\n";
	}
	

	return 0;
}

// -----------------------------------------------------------------------------------------------------------------
// Get / push / pop

int get() {
	int index = select();

	if (index < 0) {
		return -1;
	}

	if (index < stackList.size()) {
		std::cout << "The top of stack: " << BLUE << stackList[index].top() << RESET << '\n';
	}
	else if (index < stackList.size() + queueList.size()) {
		index -= stackList.size();
		std::cout << "The front of queue: " << BLUE << queueList[index].front() << RESET << '\n';
	}
	else if (index < stackList.size() + queueList.size() + dequeList.size()) {
		index -= stackList.size();
		index -= queueList.size();
		int bad_count = 10;
		std::string type_get;
		std::cout << "Input the " << GREEN << "type" << RESET << " of get (front = 1 / back = 2):\n";
		while (bad_count) {
			std::cout << ">>> ";
			std::cin >> type_get;

			if (type_get == "1") {
				std::cout << "The front of deque: " << BLUE << dequeList[index].front() << RESET << '\n';
				break;
			}
			else if (type_get == "2") {
				std::cout << "The back of deque: " << BLUE << dequeList[index].back() << RESET << '\n';
				break;
			}
			else if (type_get == "abort") {
				break;
			}
			else {
				std::cout << RED << "TypeGet = '" << type_get << " is not valid type for get element\n" << RESET;
				bad_count--;
			}
		}

		std::cout << '\n';

		if (bad_count == 0) {
			return -1; 
		}
		else if (type_get == "abort") {
			return -1;
		}
	}


	return 0;
}

int push()	 {
	int index = select();

	if (index < 0) {
		return -1;
	}

	std::string s_value;
	int value;
	int bad_count = 10;


	if (index < stackList.size()) {
		std::cout << "Input the " << GREEN << "value for push" << RESET << " in stack\n";
		while (bad_count) {
			std::cout << ">>> ";
			std::cin >> s_value;
			if (isValidInt(s_value)) {
				int value = stoi(s_value);
				stackList[index].push(value);
				break;
			}
			else if (s_value == "abort") {
				break;
			}
			else {
				std::cout << RED << "Value = '" << s_value << "' is not valid value\n" << RESET;
				bad_count--;
			}
		}
		if (s_value == "abort") {
			return -1;
		}
		else if (bad_count == 0) {
			return -1;
		}
	}
	else if (index < stackList.size() + queueList.size()) {
		index -= stackList.size();
		std::cout << "Input the " << GREEN << "value for push" << RESET << " in queue\n";
		while (bad_count) {
			std::cout << ">>> ";
			std::cin >> s_value;
			if (isValidInt(s_value)) {
				int value = stoi(s_value);
				queueList[index].push(value);
				break;
			}
			else if (s_value == "abort") {
				break;
			}
			else {
				std::cout << RED << "Value = '" << s_value << "' is not valid value\n" << RESET;
				bad_count--;
			}
		}
		if (s_value == "abort") {
			return -1;
		}
		else if (bad_count == 0) {
			return -1;
		}
	}
	else if (index < stackList.size() + queueList.size() + dequeList.size()) {
		index -= stackList.size();
		index -= queueList.size();

		std::string type_push;

		std::cout << "Input the " << GREEN << "type" << RESET << " of push (push_front = 1 / push_back = 2):\n";
		while (bad_count) {
			std::cout << ">>> ";
			std::cin >> type_push;

			if (type_push == "1" || type_push == "2") {
				break;
			}
			else if (type_push == "abort") {
				break;
			}
			else {
				std::cout << RED << "TypePush = '" << type_push << "' is not valid type for push element\n" << RESET;
				bad_count--;
			}
		}

		if (!bad_count) {
			return -1;
		}

		if (type_push == "abort") {
			return -1;
		}

		std::cout << "Input the " << GREEN << "value for push" << RESET << " in deque\n";
		while (bad_count) {
			std::cout << ">>> ";
			std::cin >> s_value;
			if (isValidInt(s_value)) {
				int value = stoi(s_value);
				if (type_push == "1") dequeList[index].push_front(value);
				if (type_push == "2") dequeList[index].push_back(value);
				break;
			}
			else if (s_value == "abort") {
				break;
			}
			else {
				std::cout << RED << "Value = '" << s_value << "' is not valid value\n" << RESET;
				bad_count--;
			}
		}
		if (s_value == "abort") {
			return -1;
		}
		else if (bad_count == 0) {
			return -1;
		}
	}

	return 0;
}

int pop() {
	int index = select();

	if (index < 0) {
		return -1;
	}

	if (index < stackList.size()) {
		if (!stackList[index].empty()) {
			std::cout << "The deleted top of stack: " << BLUE << stackList[index].pop() << RESET << '\n';
		}
		else {
			std::cout << RED << "Empty adapter" << RESET << '\n';
			return -1;
		}
	}
	else if (index < stackList.size() + queueList.size()) {
		index -= stackList.size();
		if (!queueList[index].empty()) {
			std::cout << "The deleted front of queue: " << BLUE << queueList[index].pop() << RESET << '\n';
		}
		else {
			std::cout << RED << "Empty adapter" << RESET << '\n';
			return -1;
		}
	}
	else if (index < stackList.size() + queueList.size() + dequeList.size()) {
		index -= stackList.size();
		index -= queueList.size();
		int bad_count = 10;
		std::string type_get;
		std::cout << "Input the " << GREEN << "type" << RESET << " of pop (pop_front = 1 / pop_back = 2):\n";
		while (bad_count) {
			std::cout << ">>> ";
			std::cin >> type_get;

			if (type_get == "1") {
				if (!dequeList[index].empty()) {
					std::cout << "The deleted front of deque: " << BLUE << dequeList[index].pop_front() << RESET << '\n';
				}
				else {
					std::cout << RED << "Empty adapter" << RESET << '\n';
					return -1;
				}
				break;
			}
			else if (type_get == "2") {
				if (!dequeList[index].empty()) {
					std::cout << "The deleted back of deque: " << BLUE << dequeList[index].pop_back() << RESET << '\n';
				}
				else {
					std::cout << RED << "Empty adapter" << RESET << '\n';
					return -1;
				}
				break;
			}
			else if (type_get == "abort") {
				break;
			}
			else {
				std::cout << RED << "TypePop = '" << type_get << "' is not valid type for pop element\n" << RESET;
				bad_count--;
			}
		}

		std::cout << '\n';

		if (bad_count == 0) {
			return -1;
		}
		else if (type_get == "abort") {
			return -1;
		}
	}


	return 0;
}