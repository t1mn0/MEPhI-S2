#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <errno.h>
#include <limits.h>

#include "DynamicArray.h"
#include "ErrorHandling.h"

#define EXIT "exit\n"
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define LINE "============================================================================================================================================================\n"
#define LANE "------------------------------------------------------------------------------------------------------------------------------------------------------------\n"



typedef struct Variable {
	char* name;
	DynamicArray* arrayP;
} Variable;

Variable* createVar(char* name, unsigned int size, unsigned int element_size) {
	Variable* var = (Variable*)malloc(sizeof(Variable));
	if (var == NULL) handleErrorCode(MEMORY_ALLOCARTION_ERROR);
	var->name = (char*)malloc(strlen(name) + 1);
	strcpy(var->name, name);
	DynamicArray* array = createDynamicArray(size, element_size);
	var->arrayP = array;
	return var;
}

Variable vars[5];
int lastIndex = 0;


void menu();
void run();
void create_array();
void print_state();
void print_array();
void get_element();
void set_element();
void add_element();
void cut_array();
void sort_array();
void concatenate();
void map();
void where();
void remove_array();



void menu() {
	printf("%s", LINE);
	printf("%80s", "MENU\n");
	printf("%s", LINE);
	printf("%75s%s%s", GREEN, "Available Commands:\n", RESET);
	printf("> %s1) menu%s\n", GREEN, RESET);
	printf("> %s2) create_array%s\n", GREEN, RESET);
	printf("> %s3) remove_array%s\n", GREEN, RESET);
	printf("> %s4) print_state%s\n", GREEN, RESET);
	printf("> %s5) print_array%s\n", GREEN, RESET);
	printf("> %s6) get_element%s\n", GREEN, RESET);
	printf("> %s7) set_element%s\n", GREEN, RESET);
	printf("> %s8) add_element%s\n", GREEN, RESET);
	printf("> %s9) cut_array%s\n", GREEN, RESET);
	printf("> %s10) sort_array%s\n", GREEN, RESET);
	printf("> %s11) concatenate%s\n", GREEN, RESET);
	printf("> %s12) map%s\n", GREEN, RESET);
	printf("> %s13) where%s\n\n", GREEN, RESET);
	printf("> %sexit%s\n\n", GREEN, RESET);
	printf("%s", LINE);
}


void run() {
	menu();
	char command[64];
	while (1) {
		printf(">>> ");
		fgets(command, sizeof(command), stdin);
		if (strcmp(command, EXIT) == 0) {
			exit(0);
		}
		else if (strcmp(command, "2\n") == 0) {
			create_array();
		}
		else if (strcmp(command, "4\n") == 0) {
			print_state();
		}
		else if (strcmp(command, "5\n") == 0) {
			print_array();
		}
		else if (strcmp(command, "6\n") == 0) {
			get_element();
		}
		else if (strcmp(command, "7\n") == 0) {
			set_element();
		}
		else if (strcmp(command, "8\n") == 0) {
			add_element();
		}
		else if (strcmp(command, "9\n") == 0) {
			cut_array();
		}
		else if (strcmp(command, "10\n") == 0) {
			sort_array();
		}
		else if (strcmp(command, "11\n") == 0) {
			concatenate();
		}
		else if (strcmp(command, "12\n") == 0) {
			map();
		}
		else if (strcmp(command, "13\n") == 0) {
			where();
		}
		else if (strcmp(command, "1\n") == 0) {
			menu();
		}
		else if (strcmp(command, "3\n") == 0) {
			remove_array();
		}
		else {
			printf("%s", command);
		}
	}
}



int isValidNameOfVar(char name[37]) {
	if (name[0] == '\n' || name[0] == '\0') return 0;
	for (int i = 0; i < 12; i++) {
		if (name[i] == '\0' || name[i] == '\n') {
			return 1;
		}
		if (isalpha(name[i]) == 0 && name[i] != '_') {
			return 0;
		}
	}
	return 1;
}

int isNewName(char name[13]) {
	for (int i = 0; i < lastIndex; i++) {
		if (strcmp(vars[i].name, name) == 0) {
			return 0;
		}
	}
	return 1;
}

int isValidSize(char* size) {
	char* endptr;
	if (size[0] == '\0' || size[0] == '\n') return 0;
	size[strcspn(size, "\n")] = 0;
	size[strcspn(size, "\0")] = 0;

	long num = strtol(size, &endptr, 10);

	if (*endptr == '\0' && num >= INT_MIN && num <= INT_MAX) {
		return 1;
	}
	else {
		return 0;
	}
}

int isValidIndex(int i, char* index) {
	char* endptr;
	index[strcspn(index, "\n")] = 0;
	index[strcspn(index, "\0")] = 0;

	long num = strtol(index, &endptr, 10);

	if (*endptr == '\0') {
		if (num >= 0 && num < vars[i].arrayP->size) {
			return 1;
		}
		else {
			return 0;
		}
	}
}

