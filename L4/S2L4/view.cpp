#include "BTree.hpp"

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

// -----------------------------------------------------------------------------------------------------------------
// Memory

unsigned long id = 1;

std::vector<BTree<int>> memory;

// -----------------------------------------------------------------------------------------------------------------
// Declaration

void menu();
void run();
int create_tree();
int check_state();
int print_tree();
int balance();
int get_traversal();
int max_depth();
int insert();
int erase();
int generate_dot();

// -----------------------------------------------------------------------------------------------------------------
// Base

void menu() {
	std::cout << LINE;
	std::cout << std::setw(80) << "MENU\n";
	std::cout << LINE;
	std::cout << std::setw(75) << GREEN << "Available Commands:\n" << RESET;
	std::cout << GREEN << "> 0) exit \n" << RESET;
	std::cout << GREEN << "> 1) menu\n" << RESET;														
	std::cout << GREEN << "> 2) create tree\n" << RESET;												
	std::cout << GREEN << "> 3) check state\n" << RESET;												
	std::cout << GREEN << "> 4) print tree\n" << RESET;
	std::cout << GREEN << "> 5) balance\n" << RESET;
	std::cout << GREEN << "> 6) get traversal\n" << RESET;	
	std::cout << GREEN << "> 7) max depth\n" << RESET;	
	std::cout << GREEN << "> 8) insert\n" << RESET;	
	std::cout << GREEN << "> 9) erase\n" << RESET;	
	std::cout << GREEN << "> 10) generate dot\n" << RESET;

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
		else if (command == "2") { // create tree
			system("cls");
			state = create_tree();
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
		else if (command == "4") { // print tree
			system("cls");
			state = print_tree();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "5") { // balance
			system("cls");
			state = balance();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "6") { // get traversal
			system("cls");
			state = get_traversal();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "7") { // max depth
			system("cls");
			state = max_depth();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "8") { // insert
			system("cls");
			state = insert();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "9") { // erase
			system("cls");
			state = erase();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "10") { // generate DOT
			system("cls");
			state = generate_dot();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
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
// Support function for create tree

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

// -----------------------------------------------------------------------------------------------------------------
// Create adapter

int fill_tree(BTree<int> &tree) {
	int bad_count = 10;
	std::string element;

	while (bad_count) {
		std::cout << "Input the " << GREEN << "new element" << RESET << " for add to tree:\n";
		std::cout << ">>> ";
		std::cin >> element;

		if (isValidInt(element)) {
			size_t pos;
			int el = std::stoi(element, &pos);
			try {
				tree.insert(el);
			}
			catch (const Exception& e) {
				return -1;
			}
			bad_count = 10;
		}
		else if (element == "!") {
			return 0;
		}
		else if (element == "abort") {
			return -1;
		}
		else {
			std::cout << RED << "Element = '" << element << "' is not valid element for tree\n" << RESET;
			bad_count--;
		}
	}

	if (!bad_count) {
		return -1;
	}

	return 0;
}

int create_tree() {
	promptAbort();

	BTree<int> tree = *(new BTree<int>());

	std::cout << "Root = " << RED << "nullptr" << RESET << " \n";
	std::cout << "Input '" << RED << "!" << RESET << "' to finish entering.\n\n";
	
	int code = fill_tree(tree);

	if (!code) {
		memory.push_back(tree);
		return 0;
	}
	else {
		return -1;
	}
}

// -----------------------------------------------------------------------------------------------------------------
// Print state 

void info_tree(BTree<int>& tree, int index) {
	std::cout << "--------------------------------------------------\n";
	std::cout << "|                                                |\n";
	std::cout << "|                  " << BLUE << "Binary Tree [" << RESET << index << BLUE << "]" << RESET << " \n";
	std::cout << "| " << BLUE << "Max depth: " << RESET << tree.max_depth() << "\n";
	std::cout << "| " << BLUE << "Node count: " << RESET << tree.LPR().get_size() << "\n";
	std::cout << "|                                                |\n";
	std::cout << "--------------------------------------------------\n";
}

int check_state() {
	if (memory.size() == 0) {
		std::cout << "\n" << LINE;
		std::cout << RED << "There are no one tree\n" << RESET;
		std::cout << LINE;
	}
	else {
		for (int i = 0; i < memory.size(); ++i) {
			info_tree(memory[i], i);
		}
	}

	return 0;
}

int select() {
	promptAbort();
	check_state();

	if (memory.size() == 0) return -1;

	int bad_count = 10;
	std::string s_index;

	std::cout << "Input the " << GREEN << "index" << RESET << " of tree\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_index;
		if (s_index == "abort") {
			return -1;
		}
		if (isValidIndex(s_index, memory.size())) {
			int index = stoi(s_index);
			return index;
		}
		else {
			std::cout << RED << "Invalid index: " << s_index << " is not found\n" << RESET;
			bad_count--;
		}
	}

	if (!bad_count) {
		return -1;
	}
}

int print_tree() {
	int index = select();

	if (index < 0) {
		return -1;
	}

	if (index < memory.size()) {
		std::cout << BLUE << "B-Tree content:\n" << RESET;
		memory[index].show(memory[index].getRoot());
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------------------
// Basic functions for tree

int balance() {
	int index = select();

	if (index < 0) {
		return -1;
	}

	memory[index].balance();
	std::cout << GREEN << "B-Tree was successfully balanced\n" << RESET;

	return 0;
}

int max_depth() {
	int index = select();

	if (index < 0) {
		return -1;
	}

	std::cout << BLUE << "Maximum depth of this B-Tree:\n" << RESET;
	std::cout << memory[index].max_depth() << std::endl;

	return 0;
}

int insert() {
	int index = select();

	if (index < 0) {
		return -1;
	}

	int bad_count = 10;
	std::string element;

	std::cout << RED << "Warning" << RESET << ": after adding an item to the tree, the tree may not be balanced\n";


	while (bad_count) {
		std::cout << "Input the " << GREEN << "new element" << RESET << " for add to tree:\n";
		std::cout << ">>> ";
		std::cin >> element;

		if (isValidInt(element)) {
			size_t pos;
			int el = std::stoi(element, &pos);
			try {
				memory[index].insert(el);
				return 0;
			}
			catch (const Exception& e) {
				return -1;
			}
			bad_count = 10;
		}
		else if (element == "abort") {
			return -1;
		}
		else {
			std::cout << RED << "Element = '" << element << "' is not valid element for tree\n" << RESET;
			bad_count--;
		}
	}

	if (!bad_count) {
		return -1;
	}

	return 0;
}

int erase() {
	int index = select();

	if (index < 0) {
		return -1;
	}

	int bad_count = 10;
	std::string element;

	while (bad_count) {
		std::cout << "Input the " << GREEN << "value of the node to be deleted" << RESET << " for delete from tree:\n";
		std::cout << ">>> ";
		std::cin >> element;

		if (isValidInt(element)) {
			size_t pos;
			int el = std::stoi(element, &pos);
			try {
				if (!memory[index].search_node(el)) {
					std::cout << YELLOW << "A node with this value was not found\n" << RESET;
				}
				else {
					memory[index].erase(el);
				}
				return 0;
			}
			catch (const Exception& e) {
				return -1;
			}
			bad_count = 10;
		}
		else if (element == "abort") {
			return -1;
		}
		else {
			std::cout << RED << "Element = '" << element << "' is not valid element for tree\n" << RESET;
			bad_count--;
		}
	}

	if (!bad_count) {
		return -1;
	}

	return 0;
}

int generate_dot() {
	int index = select();

	if (index < 0) {
		return -1;
	}

	if (index < memory.size()) {
		std::cout << BLUE << "DOT and PNG files will be created in the project directory and named: " << RESET << GREEN << "tree" << id << RESET << '\n';
		std::string s_id = "tree" + std::to_string(id);
		memory[index].generateDotRepresentation(s_id);
		std::string command = "dot -Tpng " + s_id + " -o " + s_id + ".png";
		std::system(command.c_str());
		id++;
	}

	return 0;
}

int get_traversal() {
	int index = select();

	if (index < 0) {
		return -1;
	}
	
	memory[index].show(memory[index].getRoot());

	std::cout << GREEN << "\n> 1) LRP (postorder)\n" << RESET;
	std::cout << GREEN << "> 2) LPR (inorder)\n" << RESET;
	std::cout << GREEN << "> 3) PRL\n" << RESET;
	std::cout << GREEN << "> 4) PLR (preorder)\n" << RESET;
	std::cout << GREEN << "> 5) RPL\n" << RESET;
	std::cout << GREEN << "> 6) RLP\n\n" << RESET;

	int bad_count = 10;
	std::string type;

	while (bad_count) {
		std::cout << "Input the " << GREEN << "type of traversal" << RESET << " for tree:\n";
		std::cout << ">>> ";
		std::cin >> type;

		if (type == "1") {
			auto traversal = memory[index].LRP();
			for (int i = 0; i < traversal.get_size(); ++i) {
				std::cout << traversal[i] << " ";
			}
			std::cout << '\n';
			return 0;
		}
		else if (type == "2") {
			auto traversal = memory[index].LPR();
			for (int i = 0; i < traversal.get_size(); ++i) {
				std::cout << traversal[i] << " ";
			}
			std::cout << '\n';
			return 0;
		}
		else if (type == "3") {
			auto traversal = memory[index].PRL();
			for (int i = 0; i < traversal.get_size(); ++i) {
				std::cout << traversal[i] << " ";
			}
			std::cout << '\n';
			return 0;
		}
		else if (type == "4") {
			auto traversal = memory[index].PLR();
			for (int i = 0; i < traversal.get_size(); ++i) {
				std::cout << traversal[i] << " ";
			}
			std::cout << '\n';
			return 0;
		}
		else if (type == "5") {
			auto traversal = memory[index].RPL();
			for (int i = 0; i < traversal.get_size(); ++i) {
				std::cout << traversal[i] << " ";
			}
			std::cout << '\n';
			return 0;
		}
		else if (type == "6") {
			auto traversal = memory[index].RLP();
			for (int i = 0; i < traversal.get_size(); ++i) {
				std::cout << traversal[i] << " ";
			}
			std::cout << '\n';
			return 0;
		}
		else if (type == "!") {
			return 0;
		}
		else if (type == "abort") {
			return -1;
		}
		else {
			std::cout << RED << "TypeTraversal = '" << type << "' is not valid type of traversal\n" << RESET;
			bad_count--;
		}
	}

	if (!bad_count) {
		return -1;
	}

	return 0;
}

