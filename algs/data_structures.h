#pragma once
#include <stdbool.h>

typedef struct data_structure_vector_int{
    int *elem;
    int *_private_end_ptr;
    int *_private_mem_end_ptr;
}vector_int;

vector_int construct_vec_i(int size);
void init_vec_i(vector_int *vec, int val);
void destroy_vec_i(vector_int *vec);
int size_vec_i(vector_int *vec);
int capacity_vec_i(vector_int *vec);
bool is_empty_vec_i(vector_int *vec);
void resize_vec_i(vector_int *vec, int val);
int push_back_vec_i(int val, vector_int *vec);
void pop_back_vec_i(vector_int *vec);
int shrink_to_fit_vec_i(vector_int *vec);
int erase_vec_i(vector_int *vec, int* element);