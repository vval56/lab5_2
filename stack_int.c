#include "stack_int.h"

int check_int(int *number, char *line) {
    if (line == NULL || line[0] == '\n') {
        return 0;
    }

    int i = 0, sign = 1;
    *number = 0;

    if (line[i] == '-') {
        sign = -1;
        i++;
    }

    while (line[i] != '\0' && line[i] != '\n') {
        if (line[i] < '0' || line[i] > '9') {
            puts("Неверный ввод: допускаются только цифры");
            return 0;
        }
        *number = (*number * 10) + (line[i] - '0');
        i++;
    }

    *number *= sign;
    return 1;
}

int empty_line(char *line) {
    return (line == NULL || line[0] == '\n');
}

int stack_is_full(STACK *stack) {
    return (stack->top == stack->capacity);
}

int stack_is_empty(STACK *stack) {
    return (stack->top == 0);
}

void stack_create(STACK *stack, int new_capacity) {
    stack->capacity = new_capacity;
    stack->stack_queue = (int*)malloc(sizeof(int) * stack->capacity);
    stack->top = 0;
}

void stack_push(STACK *stack, int number) {
    if (!stack_is_full(stack)) {
        stack->stack_queue[stack->top++] = number;
    } else {
        puts("Стек переполнен");
    }
}

int stack_pop(STACK *stack) {
    if (!stack_is_empty(stack)) {
        return stack->stack_queue[--stack->top];
    } else {
        puts("Стек пуст");
        return 0;
    }
}

int stack_peek(STACK *stack) {
    if (!stack_is_empty(stack)) {
        return stack->stack_queue[stack->top - 1];
    } else {
        puts("Стек пуст");
        return 0;
    }
}

void stack_input(STACK *stack) {
    char *line = NULL;
    size_t len = 0;
    int read;

    puts("Введите значения (для окончания ввода введите пустую строку)");

    while (!stack_is_full(stack)) {
        printf("Значение №%d стека: ", stack->top + 1);

        read = getline(&line, &len, stdin);
        if (read == -1) {
            puts("Ошибка ввода");
            free(line);
            return;
        }

        if (empty_line(line)) {
            break;
        }

        int number;
        if (check_int(&number, line)) {
            stack_push(stack, number);
        }
    }

    free(line);
}

void find_sum_after_max(STACK *stack, GARBAGE *garbage) {
    if (stack_is_empty(stack)) {
        puts("Стек пуст! Сначала заполните его.");
        stack_input(stack);
        if (stack_is_empty(stack)) return;
    }

    int max = stack_peek(stack);
    while (!stack_is_empty(stack)) {
        int val = stack_pop(stack);
        garbage->array[garbage->size++] = val;
        if (val > max) {
            max = val;
        }
    }

    int sum = 0, max_found = 1, i = 0;

    while (i != garbage->size) {
        int val = garbage->array[i++];
        stack_push(stack, val);

        if (!max_found) {
            sum += val;
        }

        if (val == max) {
            max_found = 0;
        }
    }

    printf("Сумма элементов после максимального (%d): %d\n", max, sum);
}

void print_stack(STACK * stack){
    puts("Ваш стэк");

    for(int i = stack->top - 1; i >= 0; i--){
        printf("%d\n", stack->stack_queue[i]);
    }
}

void stack_int() {
    STACK stack;
    GARBAGE garbage;
    char *line = NULL;
    size_t len = 0;
    int capacity;

    puts("Задание №1");

    do {
        puts("Введите максимальный размер стека:");
        if (getline(&line, &len, stdin) == -1) {
            puts("Ошибка ввода");
            free(line);
            return;
        }
    } while (!check_int(&capacity, line) || capacity <= 0);

    free(line);

    stack_create(&stack, capacity);
    garbage.size = 0;
    garbage.array = (int*)calloc(capacity, sizeof(int));

    stack_input(&stack);

    find_sum_after_max(&stack, &garbage);

    //print_stack(&stack);

    free(stack.stack_queue);
    free(garbage.array);
}
