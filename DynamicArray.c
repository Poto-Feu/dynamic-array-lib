#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "DynamicArray.h"

#define DEFAULT_SIZE 15

typedef size_t size_t;

struct DynamicArray
{
    size_t type_size;
    size_t elements_n; //Number of currently stored elements
    size_t element_capacity; //Number of elements that can be stored
    void *content;
    bool is_alloc;
};

DynamicArray *DynamicArray_init(size_t type_size)
{
    DynamicArray *new_DA = malloc(sizeof(DynamicArray));

    if(!new_DA) return NULL;

    new_DA->type_size = type_size;
    new_DA->elements_n = 0;
    new_DA->element_capacity = 0;
    new_DA->content = NULL;
    new_DA->is_alloc = false;

    return new_DA;
}

DynamicArray *DynamicArray_init_and_reserve(size_t type_size, size_t element_number)
{
    DynamicArray *new_DA = malloc(sizeof(DynamicArray));

    if(!new_DA) return NULL;

    new_DA->type_size = type_size;
    new_DA->elements_n = 0;
    new_DA->element_capacity = element_number;
    new_DA->content = malloc(new_DA->type_size * element_number);
    if(!new_DA->content) {
        free(new_DA);
        return NULL;
    }
    new_DA->is_alloc = true;

    return new_DA;
}

void DynamicArray_free(DynamicArray **DA)
{
    if(!DA) return;
    else if((*DA)->is_alloc) free((*DA)->content);
    free(*DA);
}

int DynamicArray_reserve(DynamicArray *DA, size_t element_number)
{
    if(!DA) return -1;
    else if(DA->element_capacity > element_number) return 0;
    else {
        void *temp_ptr = realloc(DA->content, element_number * DA->type_size);

        if(!temp_ptr) return -1;
        else {
            DA->content = temp_ptr;
            DA->is_alloc = true;
            DA->element_capacity = element_number;
            return 0;
        }
    }
}

int DynamicArray_shrink(DynamicArray *DA, size_t element_number)
{
    if(!DA) return -1;
    else if(element_number >= DA->element_capacity) {
        free(DA->content);
        DA->elements_n = 0;
        DA->content = NULL;
        DA->is_alloc = false;

        return 0;
    } else {
        void *temp_ptr = realloc(DA->content, DA->type_size * (DA->elements_n - element_number));

        if(!temp_ptr) return -1;
        else {
            DA->element_capacity -= element_number;
            if(DA->elements_n > DA->element_capacity) DA->elements_n = DA->element_capacity;
            return 0;
        }
    }
}

size_t DynamicArray_get_size(DynamicArray *DA)
{
    return DA->elements_n;
}

size_t DynamicArray_get_capacity(DynamicArray *DA)
{
    return DA->element_capacity;
}

void *DynamicArray_get_element(DynamicArray *DA, size_t index)
{
    if(index >= DA->elements_n) return NULL;
    else {
        char *DA_content_char = (char *)DA->content;
        return DA_content_char + (index * DA->type_size);
    }
}

int DynamicArray_add_element(DynamicArray *DA, void *element)
{
    if(DA->elements_n + 1 > DA->element_capacity) {
        if(DynamicArray_reserve(DA, DA->elements_n + 1) != 0) return -1;
    }
    memcpy((char *)DA->content + (DA->elements_n * DA->type_size), element, DA->type_size);
    ++DA->elements_n;

    return 0;
}