int typeOfInputElement(char element[33]) {
	char* endptr;
	element[strcspn(element, "\n")] = 0;
	element[strcspn(element, "\0")] = 0;
	strtof(element, &endptr);

	if (*endptr == '\0') {
		return 1; // Строка представима как число float
	}
	else {
		return 0; // Строка не представима как число float
	}
}

void create_array() {
	if (lastIndex >= 5) {
		handleErrorCode(MEMORY_ALLOCARTION_ERROR);
		return;
	}
	while (1) {
		char name[36];
		char varName[13];
		printf("%sInput name of new array (read max 12 characters, (Aa-Zz and '_')):%s ", GREEN, RESET);
		fgets(name, sizeof(name), stdin);
		if (isValidNameOfVar(name) == 1) {
			name[strcspn(name, "\n")] = 0;
			strncpy(varName, name, 12);
			varName[12] = '\0';
			if (isNewName(varName) == 1) {


				printf("%sInput size of new array (integer number 0-256):%s ", GREEN, RESET);
				char size[257];
				int varSize;
				fgets(size, sizeof(size), stdin);
				size[strcspn(size, "\n")] = 0;
				if (isValidSize(size) == 1) {
					varSize = atoi(size);

					Variable* var = (Variable*)malloc(sizeof(Variable));
					int isFloat = 0;
					for (int i = 0; i < varSize; i++) {
						char element[33];
						printf("\n%sInput %s%s[%d]%s:%s", GREEN, RESET, varName, i, GREEN, RESET);
						fgets(element, sizeof(element), stdin);
						if (i == 0) {
							if (typeOfInputElement(element) == 1) {
								char* endptr;
								float e = strtof(element, &endptr);
								var = createVar(varName, varSize, 4);
								var->arrayP->FieldInfo.setElement(var->arrayP, i, &e);
								isFloat = 1;
								vars[lastIndex] = *var;
							}
							else {
								char* e = (char*)malloc(sizeof(char*));
								strcpy(e, element);
								var = createVar(varName, varSize, 8);
								var->arrayP->FieldInfo.setElement(var->arrayP, i, e);
								vars[lastIndex] = *var;
							}
						}
						else {
							if (typeOfInputElement(element) == 1 && isFloat == 1) {
								char* endptr;
								float e = strtof(element, &endptr);
								var->arrayP->FieldInfo.setElement(var->arrayP, i, &e);
							}
							else if (typeOfInputElement(element) == 0 && isFloat == 0) {
								char* e = (char*)malloc(sizeof(char*));
								strcpy(e, element);
								var->arrayP->FieldInfo.setElement(var->arrayP, i, e);
							}
							else {
								i--;
								handleErrorCode(TRY_AGAIN);
								continue;
							}
						}
					}
					lastIndex++;
					printf("\n");
				}
				else {
					printf("%sINVALID_INPUT_ERROR\n%s", RED, RESET);
					printf("%sTRY AGAIN\n%s", RED, RESET);
					continue;
				}
				break;
			}
			else {
				printf("%sTHIS NAME HAS BEEN DECLARED\n%s", RED, RESET);
				continue;
			}
		}
		else {
			printf("%sINVALID_INPUT_ERROR\n%s", RED, RESET);
			printf("%sTRY AGAIN\n%s", RED, RESET);
		}
	}
}



void print_state() {
	printf("%s%85s%s", GREEN, "Memory status:\n", RESET);
	printf("%s", LANE);
	for (int i = 0; i < 5; i++) {
		printf("|%15d%15s", i, "|");
	}
	printf("\n%s", LANE);
	for (int i = 0; i < 5; i++) {
		if (i < lastIndex) {
			printf("|name: %-12s%12s", vars[i].name, "|");
		}
		else {
			printf("|name: %-12s%12s", "NONE", "|");
		}
	}
	printf("\n%s", LANE);
	for (int i = 0; i < 5; i++) {
		if (i < lastIndex) {
			printf("|size:%5d%20s", vars[i].arrayP->size, "|");
		}
		else {
			printf("|size:%5s%20s", "NONE", "|");
		}
	}
	printf("\n%s", LANE);
	for (int i = 0; i < 5; i++) {
		if (i < lastIndex) {
			if (vars[i].arrayP->element_size == 4) {
				printf("|type: float%19s", "|");
			}
			else {
				printf("|type: string%18s", "|");
			}
		}
		else {
			printf("|type: NONE%20s", "|");
		}
	}
	printf("\n%s", LANE);
}



