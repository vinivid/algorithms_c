#include "data_structures.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
/////////////////////////////////////
            Vetor amortizado
////////////////////////////////////
*/

vector_int construct_vec_i(int size){
    vector_int vec;
    if(size < 0){
        printf("\n\nERRO: TAMANHO NEGATIVO EM VETOR\n\n");
        vec.elem = NULL;
        vec._private_end_ptr = NULL;
        vec._private_mem_end_ptr = NULL;
        return vec;
    }

    if(size == 0){
        vec.elem = NULL;
        vec._private_end_ptr = NULL;
        vec._private_mem_end_ptr = NULL;

        return vec;
    }

    vec.elem = (int *)malloc(size * sizeof(int));
    vec._private_end_ptr = vec.elem + size;
    vec._private_mem_end_ptr = vec.elem + size;

    if(vec.elem == NULL){
        printf("\n\nERRO: ALOCACAO DE MEMORIA FALHOU\n\n");
        vec.elem = NULL;
        vec._private_end_ptr = NULL;
        vec._private_mem_end_ptr = NULL;
        return vec;
    }
    return vec;
}

void init_vec_i(vector_int *vec, int val){
    for(int i = 0; i < vec->_private_end_ptr - vec->elem; ++i){
        vec->elem[i] = val;
    }
}

int size_vec_i(vector_int *vec){
    return (int)((vec->_private_end_ptr) - vec->elem);
}

int capacity_vec_i(vector_int *vec){
    return (int)((vec->_private_mem_end_ptr) - vec->elem);
}

void destroy_vec_i(vector_int *vec){
    free(vec->elem);
    vec->elem = NULL;
    vec->_private_end_ptr = NULL;
    vec->_private_mem_end_ptr = NULL;
}

bool is_empty_vec_i(vector_int *vec){
    return vec->elem == vec->_private_end_ptr ? true:false;
}

void resize_vec_i(vector_int *vec, int val){
    vec->_private_end_ptr = vec->elem + (val+1);
}

int push_back_vec_i(int val, vector_int *vec){
    if(vec->_private_end_ptr - vec->elem == 0){
        vec->elem = (int *)malloc(sizeof(int));

        if(vec->elem == NULL){
            printf("\n\nERRO: ALOCACAO DE MEMORIA FALHOU\n\n");
            return 1;
        }

        vec->_private_end_ptr = vec->elem + 1;
        vec->_private_mem_end_ptr = vec->elem + 1;

        vec->elem[0] = val;

        return 0;
    }else if(vec->_private_end_ptr >= vec->_private_mem_end_ptr){
        int size = (int)(vec->_private_end_ptr - vec->elem);
        int capacity = (int)(vec->_private_mem_end_ptr - vec->elem) * 2;
        vec->elem = realloc(vec->elem, capacity * sizeof(int));

        if(vec->elem == NULL){
            printf("\n\nERRO: RELOCACAO DE MEMORIA FALHOU\n\n");
            return 2;
        }

        vec->_private_end_ptr = vec->elem + size;
        vec->_private_mem_end_ptr = vec->elem + capacity;
        *vec->_private_end_ptr = val;
        ++vec->_private_end_ptr;

        return 0;
    }else{
        *vec->_private_end_ptr = val;
        ++vec->_private_end_ptr;

        return 0;
    }
}

void pop_back_vec_i(vector_int *vec){
    --vec->_private_end_ptr;
}

int shrink_to_fit_vec_i(vector_int *vec){
    int new_size = (int)(vec->_private_end_ptr - vec->elem); 
    vec->elem = realloc(vec->elem, new_size * sizeof(int));
    if(vec->elem == NULL){
        printf("\n\nERRO: ALOCACAO DE MEMORIA FALHOU\n\n");
        return 1;
    }

    vec->_private_end_ptr = vec->elem + new_size;
    vec->_private_mem_end_ptr = vec->_private_end_ptr;
    return 0;
}

int erase_vec_i(vector_int *vec, int* element){
    int size = (int)(vec->_private_end_ptr - vec->elem);
    int capacity = (int)(vec->_private_mem_end_ptr - vec->elem);    
    int *tmp = (int *)malloc( capacity * sizeof(int));
    if(tmp == NULL){
        printf("\n\nERRO:: ALOCACAO DE MEMORIA FALHOU\n\n");
        return 1;
    }

    int left = (int)(element - vec->elem);

    for(int i = left -1; i > -1; --i){
        tmp[i] = vec->elem[i];
    }

    for(int i = left+1; i < size; ++i){
        tmp[i - 1] = vec->elem[i];  
    }

    free(vec->elem);
    vec->elem = tmp;
    vec->_private_end_ptr = vec->elem + size-1;
    vec->_private_mem_end_ptr = vec->elem + capacity;
    return 0;
}

/*
/////////////////////////////////////////////////////
                    Stack
/////////////////////////////////////////////////////
*/

struct data_structure_stack_int{
    int *start;
    int *end;
    int *capacity;
};

stack_int* construct_stack_i() {
    stack_int *tmp = (stack_int *)malloc(sizeof(stack_int));
    tmp->start = NULL;
    tmp->end = NULL;
    tmp->capacity = NULL;

    return tmp;
}

void destroy_stack_i(stack_int *stck) {
    if(stck->start == NULL) return;

    free(stck->start);
    free(stck);
}

int get_top_stack_i(stack_int *stck) {
    if(stck->start == stck->end){
        printf("\n\nERRO:: SEM VALOR NO TOPO PARA RETORNAR\n\n");
        return -451;
    }

    return *(stck->end - 1);
}

int set_top_stack_i(int val, stack_int *stck) {
    if(stck->start == stck->end) {
        printf("\n\nERRO:: SEM VALOR NO TOPO PARA RETORNAR\n\n");
        return 1;
    }

    *(stck->end - 1) = val;
    return 0;
}

