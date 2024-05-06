#include "Sequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "ImmutableListSequence.hpp"
#include "MutableArraySequence.hpp"
#include "MutableListSequence.hpp"

#define EXIT	"exit\n"
#define RESET	"\033[0m"
#define RED		"\033[1;31m"
#define YELLOW	"\033[1;33m"
#define GREEN	"\033[1;32m"
#define BLUE	"\033[1;34m"
#define LINE "============================================================================================================================================================\n"
#define LANE "------------------------------------------------------------------------------------------------------------------------------------------------------------\n"

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>

// -----------------------------------------------------------------------------------------------------------------
// Variable struct

template <typename T>
struct Var {
	std::string name;
	std::string typeseq;
	Sequence<T>* seq;

	Var(std::string name, std::string typeseq, Sequence<T>* seq) : name(name), typeseq(typeseq), seq(seq) {}
};

template <typename T>
using Variable = Var<T>;

template <typename T>
std::unique_ptr<Variable<T>> VariableFactory(std::string name, std::string typeseq, Sequence<T>* seq) {
	return Variable<T>(name, typeseq, seq);
}

template <typename T>
std::vector<Variable<T>> vars;

// -----------------------------------------------------------------------------------------------------------------
// Declaration

void menu();
void run();
int create_seq();
int remove_seq();
int check_state();
int print_seq();
int get();
int set();
int push();
int pop();
int get_size();
int is_empty();
int get_subseq();
int concat();
int find();
int count();

// -----------------------------------------------------------------------------------------------------------------
// 

