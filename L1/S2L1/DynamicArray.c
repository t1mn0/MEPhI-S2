#include <stdlib.h>
#include "FloatDynamicArray.h"
#include "StringDynamicArray.h"
#include "ErrorHandling.h"

typedef struct FI FI;
typedef struct DynamicArray DynamicArray;

typedef struct FI {
    DynamicArray* (*initDynamicArray)(unsigned int size);
    void (*resize)(DynamicArray* array, unsigned int delta);
    void (*print)(DynamicArray* array);
    void (*addElement)(DynamicArray* array, void* valueP);
    void (*setElement)(DynamicArray* array, unsigned int index, void* valueP);
    void* (*getElement)(DynamicArray* array, int index);
    void (*concatenation)(DynamicArray* array1, DynamicArray* array2);
    void (*sort)(DynamicArray* array, unsigned int param);
    void (*map)(DynamicArray* array, void* (*func)(void*));
    DynamicArray* (*where)(DynamicArray* array, int (*func)(void*));
} FI;

typedef struct DynamicArray {
    void* array;
    int size;
    int element_size;
    FI FieldInfo;
} DynamicArray;

FI createFieldInfo(DynamicArray* array) {
    switch (array->element_size) {
    case 4: return createFloatFieldInfo();
    case 8: return createStringFieldInfo();
    default: break;
    }
}

DynamicArray* createDynamicArray(unsigned int size, unsigned int element_size) {
    DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (array == NULL) handleErrorCode(MEMORY_ALLOCARTION_ERROR);
    array->element_size = element_size;
    array->size = size;
    array->FieldInfo = createFieldInfo(array);
    array->array = array->FieldInfo.initDynamicArray(size);
    return array;
}