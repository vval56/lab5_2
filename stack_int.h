#include <stdio.h>
#include <stdlib.h>

#ifndef STACK_INT_H
#define STACK_INT_H

typedef struct STACK{
    int *stack_queue;
    int top;
    int capacity;
}STACK;

typedef struct GARBAGE{
    int * array;
    int size;
}GARBAGE;

int check_int(int *number, char *line);
int empty_line(char *line);
int stack_is_full(STACK *stack);
int stack_is_empty(STACK *stack);
void stack_create(STACK *stack, int new_capacity);
void stack_push(STACK *stack, int number);
int stack_pop(STACK *stack);
int stack_peek(STACK *stack);
void stack_input(STACK *stack);
void find_sum_after_max(STACK *stack, GARBAGE *garbage);
void print_stack(STACK * stack);
void stack_int();

#endif
