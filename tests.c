/*
    Copyright (C) 2021 Adrien Saad

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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "DynamicArray.h"

int main()
{
    struct DummyStruct {
        int a;
        float b;
    };

    struct DummyStruct dummy_1 = { .b = 1 };
    struct DummyStruct dummy_2 = { .b = 2 };
    struct DummyStruct dummy_3 = { .b = 3 };

    struct DummyStruct *dummy_ptr = NULL;
    struct DummyStruct struct_array[3] = { dummy_1, dummy_2, dummy_3 };
    DynamicArray *da = DynamicArray_init_and_reserve(sizeof(struct DummyStruct), 25);

    if(!da) return EXIT_FAILURE;

    assert(DynamicArray_shrink(da, 4) == 0);
    assert(DynamicArray_reserve(da, 50) == 0);
    assert(DynamicArray_get_capacity(da) == 50);

    DynamicArray_add_element(da, &dummy_1);
    DynamicArray_add_element(da, &dummy_2);
    DynamicArray_add_element(da, &dummy_3);

    assert(DynamicArray_remove_element(da, 1) == 0);
    dummy_ptr = DynamicArray_get_element(da, 1);
    assert(dummy_ptr->b == 3);

    assert(DynamicArray_shrink(da, 49) == 0);
    assert(DynamicArray_remove_element(da, 0) == 0);
    DynamicArray_add_multiple_elements(da, struct_array, 2);
    assert(DynamicArray_shrink(da, 30) == 0);

    DynamicArray_free(&da);

    return EXIT_SUCCESS;
}