void menu() {
	std::cout << LINE;
	std::cout << std::setw(80) << "MENU\n";
	std::cout << LINE;
	std::cout << std::setw(75) << GREEN << "Available Commands:\n" << RESET;
	std::cout << GREEN << "> 0) exit \n" << RESET;									// YES
	std::cout << GREEN << "> 1) menu\n" << RESET;									// YES
	std::cout << GREEN << "> 2) create sequence\n" << RESET;						// YES
	std::cout << GREEN << "> 3) remove sequence\n" << RESET;						// YES
	std::cout << GREEN << "> 4) check state\n" << RESET;							// YES
	std::cout << GREEN << "> 5) print sequence\n" << RESET;							// YES
	std::cout << GREEN << "> 6) get\n" << RESET;									// YES
	std::cout << GREEN << "> 7) set\n" << RESET;									// YES
	std::cout << GREEN << "> 8) push\n" << RESET;									// YES
	std::cout << GREEN << "> 9) pop\n" << RESET;									// YES
	std::cout << GREEN << "> 10) get size\n" << RESET;								// YES
	std::cout << GREEN << "> 11) is empty\n" << RESET;								// YES
	std::cout << GREEN << "> 12) get subsequence\n" << RESET;						// 
	std::cout << GREEN << "> 13) concatenation\n" << RESET;							// YES
	std::cout << GREEN << "> 14) find\n" << RESET;									// YES
	std::cout << GREEN << "> 15) count\n" << RESET;									// YES
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
		else if (command == "2") { // create
			system("cls");
			state = create_seq();
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
		else if (command == "3") { // remove
			system("cls");
			state = remove_seq();
			if (state) {
				system("cls");
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			menu();
			bad_count = 10;
		}
		else if (command == "4") { // check state
			system("cls");
			check_state();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			menu();
		}
		else if (command == "5") { // print sequence
			system("cls");
			state = print_seq();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "6") { // get
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
		else if (command == "7") { // set
			system("cls");
			state = set();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "8") { // push
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
		else if (command == "9") { // pop
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
		else if (command == "10") { // get size
			system("cls");
			state = get_size();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "11") { // is empty
			system("cls");
			state = is_empty();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "12") { // get subseq
			system("cls");
			state = get_subseq();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "13") { // concat
			system("cls");
			state = concat();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "14") { // find
			system("cls");
			state = find();
			std::cout << ">>> ";
			std::cin >> command;
			system("cls");
			if (state) {
				std::cout << YELLOW << "The operation was aborted\n" << RESET;
			}
			menu();
			bad_count = 10;
		}
		else if (command == "15") { // count
			system("cls");
			state = count();
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
// Variable search function by name

int findVarByName(std::string nameseq) {
	for (int i = 0; i < vars<int>.size(); ++i) {
		if (vars<int>[i].name == nameseq) {
			return i;
		}
	}
	return -1;
}

// -----------------------------------------------------------------------------------------------------------------

void promptAbort() {
	std::cout << LANE;
	std::cout << "Enter '" << RED << "abort" << RESET << "' to finish the operation prematurely (the operation will not be executed)\n";
	std::cout << LANE;
}

// -----------------------------------------------------------------------------------------------------------------
// Functions for creating sequence & variable of sequence

bool isValidSizeSeq(const std::string& s_size) {
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

bool isValidName(const std::string& nameseq) {
	bool flag = false;
	if (nameseq.size() == 0 || isdigit(nameseq[0])) {
		return false;
	}
	for (int i = 0; i < nameseq.size(); ++i) {
		if (isdigit(nameseq[i])) {
			flag = true;
		}
		else if (!isdigit(nameseq[i]) && flag || !isalpha(nameseq[i]) && !isdigit(nameseq[i]) && nameseq[i] != '_') {
			return false;
		}
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

std::string getTypeSeq() {
	std::cout << GREEN << "Sequence\n" << RESET;
	std::cout << GREEN << "|--ListSequence\n" << RESET;
	std::cout << GREEN << "|   |--MutableListSequence (mls)\n" << RESET;
	std::cout << GREEN << "|   |--ImmutableListSequence (imls)\n" << RESET;
	std::cout << GREEN << "|\n" << RESET;
	std::cout << GREEN << "|--ArraySequence\n" << RESET;
	std::cout << GREEN << "    |--MutableArraySequence (mas)\n" << RESET;
	std::cout << GREEN << "    |--ImmutableArraySequence (imas)\n" << RESET;
	std::cout << "Input the type of sequence (mls / imls / mas / imas)\n";

	std::string typeseq;
	int bad_count = 10;

	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> typeseq;

		if (typeseq == "mls") {
			break;
		}
		else if (typeseq == "imls") {
			break;
		}
		else if (typeseq == "mas") {
			break;
		}
		else if (typeseq == "imas") {
			break;
		}
		else if (typeseq == "abort") {
			break;
		}
		else {
			std::cout << RED << "TypeSeq = '" << typeseq << "' is not valid type of sequnce\n" << RESET;
			bad_count--;
		}
	}

	if (bad_count == 0) {
		return "ERR-0001-ATTEXP"; // attempts expired
	}
	else if (typeseq == "abort") {
		return "ERR-1111-FUNCINTERR"; // function interrupted
	}
	return typeseq;
}

int getSizeSeq() {
	std::string s_sizeseq;
	int sizeseq = -1;
	int bad_count = 10;

	std::cout << "Input the " << GREEN << "size" << RESET << " of sequence (0 <= size <= 1000)\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_sizeseq;
		if (isValidSizeSeq(s_sizeseq)) {
			size_t pos;
			sizeseq = std::stoi(s_sizeseq, &pos);
			break;
		}
		else if (s_sizeseq == "abort") {
			break;
		}
		else {
			std::cout << RED << "SizeSeq = '" << s_sizeseq << "' is not valid size for sequnce\n" << RESET;
			bad_count--;
		}
	}

	if (s_sizeseq == "abort") {
		return -1111;
	}
	else if (bad_count == 0) {
		return -1;
	}

	return sizeseq;
}

int getTypeFill() {
	std::string s_typefill;
	int typefill = -1;
	int bad_count = 10;

	std::cout << "Input the " << GREEN << "type of fill" << RESET << " (1 = by default element / 2 = by hand)\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_typefill;
		if (s_typefill == "1" || s_typefill == "2") {
			if (s_typefill == "1") {
				typefill = 1;
			}
			else {
				typefill = 2;
			}
			break;
		}
		else if (s_typefill == "abort") {
			break;
		}
		else {
			std::cout << RED << "TypeFill = '" << s_typefill << "' is not type of fill sequnce\n" << RESET;
			bad_count--;
		}
	}

	if (bad_count == 0) {
		return -1;
	}
	else if (s_typefill == "abort") {
		return -1111;
	}

	return typefill;
}

std::string getNameVar() {
	promptAbort();

	std::string nameseq;
	int bad_count = 10;

	std::cout << "Input the " << GREEN << "name" << RESET << " of sequence (A-Z && a-z && all digits in the end of name):\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> nameseq;

		if (nameseq == "abort") {
			break;
		}
		else if (isValidName(nameseq)) {
			if (findVarByName(nameseq) == -1) {
				break;
			}
			else {
				std::cout << RED << "NameSeq = '" << nameseq << "' is already taken\n" << RESET;
				bad_count--;
			}
		}
		else {
			std::cout << RED << "NameSeq = '" << nameseq << "' is not valid name of sequence\n" << RESET;
			bad_count--;
		}
	}

	if (bad_count == 0) {
		return "ERR-0001-ATTEXP"; // attempts expired
	}
	else if (nameseq == "abort") {
		return "ERR-1111-FUNCINTERR"; // function interrupted
	}

	return nameseq;
}



int fillSeq(Sequence<int>*& seq, int size, int typefill) {
	Sequence<int>* new_seq = seq->Factory();

	int bad_count = 10;
	std::string element;
	std::string forERR = "NONE";

	if (typefill == 1) {
		std::cout << "Input the " << GREEN << "default element" << RESET << " for sequence\n";

		while (bad_count) {
			std::cout << ">>> ";
			std::cin >> element;

			if (isValidInt(element)) {
				size_t pos;
				int el;
				for (int i = 0; i < size; ++i) {
					el = std::stoi(element, &pos);
					try {
						new_seq = new_seq->push_back(el);
					}
					catch (const Exception& e) {
						forERR = e.getErrorMessage();
						break;
					}
				}
				break;
			}
			else if (element == "abort") {
				forERR = "ERR-1111-FUNCINTERR";
			}
			else {
				std::cout << RED << "Element = '" << element << "' is not valid element for sequence\n" << RESET;
				bad_count--;
			}
		}
	}
	else {
		int i = 0;
		while (bad_count && i < size) {
			std::cout << "Input the " << GREEN << "[" << i << "]" << RESET << " for sequence\n";
			std::cout << ">>> ";
			std::cin >> element;

			if (isValidInt(element)) {
				size_t pos;
				int el = std::stoi(element, &pos);
				try {
					new_seq = new_seq->push_back(el);
				}
				catch (const Exception& e) {
					forERR = e.getErrorMessage();
					break;
				}
				i++;
			}
			else if (element == "abort") {
				forERR = "ERR-1111-FUNCINTERR";
			}
			else {
				std::cout << RED << "Element = '" << element << "' is not valid element for sequence\n" << RESET;
				bad_count--;
			}
		}
	}

	if (forERR.substr(0, 3) == "ERR") {
		return -1110;
	}
	else if (forERR != "NONE") {
		std::cout << forERR << '\n';
		return -11;
	}

	seq = new_seq;
	return 0;
}

void infoSeq(int index) {
	if (index >= 0 && index < vars<int>.size()) {
		std::cout << LANE;
		std::cout << std::setw(65) << "Sequence " << index << '\n';
		std::cout << LANE;

		std::cout << "The name of sequence " << BLUE << vars<int>[index].name << '\n' << RESET;
		if ((vars<int>[index].typeseq).compare("mls") == 0) {
			std::cout << "The type of sequence: " << BLUE << "MutableListSequence\n" << RESET;
		}
		else if ((vars<int>[index].typeseq).compare("imls") == 0) {
			std::cout << "The type of sequence: " << BLUE << "ImmutableListSequence\n" << RESET;
		}
		else if ((vars<int>[index].typeseq).compare("mas") == 0) {
			std::cout << "The type of sequence: " << BLUE << "MutableArraySequence\n" << RESET;
		}
		else if ((vars<int>[index].typeseq).compare("imas") == 0) {
			std::cout << "The type of sequence: " << BLUE << "ImmutableArraySequence\n" << RESET;
		}

		std::cout << "The size of sequence: " << BLUE << vars<int>[index].seq->get_size() << '\n' << RESET;
		std::cout << LANE;
	}
	else {
		std::cout << RED << "Index is out of range\n" << RESET;
	}
}

void createVar(Sequence<int>* seq, std::string typeseq, std::string name) {
	Variable<int>* new_var = new Variable<int>(name, typeseq, seq);
	vars<int>.push_back(*new_var);
}

int create_seq() {
	std::string namevar = getNameVar();
	if (namevar.substr(0, 3) == "ERR") {
		return -1010;
	}

	std::string typeseq = getTypeSeq();
	if (typeseq.substr(0, 3) == "ERR") {
		return -1010;
	}

	int sizeseq = getSizeSeq();
	if (sizeseq < 0) {
		return -1010;
	}

	int typefill = getTypeFill();
	if (typefill < 0 || typefill > 2) {
		return -1010;
	}


	Sequence<int>* seq;
	int state = 0;

	if (typeseq.compare("imls") == 0) {
		seq = new ImmutableListSequence<int>();
	}
	else if (typeseq.compare("imas") == 0) {
		seq = new ImmutableArraySequence<int>();
	}
	else if (typeseq.compare("mls") == 0) {
		seq = new MutableListSequence<int>();
	}
	else if (typeseq.compare("mas") == 0) {
		seq = new MutableArraySequence<int>();
	}

	state = fillSeq(seq, sizeseq, typefill);

	if (state == 0) {
		createVar(seq, typeseq, namevar);
		infoSeq(vars<int>.size() - 1);
		return 0;
	}
	else {
		return -1110;
	}

}

// -----------------------------------------------------------------------------------------------------------------
// Core-function of sequence selection from the vector

int select() {
	promptAbort();
	check_state();

	std::string nameseq;
	int bad_count = 10;

	std::cout << "Input the " << GREEN << "name" << RESET << " of sequence\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> nameseq;
		int index = findVarByName(nameseq);
		if (index != -1) {
			return index;
		}
		if (nameseq == "abort") {
			return -1011;
		}
		else {
			std::cout << RED << "Name seq = '" << nameseq << "' is not found\n" << RESET;
			bad_count--;
		}
	}

	return -1011;
}

// -----------------------------------------------------------------------------------------------------------------
// Functions for remove sequence & variable of sequence

int remove_seq() {
	if (vars<int>.size() == 0) {
		std::cout << RED << "There are no sequences\n" << RESET;
		return -1110;
	}

	int index = select();

	if (index < 0) {
		return -1110;
	}

	vars<int>.erase(vars<int>.begin() + index);
	return 0;
}

// -----------------------------------------------------------------------------------------------------------------
// Functions for output

int check_state() {
	if (vars<int>.size() == 0) {
		std::cout << RED << "There are no sequences\n" << RESET;
		return 1;
	}

	for (int i = 0; i < vars<int>.size(); ++i) {
		infoSeq(i);
	}

	return 0;
}

int print_seq() {
	if (vars<int>.size() == 0) {
		std::cout << RED << "There are no sequences\n" << RESET;
		return -11;
	}

	int index = select();

	if (index < 0) {
		return -11;
	}

	std::cout << BLUE << "Sequence content:\n" << RESET;
	for (int i = 0; i < vars<int>[index].seq->get_size(); ++i) {
		std::cout << vars<int>[index].seq->get(i) << " ";
	}
	std::cout << "\n";

	return 0;
}

// -----------------------------------------------------------------------------------------------------------------
// Get / set / push / pop / size

int get() {
	if (vars<int>.size() == 0) {
		std::cout << RED << "There are no sequences\n" << RESET;
		return -10;
	}

	int index = select();

	if (index < 0) {
		return -1000;
	}

	std::string s_indexseq;
	int indexseq = -1;
	int bad_count = 10;

	std::cout << "Input the " << GREEN << "index" << RESET << " of sequence\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_indexseq;
		if (isValidIndex(s_indexseq, vars<int>[index].seq->get_size())) {
			size_t pos;
			indexseq = std::stoi(s_indexseq, &pos);
			std::cout << BLUE << vars<int>[index].name << "[" << RESET << s_indexseq << BLUE << "]" << RESET << " = " << vars<int>[index].seq->get(indexseq) << "\n";
			break;
		}
		else if (s_indexseq == "abort") {
			break;
		}
		else {
			std::cout << RED << "Index = '" << s_indexseq << "' is not valid index for sequnce\n" << RESET;
			bad_count--;
		}
	}

	if (bad_count == 0) {
		return -1011;
	}
	else if (s_indexseq == "abort") {
		return -1;
	}
	return indexseq;
}

int set() {
	if (vars<int>.size() == 0) {
		std::cout << RED << "There are no sequences\n" << RESET;
		return -10;
	}

	int index = select();

	if (index < 0) {
		return -1111;
	}

	std::string s_indexseq;
	size_t indexseq = -1;
	std::string s_value;
	int value;
	int bad_count = 10;
	bool isnew = false;

	std::cout << "Input the " << GREEN << "index" << RESET << " of sequence\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_indexseq;
		if (isValidIndex(s_indexseq, vars<int>[index].seq->get_size())) {
			size_t pos;
			indexseq = std::stoi(s_indexseq, &pos);
			break;
		}
		else if (s_indexseq == "abort") {
			break;
		}
		else {
			std::cout << RED << "Index = '" << s_indexseq << "' is not valid index for sequnce\n" << RESET;
			bad_count--;
		}
	}

	if (bad_count == 0) {
		return -1011;
	}
	else if (s_indexseq == "abort") {
		return -1;
	}

	bad_count = 10;

	std::cout << "Input the " << GREEN << "new value" << RESET << " of " << BLUE << vars<int>[index].name << "[" << RESET << indexseq << BLUE << "]" << RESET << "\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_value;
		if (isValidInt(s_value)) {
			size_t pos;
			int value = std::stoi(s_value, &pos);

			if (vars<int>[index].typeseq != "imas" && vars<int>[index].typeseq != "imls") {
				vars<int>[index].seq = vars<int>[index].seq->set(value, indexseq);
			}
			else {
				Sequence<int>* seq_copy = vars<int>[index].seq->Factory();
				for (int i = 0; i < vars<int>[index].seq->get_size(); ++i) {
					seq_copy = seq_copy->push_back(vars<int>[index].seq->get(i));
				}
				seq_copy = vars<int>[index].seq->set(value, indexseq);

				int j = 1;
				std::string new_name = vars<int>[index].name;
				new_name += std::to_string(j);
				while (isValidName(new_name) == false && j < 10) {
					j++;
					new_name.pop_back();
					new_name += std::to_string(j);
				}
				createVar(seq_copy, vars<int>[index].typeseq, new_name);
				isnew = true;
			}
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
		return -101;
	}
	else if (isnew) {
		std::cout << LANE;
		std::cout << BLUE << "When the operation was performed, a new sequence was created\n" << RESET;
		std::cout << LANE;
		return 0;
	}
	else if (bad_count == 0) {
		return -111;
	}

	return 0;
}

int push() {
	if (vars<int>.size() == 0) {
		std::cout << RED << "There are no sequences\n" << RESET;
		return -10;
	}

	int index = select();

	if (index < 0) {
		return -1111;
	}

	std::string s_typepush;
	std::string s_value;
	int value;
	int bad_count = 10;
	bool isnew = false;

	std::cout << "Input the " << GREEN << "type of pushing" << RESET << " in sequence (1 = push_back / 2 = push_front)\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_typepush;
		if (s_typepush == "1" || s_typepush == "2") {
			break;
		}
		else if (s_typepush == "abort") {
			break;
		}
		else {
			std::cout << RED << "Type pushing = '" << s_typepush << "' is not type of pushing for sequnce\n" << RESET;
			bad_count--;
		}
	}

	if (bad_count == 0) {
		return -1011;
	}
	else if (s_typepush == "abort") {
		return -1;
	}

	bad_count = 10;

	std::cout << "Input the " << GREEN << "value for push" << RESET << "\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_value;
		if (isValidInt(s_value)) {
			size_t pos;
			int value = std::stoi(s_value, &pos);

			if (vars<int>[index].typeseq != "imas" && vars<int>[index].typeseq != "imls") {
				if (s_typepush == "1") {
					vars<int>[index].seq = vars<int>[index].seq->push_back(value);
				}
				else {
					vars<int>[index].seq = vars<int>[index].seq->push_front(value);
				}
			}
			else {
				Sequence<int>* seq_copy = vars<int>[index].seq->Factory();
				for (int i = 0; i < vars<int>[index].seq->get_size(); ++i) {
					seq_copy = seq_copy->push_back(vars<int>[index].seq->get(i));
				}

				if (s_typepush == "1") {
					seq_copy = vars<int>[index].seq->push_back(value);
				}
				else {
					seq_copy = vars<int>[index].seq->push_front(value);
				}

				int j = 1;
				std::string new_name = vars<int>[index].name;
				new_name += std::to_string(j);
				while (isValidName(new_name) == false && j < 10) {
					j++;
					new_name.pop_back();
					new_name += std::to_string(j);
				}
				createVar(seq_copy, vars<int>[index].typeseq, new_name);
				isnew = true;
			}
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
		return -101;
	}
	else if (isnew) {
		std::cout << LANE;
		std::cout << BLUE << "When the operation was performed, a new sequence was created\n" << RESET;
		std::cout << LANE;
		return 0;
	}
	else if (bad_count == 0) {
		return -111;
	}

	return 0;
}

int pop() {
	if (vars<int>.size() == 0) {
		std::cout << RED << "There are no sequences\n" << RESET;
		return -10;
	}

	int index = select();

	if (index < 0) {
		return -1111;
	}

	std::string s_typepop;
	std::string s_value;
	std::string forERR = "NONE";
	int value;
	int bad_count = 10;
	bool isnew = false;

	if (vars<int>[index].seq->empty() == 1) {
		std::cout << RED << "Nothing to remove from sequence\n" << RESET;
		return -11;
	}

	std::cout << "Input the " << GREEN << "type of pop" << RESET << " in sequence (1 = pop_back / 2 = pop_front)\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_typepop;
		if (s_typepop == "1" || s_typepop == "2") {
			break;
		}
		else if (s_typepop == "abort") {
			break;
		}
		else {
			std::cout << RED << "Type pushing = '" << s_typepop << "' is not type of pop for sequnce\n" << RESET;
			bad_count--;
		}
	}

	if (bad_count == 0) {
		return -1011;
	}
	else if (s_typepop == "abort") {
		return -1;
	}

	bad_count = 10;

	if (vars<int>[index].typeseq != "imas" && vars<int>[index].typeseq != "imls") {
		try {
			if (s_typepop == "1") {
				vars<int>[index].seq->pop_back();
			}
			else {
				vars<int>[index].seq->pop_front();
			}
		}
		catch (const Exception& e) {
			forERR = e.getErrorMessage();
		}

		if (forERR != "NONE") {
			std::cout << forERR << '\n';
			return -11;
		}
	}
	else {
		Sequence<int>* seq_copy = vars<int>[index].seq->Factory();
		for (int i = 0; i < vars<int>[index].seq->get_size(); ++i) {
			seq_copy = seq_copy->push_back(vars<int>[index].seq->get(i));
		}
		try {
			if (s_typepop == "1") {
				seq_copy = vars<int>[index].seq->pop_back();
			}
			else {
				seq_copy = vars<int>[index].seq->pop_front();
			}
		}
		catch (const Exception& e) {
			forERR = e.getErrorMessage();
		}

		if (forERR != "NONE") {
			std::cout << forERR << '\n';
			return -11;
		}

		int j = 1;
		std::string new_name = vars<int>[index].name;
		new_name += std::to_string(j);
		while (isValidName(new_name) == false && j < 10) {
			j++;
			new_name.pop_back();
			new_name += std::to_string(j);
		}
		createVar(seq_copy, vars<int>[index].typeseq, new_name);
		isnew = true;
	}

	if (isnew) {
		std::cout << LANE;
		std::cout << BLUE << "When the operation was performed, a new sequence was created\n" << RESET;
		std::cout << LANE;
		return 0;
	}

	return 0;
}

int get_size() {
	if (vars<int>.size() == 0) {
		std::cout << RED << "There are no sequences\n" << RESET;
		return -10;
	}

	int index = select();
	if (index < 0) {
		return -101;
	}

	std::cout << BLUE << vars<int>[index].name << ".size = " << RESET << vars<int>[index].seq->get_size() << "\n";

	return 0;
}

int is_empty() {
	if (vars<int>.size() == 0) {
		std::cout << RED << "There are no sequences\n" << RESET;
		return -10;
	}

	int index = select();
	if (index < 0) {
		return -101;
	}

	if (index != -1) {
		if (vars<int>[index].seq->empty()) {
			std::cout << BLUE << vars<int>[index].name << " is empty" << RESET << "\n";
		}
		else {
			std::cout << BLUE << vars<int>[index].name << " is not empty" << RESET << "\n";
		}
	}

	return 0;
}

// -----------------------------------------------------------------------------------------------------------------
// 

int concat() {
	if (vars<int>.size() == 0) {
		std::cout << RED << "There are no sequences\n" << RESET;
		return -10;
	}

	bool isnew = false;

	int index_1 = select();

	if (index_1 < 0) {
		return -1111;
	}

	std::string wait = "";
	std::cout << ">>> ";
	std::cin >> wait;

	system("cls");

	int index_2 = select();

	if (index_2 < 0) {
		return -1111;
	}

	if (vars<int>[index_1].typeseq != "imas" && vars<int>[index_1].typeseq != "imls") {
		vars<int>[index_1].seq = vars<int>[index_1].seq->concat(*(vars<int>[index_2].seq));
	}
	else {
		Sequence<int>* seq_copy = vars<int>[index_1].seq->Factory();
		for (int i = 0; i < vars<int>[index_1].seq->get_size(); ++i) {
			seq_copy = seq_copy->push_back(vars<int>[index_1].seq->get(i));
		}
		for (int i = 0; i < vars<int>[index_2].seq->get_size(); ++i) {
			seq_copy = seq_copy->push_back(vars<int>[index_2].seq->get(i));
		}

		int j = 1;
		std::string new_name = vars<int>[index_1].name;
		new_name += std::to_string(j);
		while (isValidName(new_name) == false && j < 10) {
			j++;
			new_name.pop_back();
			new_name += std::to_string(j);
		}
		createVar(seq_copy, vars<int>[index_1].typeseq, new_name);
		isnew = true;
	}

	if (isnew) {
		std::cout << LANE;
		std::cout << BLUE << "When the operation was performed, a new sequence was created\n" << RESET;
		std::cout << LANE;
	}

	return 0;
}

int get_subseq() {
	if (vars<int>.size() == 0) {
		std::cout << RED << "There are no sequences\n" << RESET;
		return -10;
	}

	int index = select();

	if (index < 0) {
		return -1000;
	}

	std::string s_firstindex;
	int firstindex = -1;
	std::string s_secondtindex;
	int secondindex = -1;
	int bad_count = 10;
	bool isnew = false;

	std::cout << "Input the " << GREEN << "the start-index " << RESET "you want to take" << " in this sequence\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_firstindex;
		if (isValidIndex(s_firstindex, vars<int>[index].seq->get_size())) {
			size_t pos;
			firstindex = std::stoi(s_firstindex, &pos);
			break;
		}
		else if (s_firstindex == "abort") {
			break;
		}
		else {
			std::cout << RED << "Start-index = '" << s_firstindex << "' is not valid index\n" << RESET;
			bad_count--;
		}
	}

	if (s_firstindex == "abort") {
		return -101;
	}
	else if (bad_count == 0) {
		return -1;
	}

	bad_count = 10;

	std::cout << "Input the " << GREEN << "the finish-index " << RESET "you want to take" << " in this sequence\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_secondtindex;
		if (isValidIndex(s_secondtindex, vars<int>[index].seq->get_size())) {
			size_t pos;
			secondindex = std::stoi(s_secondtindex, &pos);
			break;
		}
		else if (s_secondtindex == "abort") {
			break;
		}
		else {
			std::cout << RED << "Finish-index = '" << s_secondtindex << "' is not valid index\n" << RESET;
			bad_count--;
		}
	}

	if (s_secondtindex == "abort") {
		return -101;
	}
	else if (bad_count == 0) {
		return -1;
	}

	int j = 1;
	std::string new_name = "sub";
	new_name += vars<int>[index].name;

	try {
		Sequence<int>* res_seq = vars<int>[index].seq->Factory();
		for (int i = firstindex; i <= secondindex; ++i) {
			res_seq = res_seq->push_back(vars<int>[index].seq->get(i));
		}
		createVar(res_seq, vars<int>[index].typeseq, new_name);
		isnew = true;
	}
	catch (const Exception& e) {
		return -1111;
	}


	if (isnew) {
		std::cout << LANE;
		std::cout << BLUE << "When the operation was performed, a new sequence was created\n" << RESET;
		std::cout << LANE;
	}
	return 0;
}

