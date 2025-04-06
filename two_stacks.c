#include "two_stacks.h"

void stack_input_descending(STACK *stack) {
    char *line = NULL;
    size_t len = 0;
    int prev = 32767;

    puts("Стек №1. Вводите числа по убыванию.");
    puts("Введите значения (для окончания ввода введите пустую строку)");

    while (!stack_is_full(stack)) {
        printf("Значение №%d стека: ", stack->top + 1);

        if (getline(&line, &len, stdin) == -1) {
            puts("Ошибка ввода");
            free(line);
            exit(EXIT_FAILURE);
        }

        if (empty_line(line)) {
            break;
        }

        int number;
        if (check_int(&number, line)) {
            if (stack->top == 0 || number <= prev) {
                stack_push(stack, number);
                prev = number;
            } else {
                puts("Ошибка: число должно быть меньше или равно предыдущему!");
            }
        }
    }
    free(line);
}

void stack_input_ascending(STACK *stack) {
    char *line = NULL;
    size_t len = 0;
    int prev = -32767;

    puts("Стек №2. Вводите числа по возрастанию.");
    puts("Введите значения (для окончания ввода введите пустую строку)");

    while (!stack_is_full(stack)) {
        printf("Значение №%d стека: ", stack->top + 1);

        if (getline(&line, &len, stdin) == -1) {
            puts("Ошибка ввода");
            free(line);
            exit(EXIT_FAILURE);
        }

        if (empty_line(line)) {
            break;
        }

        int number;
        if (check_int(&number, line)) {
            if (stack->top == 0 || number >= prev) {
                stack_push(stack, number);
                prev = number;
            } else {
                puts("Ошибка: число должно быть больше или равно предыдущему!");
            }
        }
    }
    free(line);
}

void merge_stacks(STACK *asc, STACK *desc, STACK *result) {
    STACK temp_desc = *desc;
    STACK temp_asc = *asc;

    STACK reversed_asc;
    stack_create(&reversed_asc, temp_asc.capacity);
    while (!stack_is_empty(&temp_asc)) {
        stack_push(&reversed_asc, stack_pop(&temp_asc));
    }

    while (!stack_is_empty(&temp_desc) && !stack_is_empty(&reversed_asc)) {
        if (temp_desc.stack_queue[temp_desc.top - 1] > reversed_asc.stack_queue[reversed_asc.top - 1]) {
            stack_push(result, stack_pop(&temp_desc));
        } else {
            stack_push(result, stack_pop(&reversed_asc));
        }
    }

    while (!stack_is_empty(&temp_desc)) {
        stack_push(result, stack_pop(&temp_desc));
    }
    while (!stack_is_empty(&reversed_asc)) {
        stack_push(result, stack_pop(&reversed_asc));
    }
}

void two_stacks_task() {
    STACK stack_asc, stack_desc, result_stack;
    char *line = NULL;
    size_t len = 0;
    int capacity_asc, capacity_desc;

    puts("Второе задание");

    do {
        puts("Введите максимальный размер стека №1:");
        if (getline(&line, &len, stdin) == -1) {
            puts("Ошибка ввода");
            free(line);
            exit(EXIT_FAILURE);
        }
    } while (!check_int(&capacity_desc, line) || capacity_desc <= 0);
    free(line);
    line = NULL;

    do {
        puts("Введите максимальный размер стека №2:");
        if (getline(&line, &len, stdin) == -1) {
            puts("Ошибка ввода");
            free(line);
            exit(EXIT_FAILURE);
        }
    } while (!check_int(&capacity_asc, line) || capacity_asc <= 0);
    free(line);
    line = NULL;

    stack_create(&stack_desc, capacity_desc);
    stack_create(&stack_asc, capacity_asc);
    stack_create(&result_stack, capacity_asc + capacity_desc);

    stack_input_descending(&stack_desc);
    stack_input_ascending(&stack_asc);

    merge_stacks(&stack_desc, &stack_asc, &result_stack);

    puts("\nСтек по убыванию:");
    print_stack(&stack_desc);

    puts("\nСтек по возрастанию:");
    print_stack(&stack_asc);

    puts("\nРезультирующий стек по убыванию:");
    print_stack(&result_stack);

    free(stack_desc.stack_queue);
    free(stack_asc.stack_queue);
    free(result_stack.stack_queue);
}