int select_array() {
	if (lastIndex == 0) return -1;
	print_state();
	while (1) {
		char name[36];
		printf("\n%sSelect an array (input a name) :%s ", GREEN, RESET);
		fgets(name, sizeof(name), stdin);
		name[strcspn(name, "\n")] = 0;
		name[strcspn(name, "\0")] = 0;
		for (int i = 0; i < lastIndex; i++) {
			if (strcmp(vars[i].name, name) == 0) {
				return i;
			}
		}
		handleErrorCode(NO_ARRAY);
	}
}

void print_array() {
	int i = select_array();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		printf("\n");
		vars[i].arrayP->FieldInfo.print(vars[i].arrayP);
	}
	printf("\n%s", LINE);
}

void get_element() {
	int i = select_array();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		while (1) {
			printf("\n");
			printf("%sInput index of that array:%s ", GREEN, RESET);
			char index[33];
			int j;
			fgets(index, sizeof(index), stdin);
			index[strcspn(index, "\n")] = 0;
			index[strcspn(index, "\0")] = 0;
			if (isValidIndex(i, index) == 1) {
				j = atoi(index);
				if (vars[i].arrayP->element_size == 4) {
					float* element = vars[i].arrayP->FieldInfo.getElement(vars[i].arrayP, j);
					printf("%s[%d] = %f\n", vars[i].name, j, *element);
				}
				else {
					char* element = vars[i].arrayP->FieldInfo.getElement(vars[i].arrayP, j);
					printf("%s[%d] = %s\n", vars[i].name, j, element);
				}
				break;
			}
			else {
				handleErrorCode(ARRAY_INDEX_OUT_OF_BOUNDS_ERROR);
			}
		}
	}
	printf("\n%s", LINE);
}

void set_element() {
	int i = select_array();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		while (1) {
			printf("\n");
			printf("%sInput index of that array:%s ", GREEN, RESET);
			char index[33];
			int j;
			fgets(index, sizeof(index), stdin);
			index[strcspn(index, "\n")] = 0;
			index[strcspn(index, "\0")] = 0;
			if (isValidIndex(i, index) == 1) {
				j = atoi(index);
				if (vars[i].arrayP->element_size == 4) {
					printf("%sInput value you want to set:%s ", GREEN, RESET);
					char element[65];
					fgets(element, sizeof(element), stdin);
					if (typeOfInputElement(element) == 1) {
						char* endptr;
						float e = strtof(element, &endptr);
						vars[i].arrayP->FieldInfo.setElement(vars[i].arrayP, j, &e);
					}
					else {
						handleErrorCode(INPUT_TYPE_ERROR);
						continue;
					}
				}
				else {
					printf("%sInput value you want to set:%s ", GREEN, RESET);
					char element[65];
					fgets(element, sizeof(element), stdin);
					char* e = (char*)malloc(sizeof(char*));
					element[strcspn(element, "\n")] = 0;
					element[strcspn(element, "\0")] = 0;
					strcpy(e, element);
					if (typeOfInputElement(element) == 0) {
						vars[i].arrayP->FieldInfo.setElement(vars[i].arrayP, j, e);
					}
					else {
						handleErrorCode(INPUT_TYPE_ERROR);
						continue;
					}
				}
				break;
			}
			else {
				handleErrorCode(ARRAY_INDEX_OUT_OF_BOUNDS_ERROR);
				continue;
			}
		}
	}
	printf("\n%s", LINE);
}

void add_element() {
	int i = select_array();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		while (1) {
			printf("\n");
			if (vars[i].arrayP->element_size == 4) {
				printf("%sInput value you want to add:%s ", GREEN, RESET);
				char element[65];
				fgets(element, sizeof(element), stdin);
				if (typeOfInputElement(element) == 1) {
					char* endptr;
					float e = strtof(element, &endptr);
					vars[i].arrayP->FieldInfo.addElement(vars[i].arrayP, &e);
				}
				else {
					handleErrorCode(INPUT_TYPE_ERROR);
					continue;
				}
			}
			else {
				printf("%sInput value you want to add:%s ", GREEN, RESET);
				char element[65];
				fgets(element, sizeof(element), stdin);
				char* e = (char*)malloc(sizeof(char*));
				element[strcspn(element, "\n")] = 0;
				element[strcspn(element, "\0")] = 0;
				strcpy(e, element);
				if (typeOfInputElement(element) == 0) {
					vars[i].arrayP->FieldInfo.addElement(vars[i].arrayP, e);
				}
				else {
					handleErrorCode(INPUT_TYPE_ERROR);
					continue;
				}
			}
			break;
		}
	}
	printf("\n%s", LINE);
}

