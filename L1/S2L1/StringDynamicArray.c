#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DynamicArray.h"
#include "ErrorHandling.h"



void concatenationString(DynamicArray* array_1, DynamicArray* array_2) {
    int size_1 = array_1->size;
    array_1->FieldInfo.resize(array_1, array_2->size);
    for (int i = size_1; i < array_1->size; i++) {
        float* q = array_2->FieldInfo.getElement(array_2, i - size_1);
        array_1->FieldInfo.setElement(array_1, i, q);
    }
}



char** initStringDynamicArray(unsigned int size);
void resizeStringDynamicArray(DynamicArray* array, int delta);
void printStringDynamicArray(DynamicArray* array);
void addStringElement(DynamicArray* array, char* valueP);
void setStringElement(DynamicArray* array, unsigned int index, char* valueP);
char* getStringElement(DynamicArray* array, unsigned int index);
void sortString(DynamicArray* array, unsigned int param);
void mapString(DynamicArray* array, char* (*func)(char*));
DynamicArray* whereString(DynamicArray* array, int (*func)(char*));



FI createStringFieldInfo() {
    FI string_fi = {
    .initDynamicArray = initStringDynamicArray,
    .resize = resizeStringDynamicArray,
    .print = printStringDynamicArray,
    .addElement = addStringElement,
    .setElement = setStringElement,
    .getElement = getStringElement,
    .concatenation = concatenationString,
    .sort = sortString,
    .map = mapString,
    .where = whereString
    };
    return string_fi;
}



char** initStringDynamicArray(unsigned int size) {
    char** array = (char**)malloc(sizeof(char*) * size);
    if (array == NULL) handleErrorCode(MEMORY_ALLOCARTION_ERROR);
    for (int i = 0; i < size; i++) {
        array[i] = "EMPTY!";
    }
    return array;
}

void setStringElement(DynamicArray* array, unsigned int index, char* valueP) {
    if (index > array->size) handleErrorCode(ARRAY_INDEX_OUT_OF_BOUNDS_ERROR);
    ((char**)(array->array))[index] = valueP;
}

char* getStringElement(DynamicArray* array, unsigned int index) {
    if (index > array->size) handleErrorCode(ARRAY_INDEX_OUT_OF_BOUNDS_ERROR);
    return ((char**)(array->array))[index];
}

void resizeStringDynamicArray(DynamicArray* array, int delta) {
    int size = array->size;
    array->size = size + delta;
    array->array = (char**)realloc(array->array, sizeof(char*) * (size + delta));
    if (array->array == NULL) handleErrorCode(MEMORY_ALLOCARTION_ERROR);
    if (delta > 0) {
        for (int i = size; i < size + delta; i++) {
            array->FieldInfo.setElement(array, i, " ");
        }
    }
}

void printStringDynamicArray(DynamicArray* array) {
    for (int i = 0; i < array->size; i++) {
        printf("%s\n", ((char**)(array->array))[i]);
    }
}

void addStringElement(DynamicArray* array, char* valueP) {
    array->FieldInfo.resize(array, 1);
    array->FieldInfo.setElement(array, array->size - 1, valueP);
}

int compareString_1(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int compareString_2(const void* a, const void* b) {
    return -strcmp(*(const char**)a, *(const char**)b);
}

void sortString(DynamicArray* array, unsigned int param) {
    if (param == 0) {
        qsort(array->array, array->size, array->element_size, compareString_1);
    }
    else if (param == 1) {
        qsort(array->array, array->size, array->element_size, compareString_2);
    }
}

void mapString(DynamicArray* array, char* (*func)(char*)) {
    char* s;
    for (int i = 0; i < array->size; i++) {
        s = array->FieldInfo.getElement(array, i);
        array->FieldInfo.setElement(array, i, func(s));
    }
}

DynamicArray* whereString(DynamicArray* array, int (*func)(char*)) {
    DynamicArray* new_array = createDynamicArray(1, 8);
    int isFirst = 1;
    for (int i = 0; i < array->size; i++) {
        if (func(array->FieldInfo.getElement(array, i)) == 1) {
            if (isFirst) {
                new_array->FieldInfo.setElement(new_array, 0, array->FieldInfo.getElement(array, i));
                isFirst = 0;
            }
            else {
                new_array->FieldInfo.addElement(new_array, array->FieldInfo.getElement(array, i));
            }
        }
    }
    return new_array;
}