int push_back_stack_i(int val, stack_int *stck) {
    if(stck->end - stck->start == 0) {
        stck->start = (int *)malloc(sizeof(int));

        if (stck->start == NULL) {
            printf("\n\nERRO:: ALOCACAO DE MEMORIA FALHOU\n\n");
            return 1;
        }

        stck->end = stck->start + 1;
        stck->capacity = stck->start +1;
        stck->start[0] = val;

        return 0;
    }else if(stck->end >= stck->capacity) {
        int size = (int)(stck->end - stck->start);
        int capacity = (int)(stck->capacity - stck->start) * 2;

        stck->start = realloc(stck->start, capacity * sizeof(int));

        if(stck->start == NULL) {
            printf("\n\nERRO:: REALOCACAO DE MEMORIA FALHOU\n\n");
            return 2;
        }

        stck->end = stck->start + size;
        stck->capacity = stck->start + capacity;

        *stck->end = val;
        ++stck->end;

        return 0;
    }else{
        *stck->end = val;
        ++stck->end;

        return 0;
    }
}

int pop_back_stack_i(stack_int *stck) {
    if(stck->end - stck->start) {
        --stck->end;
        return *stck->end;
    }else {
        printf("ERRO:: NAO HA ELEMENTOS PARA REMOVER");
        return -451;
    }
}

int size_stack_i(stack_int *stck){
    return (int)(stck->end - stck->start);
}

int capacity_stack_i(stack_int *stck){
    return (int)(stck->capacity - stck->start);
}

bool is_empty_stack_i(stack_int *stck){
    return stck->start == stck->end ? true:false;
}


/*
/////////////////////////////////////////////////////
                    Queue
/////////////////////////////////////////////////////
*/

struct data_structure_queue_int {
    //O current front representa o index da front no momento
    int curr_front;
    int curr_end;

    int* start;
    int* capacity;
};

queue_int* construct_queue_i() {
    queue_int* tmp = (queue_int *)malloc(sizeof(queue_int));

    tmp->start = NULL;
    tmp->capacity = NULL;

    return tmp;
}

void destroy_queue_i(queue_int *que) {
    free(que->start);
    free(que);
}

int front_queue_i(queue_int *que) {
    return que->start[que->curr_front];
}

int back_queue_i(queue_int *que) {
    return que->start[que->curr_end];
}

int push_queue_i(int val, queue_int *que) {
    if(&que->start[que->curr_front] - que->start == 0) {
        que->start = (int *)malloc(sizeof(int));

        if(que->start == NULL) {
            printf("\n\nERRO:: ALOCACAO DE MEMORIA FALHOU\n\n");
            return 1;
        }

        que->capacity = que->start + 1;
        que->curr_front = 0;

        que->start[0] = val;
        return 0;
    }else if(&que->start[que->curr_end + 1] == &que->start[que->curr_front]){
        int sz = (int)(que->capacity - que->start);
        int n_capacity = sz * 2;

        int *tmp = (int *)malloc(n_capacity * sizeof(int));
        int tmp_pos = 0;


        if (tmp == NULL) {
            printf("\n\nERRO: ALOCACO DE MEMORIA FALHOU\n\n");
            return 1;
        }


        for(int i = que->curr_front; i < sz; ++i) {
            tmp[tmp_pos] = que->start[i];
            ++tmp_pos; 
        }

        int left_part = (int)(&que->start[que->curr_end] - que->start);
        for (int i = 0; i < left_part; ++i){
            tmp[tmp_pos] = que->start[i];
            ++tmp_pos;
        }

        free(que->start);
        que->start = tmp;
        que->capacity = que->start + n_capacity;

        que->curr_front = 0;
        que->curr_end = sz;
        que->start[que->curr_end] = val;

        return 0;
    }else{
        if(&que->start[que->curr_end + 1] == que->capacity) {
            que->start[0] = val;
            que->curr_end = 0;
            return 0;
        }else{
            ++que->curr_end;
            que->start[que->curr_end] = val;
            return 0;
        }
    }
}

int pop_queue_i(queue_int *que) {
    if (&que->start[que->curr_front + 1] == que->capacity ) {
        int tmp = que->start[que->curr_front];
        que->curr_front = 0;
        return tmp;
    } else {
        int tmp = que->start[que->curr_front];
        ++que->curr_front;
        return tmp;
    }
}

int size_queue_i(queue_int *que) {
    if (que->curr_end <= que->curr_front) {
        int part1 = (int)(&que->start[que->curr_end] - que->start);
        int part2 = (int)(que->capacity - &que->start[que->curr_front]);
        return part1 + part2;
    }else{
        return (int)(que->start[que->curr_end] - que->start[que->curr_front]);
    }
}

int shrink_to_fit_queue_i(queue_int *que) {
        int sz = size_queue_i(que);

        int *tmp = (int *)malloc(sz * sizeof(int));
        int tmp_pos = 0;


        if (tmp == NULL) {
            printf("\n\nERRO: ALOCACO DE MEMORIA FALHOU\n\n");
            return 1;
        }


        for(int i = que->curr_front; i < sz; ++i) {
            tmp[tmp_pos] = que->start[i];
            ++tmp_pos; 
        }

        int left_part = (int)(&que->start[que->curr_end] - que->start);
        for (int i = 0; i < left_part; ++i){
            tmp[tmp_pos] = que->start[i];
            ++tmp_pos;
        }

        free(que->start);
        que->start = tmp;
        que->capacity = que->start + sz;

        que->curr_front = 0;
        que->curr_end = sz;

        return 0;
}

bool is_empty_queue_i(queue_int *que) {
    return size_queue_i(que) ? false:true;
}