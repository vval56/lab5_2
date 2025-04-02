#include <stdio.h>
#include <stdlib.h>

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

typedef struct STACK_CHAR{
    int top;
    char * queue;
    int capacity;
}STACK_CHAR;

typedef struct QUEUE_EXPRESSION{
    char * expression;
    int size;
}QUEUE;

typedef struct DOUBLE_STACK{
    int top;
    double * queue;
    int capacity;
}DOUBLE_STACK;

int char_stack_is_full(STACK_CHAR *stack);
int char_stack_is_empty(STACK_CHAR *stack);
void char_stack_create(STACK_CHAR *stack, int new_capacity);
void char_stack_push(STACK_CHAR *stack, char operand);
char char_stack_pop(STACK_CHAR *stack);
char char_stack_peek(STACK_CHAR *stack);
int double_stack_is_full(DOUBLE_STACK *stack);
int double_stack_is_empty(DOUBLE_STACK *stack);
void double_stack_create(DOUBLE_STACK *stack, int new_capacity);
void double_stack_push(DOUBLE_STACK *stack, double num);
double double_stack_pop(DOUBLE_STACK *stack);
void error_in_file(int value);
int priority(char op);
double calculate(double num1, double num2, char op);
void infix_to_postfix(QUEUE *problem, const char *line, STACK_CHAR *stack);
double evaluate_postfix(QUEUE *problem);
void remove_spaces(char *line);
void solve_expression(const char *filename);
int my_isdigit(int c);

#endif
