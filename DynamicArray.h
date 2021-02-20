/*
    Copyright (C) 2020 Adrien Saad

    This file is part of DynamicArrayLib.

    DynamicArrayLib is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DynamicArrayLib is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with DynamicArrayLib. If not, see <https://www.gnu.org/licenses/>.
*/

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

/*This function (re)allocates memory for slots according to the element_number parameter. It will do
nothing if the element_number parameter is inferior to the current number of slots present in the
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

/*Delete the element in the specified index (if it exists) and move the elements following it to
fill the gap. Return NULL if out of bounds*/
int DynamicArray_remove_element(DynamicArray *DA, size_t pos);

#endif
