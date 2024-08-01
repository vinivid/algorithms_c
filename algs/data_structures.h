#pragma once
#include <stdbool.h>

typedef struct data_structure_vector_int{
    int size;
    int capacity;
    int *elem;
    int *end_ptr;
    int *mem_end_ptr;
}vector_int;

int construct_vec_i(vector_int *vec, int size);
void init_vec_i(vector_int *vec, int val);
void destroy_vec_i(vector_int *vec);
bool is_empty_i(vector_int *vec);
void resize_i(vector_int *vec, int val);
int push_back_i(int val, vector_int *vec);
void pop_back_i(vector_int *vec);
int shrink_to_fit_i(vector_int *vec);
int erase_vec_i(vector_int *vec, int* element);