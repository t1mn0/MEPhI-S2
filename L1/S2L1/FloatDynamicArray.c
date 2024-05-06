#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DynamicArray.h"
#include "ErrorHandling.h"



void concatenationFloat(DynamicArray* array_1, DynamicArray* array_2) {
    int size_1 = array_1->size;
    array_1->FieldInfo.resize(array_1, array_2->size);
    for (int i = size_1; i < array_1->size; i++) {
        float* q = array_2->FieldInfo.getElement(array_2, i - size_1);
        array_1->FieldInfo.setElement(array_1, i, q);
    }
}



FI createFloatFieldInfo();
float* initFloatDynamicArray(unsigned int size);
void resizeFloatDynamicArray(DynamicArray* array, int delta);
void printFloatDynamicArray(DynamicArray* array);
void addFloatElement(DynamicArray* array, float* valueP);
void setFloatElement(DynamicArray* array, unsigned int index, float* valueP);
float* getFloatElement(DynamicArray* array, unsigned int index);
void sortFloat(DynamicArray* array, unsigned int param);
void mapFloat(DynamicArray* array, float (*func)(float*));
DynamicArray* whereFloat(DynamicArray* array, int (*func)(float*));



FI createFloatFieldInfo() {
    FI float_fi = {
    .initDynamicArray = initFloatDynamicArray,
    .resize = resizeFloatDynamicArray,
    .print = printFloatDynamicArray,
    .addElement = addFloatElement,
    .setElement = setFloatElement,
    .getElement = getFloatElement,
    .concatenation = concatenationFloat,
    .sort = sortFloat,
    .map = mapFloat,
    .where = whereFloat
    };
    return float_fi;
}



float* initFloatDynamicArray(unsigned int size) {
    float* array = (float*)malloc(sizeof(float) * size);
    if (array == NULL) handleErrorCode(MEMORY_ALLOCARTION_ERROR);
    for (int i = 0; i < size; i++) {
        array[i] = 0.0;
    }
    return array;
}

void resizeFloatDynamicArray(DynamicArray* array, int delta) {
    int size = array->size;
    array->size = size + delta;
    array->array = (float*)realloc(array->array, sizeof(float) * (size + delta));
    if (array->array == NULL) handleErrorCode(MEMORY_ALLOCARTION_ERROR);
    if (delta > 0) {
        for (int i = size; i < size + delta; i++) {
            float zero = 0.0;
            array->FieldInfo.setElement(array, i, &zero);
        }
    }
}

void printFloatDynamicArray(DynamicArray* array) {
    for (int i = 0; i < array->size; i++) {
        printf("%f\n", ((float*)array->array)[i]);
    }
}

void addFloatElement(DynamicArray* array, float* valueP) {
    array->FieldInfo.resize(array, 1);
    ((float*)(array->array))[array->size - 1] = *valueP;
}

void setFloatElement(DynamicArray* array, unsigned int index, float* valueP) {
    if (index > array->size) handleErrorCode(ARRAY_INDEX_OUT_OF_BOUNDS_ERROR);
    ((float*)(array->array))[index] = *valueP;
}

float* getFloatElement(DynamicArray* array, unsigned int index) {
    if (index > array->size) handleErrorCode(ARRAY_INDEX_OUT_OF_BOUNDS_ERROR);
    return &(((float*)array->array)[index]);
}

int compareFloat_1(float* arg1, float* arg2) {
    float num1 = *arg1;
    float num2 = *arg2;

    if (num1 < num2) {
        return -1;
    }
    else if (num1 > num2) {
        return 1;
    }
    else {
        return 0;
    }
}

int compareFloat_2(float* arg1, float* arg2) {
    return -compareFloat_1(arg1, arg2);
}

void sortFloat(DynamicArray* array, unsigned int param) {
    if (param == 0) {
        qsort(array->array, array->size, array->element_size, compareFloat_1);
    }
    else if (param == 1) {
        qsort(array->array, array->size, array->element_size, compareFloat_2);
    }
}

void mapFloat(DynamicArray* array, float (*func)(float*)) {
    for (int i = 0; i < array->size; i++) {
        float z = func(array->FieldInfo.getElement(array, i));
        array->FieldInfo.setElement(array, i, &z);
    }
}

DynamicArray* whereFloat(DynamicArray* array, int (*func)(float*)) {
    DynamicArray* new_array = createDynamicArray(1, 4);
    int isFirst = 1;
    for (int i = 0; i < array->size; i++) {
        float* v = array->FieldInfo.getElement(array, i);
        if (func(v) == 1) {
            if (isFirst == 1) {
                new_array->FieldInfo.setElement(new_array, 0, v);
                isFirst = 0;
            }
            else {
                new_array->FieldInfo.addElement(new_array, v);
            }
        }
    }
    return new_array;
}