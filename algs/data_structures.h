#pragma once
#include <stdbool.h>
/*
    Se deseja usar void * só mudar para void * na sua implementação, se quiser
ser mais correto ainda use macros eg: max e min da stdlib, analogamente se
quiser que o tipo seja float ou etc só trocar o tipo, se pa seja até melhor
porque você re-olha a implementação pra ela ficar mais na sua cabeça.
*/

/*
    Estrutura de dado similar ao do STL vector do c++ não segue as regras do rudinei
por não ser completamente privada. Entretanto por causa disso acaba sendo mais
segura pois evita do usúario de utilizar um pointeiro para o dado, de forma a ter
acesso facil, e depois alguma das funções mudar esse pointeiro e der algum erro.
*/

typedef struct data_structure_vector_int {
    int *elem;
    int *_private_end_ptr;
    int *_private_mem_end_ptr;
}vector_int;

vector_int construct_vec_i (int size);
void init_vec_i (vector_int *vec, int val);
void destroy_vec_i (vector_int *vec);
int size_vec_i (vector_int *vec);
int capacity_vec_i (vector_int *vec);
bool is_empty_vec_i (vector_int *vec);
void resize_vec_i (vector_int *vec, int val);

//Retorna 0 se foi efetuado com sucesso e differente de 0 caso teve algum erro
int push_back_vec_i (int val, vector_int *vec);
void pop_back_vec_i (vector_int *vec);
int shrink_to_fit_vec_i (vector_int *vec);
int erase_vec_i (vector_int *vec, int* element);

/*
    Stack, também chamda de pilha, é uma estrutura que tem o intuito de ter accesos
e modificações apenas através de seu topo, seguindo a lógica do LIFO. 
    Nesta implementação utiliza um vetor armortizdo como base, entrtanto ele pode 
utilizar de  outros tipos de containers para implementar sua função.
*/

typedef struct data_structure_stack_int stack_int;

//Construtor padrão de uma stack
stack_int* construct_stack_i();

//deleta todos os elementos da stack
void destroy_stack_i(stack_int *stck);

//retorna o valor do topo da stack   
int get_top_stack_i(stack_int *stck);

//modifica o valor do topo da stack
int set_top_stack_i(int val, stack_int* stck);

//Retorna 0 se foi efetuado com sucesso e 1 caso teve algum erro
int push_back_stack_i (int val, stack_int *stck);

//Remove o ultimo item da stack e retorna seu valor
int pop_back_stack_i (stack_int *stck);

//Retorna o tamanho da stack
int size_stack_i(stack_int *stck);

//Retorna a capacidade reservada para a stack
int capacity_stack_i(stack_int *stck);

//Checa se a stack esta vazia
bool is_empty_stack_i (stack_int *stck);

/*
    Queue também conhecida como fila, é uma estrutura de dados que tem o 
mesmo comportamento de uma "fila" que é o, primeiro a entrar primeiro a 
sair chamado de FIFO (First in first out).

*/

typedef struct data_structure_queue_int queue_int;

//Construtor padrão da queue
queue_int* construct_queue_i();

//Destrutor padrão da queue
void destroy_queue_i(queue_int* que);

//Retorna o valor da frete da fila
int front_queue_i(queue_int* que);

//Retorna o valor da ultima posição da fila
int back_queue_i(queue_int* que);

//Coloaca um valor no fim da fila
int push_queue_i(int val, queue_int* que);

//Remove um valor da frente da fila
int pop_queue_i(queue_int* que);

//Retorna o tamanho da fila
int size_queue_i(queue_int* que);

//Retorna a capacidade reservada para a fila
int capacity_queue_i(queue_int* que);

//Realoca a fila para o tamanho total que seus objetos ocupam
int shrink_to_fit_queue_i(queue_int* que);

//Retorna true se a fila estiver vazia
bool is_empty_queue(queue_int* que);