int find() {
	if (vars<int>.size() == 0) {
		std::cout << RED << "There are no sequences\n" << RESET;
		return -10;
	}

	int index = select();

	if (index < 0) {
		return -1000;
	}

	std::string s_value;
	int value = -1;
	int bad_count = 10;

	std::cout << "Input the " << GREEN << "the value you want to find" << RESET << " in sequence\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_value;
		if (isValidInt(s_value)) {
			size_t pos;
			int value = std::stoi(s_value, &pos);
			std::cout << BLUE << vars<int>[index].name << ".find(" << value << ") = " << RESET;
			std::cout << vars<int>[index].seq->find(value) << "\n";
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
		return -101;
	}
	else if (bad_count == 0) {
		return -111;
	}

	return 0;
}

int count() {
	if (vars<int>.size() == 0) {
		std::cout << RED << "There are no sequences\n" << RESET;
		return -10;
	}

	int index = select();

	if (index < 0) {
		return -1000;
	}

	std::string s_value;
	int value = -1;
	int bad_count = 10;

	std::cout << "Input the " << GREEN << "the value you want to count" << RESET << " in sequence\n";
	while (bad_count) {
		std::cout << ">>> ";
		std::cin >> s_value;
		if (isValidInt(s_value)) {
			size_t pos;
			int value = std::stoi(s_value, &pos);
			std::cout << BLUE << vars<int>[index].name << ".count(" << value << ") = " << RESET;
			std::cout << vars<int>[index].seq->count(value) << "\n";
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
		return -101;
	}
	else if (bad_count == 0) {
		return -111;
	}

	return 0;
}