int isValidNewSize(int i, char* index) {
	char* endptr;
	index[strcspn(index, "\n")] = 0;
	index[strcspn(index, "\0")] = 0;

	long num = strtol(index, &endptr, 10);

	if (*endptr == '\0') {
		if (num >= 0 && num <= vars[i].arrayP->size) {
			return 1;
		}
		else {
			return 0;
		}
	}
}

void cut_array() {
	int i = select_array();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		while (1) {
			printf("\n");
			printf("%sInput new size-1 (will take the first elements):%s ", GREEN, RESET);
			char index[33];
			int j;
			fgets(index, sizeof(index), stdin);
			index[strcspn(index, "\n")] = 0;
			index[strcspn(index, "\0")] = 0;
			if (isValidNewSize(i, index) == 1) {
				j = atoi(index);
				printf("%d %d\n", j, vars[i].arrayP->size);
				if (j == vars[i].arrayP->size) {
					return;
				}
				int delta = j - vars[i].arrayP->size;
				if (-delta == vars[i].arrayP->size) {
					handleErrorCode(INVALID_INPUT_ERROR);
					continue;
				}
				vars[i].arrayP->FieldInfo.resize(vars[i].arrayP, delta);
				break;
			}
			else {
				handleErrorCode(INVALID_INPUT_ERROR);
				continue;
			}
		}
	}
	printf("\n%s", LINE);
}



void sort_array() {
	int i = select_array();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		while (1) {
			printf("\n");
			printf("%sInput type of sort: increasing or decreasing [i / d]%s ", GREEN, RESET);
			char c[2];
			fgets(c, sizeof(c), stdin);
			if (strcmp(c, "d") == 0) {
				vars[i].arrayP->FieldInfo.sort(vars[i].arrayP, 1);
			}
			else if (strcmp(c, "i") == 0) {
				vars[i].arrayP->FieldInfo.sort(vars[i].arrayP, 0);
			}
			else {
				handleErrorCode(INPUT_TYPE_ERROR);
				continue;
			}
			break;
		}
	}
	printf("\n%s", LINE);
}

void concatenate() {
	printf("%sNOW YOU SELECT THE ARRAY TO WHICH THE FOLLOWING ARRAY WILL BE SELECTED\n%s", YELLOW, RESET);
	int i1 = select_array();
	if (i1 < 0) {
		handleErrorCode(NO_ARRAY);
		return;
	}
	printf("%sNOW YOU ARE NOW SELECT AN ARRAY THAT YOU WILL ADD TO THE ONE YOU HAVE ALREADY SELECTED\n%s", YELLOW, RESET);
	int i2 = select_array();
	if (i2 < 0) {
		handleErrorCode(NO_ARRAY);
		return;
	}
	while (1) {
		if (vars[i1].arrayP->element_size == vars[i2].arrayP->element_size) {
			vars[i1].arrayP->FieldInfo.concatenation(vars[i1].arrayP, vars[i2].arrayP);
			break;
		}
		else {
			handleErrorCode(INPUT_TYPE_ERROR);
			continue;
		}
	}
}

float exampleMapF(float* b) {
	return *b * *b;
}

char* exampleMapS(char* b) {
	strcat(b, " by: John");
	return b;
}

void map() {
	int i = select_array();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		if (vars[i].arrayP->element_size == 4) {
			vars[i].arrayP->FieldInfo.map(vars[i].arrayP, *exampleMapF);
		}
		else {
			vars[i].arrayP->FieldInfo.map(vars[i].arrayP, *exampleMapS);
		}
	}
	printf("\n%s", LINE);
}



int exampleWhereF(float* b) {
	if ((*b) > 0) return 1;
	return 0;
}

int exampleWhereS(char* b) {
	if ((b[0] == 'E') || (b[0] == 'e') || (b[0] == 'Y') || (b[0] == 'y') || (b[0] == 'U') ||
		(b[0] == 'U') || (b[0] == 'O') || (b[0] == 'o') || (b[0] == 'A') || (b[0] == 'a')) return 1;
	return 0;
}

void where() {
	int i = select_array();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		if (vars[i].arrayP->element_size == 4) {
			vars[i].arrayP = vars[i].arrayP->FieldInfo.where(vars[i].arrayP, *exampleWhereF);
		}
		else {
			vars[i].arrayP = vars[i].arrayP->FieldInfo.where(vars[i].arrayP, *exampleWhereS);
		}
	}
	printf("\n%s", LINE);
}



void remove_array() {
	int i = select_array();
	if (i < 0) {
		handleErrorCode(NO_ARRAY);
	}
	else {
		printf("%sDeleting...%s\n", GREEN, RESET);
		//printf("%d %d %d", lastIndex, );
		int j = 0;
		for (j = i; j + 1 < lastIndex; j++) {
			vars[j] = vars[j + 1];
		}
		lastIndex--;
		printf("%sSuccessfully deleted%s\n", GREEN, RESET);
	}
}
