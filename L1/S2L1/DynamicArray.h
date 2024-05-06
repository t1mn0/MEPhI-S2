#ifndef DynamicArray_H
#define DynamicArray_H

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

DynamicArray* createDynamicArray(int size, unsigned int element_size);

#endif DynamicArray_H