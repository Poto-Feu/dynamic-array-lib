#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

#include <stddef.h>

typedef struct DynamicArray DynamicArray;

/*Note: a slot is a space available for storing an element. It may or may not be occupied.*/

/*All functions returning an int value return a non-zero value if an error happened.*/

/*Returns NULL if the memory allocation failed.*/
DynamicArray *DynamicArray_init(size_t type_size);
DynamicArray *DynamicArray_init_and_reserve(size_t type_size, size_t el_number);

/*Necessary to avoid memory leaks.*/
void DynamicArray_free(DynamicArray **DA);

/*This function (re)allocates memory for slots according to the element_number parameter - it will
do nothing if the element_number parameter is inferior to the current number of slots present in the
DynamicArray - use shrink instead.*/
int DynamicArray_reserve(DynamicArray *DA, size_t element_number);

/*This function shrink the DynamicArray by removing the specified number of element slots. If
the specified value is superior to the element capacity of the DynamicArray, the memory is freed.*/
int DynamicArray_shrink(DynamicArray *DA, size_t element_number);

/*Return the number of currently stored elements.*/
size_t DynamicArray_get_size(DynamicArray *DA);
/*Return the number of elements slots available.*/
size_t DynamicArray_get_capacity(DynamicArray *DA);
/*Return NULL if the index is out of bounds.*/
void *DynamicArray_get_element(DynamicArray *DA, size_t index);

/*If there is not enough available slots, more memory will be allocated - this will cause
performance issues if often called without care - don't forget to use reserve.*/
int DynamicArray_add_element(DynamicArray *DA, void *element);

#endif
