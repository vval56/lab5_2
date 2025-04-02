#include "arithmetic_expression.h"

int my_strlen(const char *str) {
    int length = 0;

    if (str == NULL) {
        fprintf(stderr, "Ошибка: NULL pointer передан в my_strlen\n");
        exit(EXIT_FAILURE);
    }

    while (*str != '\0') {
        length++;
        str++;
    }

    return length;
}

int my_isdigit(int c) {
    return (c >= '0' && c <= '9');
}

int char_stack_is_full(STACK_CHAR *stack) {
    return (stack->top == stack->capacity);
}

int char_stack_is_empty(STACK_CHAR *stack) {
    return (stack->top == 0);
}

void char_stack_create(STACK_CHAR *stack, int new_capacity) {
    stack->capacity = new_capacity;
    stack->queue = (char*)malloc(sizeof(char) * stack->capacity);
    stack->top = 0;
}

void char_stack_push(STACK_CHAR *stack, char operand) {
    if (!char_stack_is_full(stack)) {
        stack->queue[stack->top++] = operand;
    } else {
        puts("Стек переполнен");
        exit(1);
    }
}

char char_stack_pop(STACK_CHAR *stack) {
    if (!char_stack_is_empty(stack)) {
        return stack->queue[--stack->top];
    } else {
        puts("Стек пуст");
        exit(1);
    }
}

char char_stack_peek(STACK_CHAR *stack) {
    if (!char_stack_is_empty(stack)) {
        return stack->queue[stack->top - 1];
    } else {
        puts("Стек пуст");
        exit(1);
    }
}

int double_stack_is_full(DOUBLE_STACK *stack) {
    return (stack->top == stack->capacity);
}

int double_stack_is_empty(DOUBLE_STACK *stack) {
    return (stack->top == 0);
}

void double_stack_create(DOUBLE_STACK *stack, int new_capacity) {
    stack->capacity = new_capacity;
    stack->queue = (double*)malloc(sizeof(double) * stack->capacity);
    stack->top = 0;
}

void double_stack_push(DOUBLE_STACK *stack, double num) {
    if (!double_stack_is_full(stack)) {
        stack->queue[stack->top++] = num;
    } else {
        puts("Стек переполнен");
        exit(1);
    }
}

double double_stack_pop(DOUBLE_STACK *stack) {
    if (!double_stack_is_empty(stack)) {
        return stack->queue[--stack->top];
    } else {
        puts("Стек пуст");
        exit(1);
    }
}

void error_in_file(int value) {
    FILE *file = fopen("error_expression.txt", "wt");
    if (file) {
        fprintf(file, "Ошибка на позиции: %d", value);
        fclose(file);
    }
}

int priority(char op) {
    switch(op) {
        case '^': return 4;
        case '*':
        case '/': return 3;
        case '+':
        case '-': return 2;
        default: return 0;
    }
}

double calculate(double num1, double num2, char op) {
    switch(op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/':
            if (num2 == 0) {
                puts("Деление на ноль!");
                exit(1);
            }
            return num1 / num2;
    }
}

void infix_to_postfix(QUEUE *problem, const char *line, STACK_CHAR *stack) {
    int i = 0, pos = 0;
    char_stack_create(stack, 100);

    while (line[i] != '\0') {
        if (line[i] == ' ') {
            i++;
            continue;
        }

        if (my_isdigit(line[i]) || (line[i] == '-' && (i == 0 || line[i-1] == '('))) {
            if (line[i] == '-') {
                problem->expression[pos++] = line[i++];
            }
            while (my_isdigit(line[i]) || line[i] == '.') {
                problem->expression[pos++] = line[i++];
            }
            problem->expression[pos++] = ' ';
            continue;
        }

        if (line[i] == '(') {
            char_stack_push(stack, line[i]);
        }
        else if (line[i] == ')') {
            while (!char_stack_is_empty(stack) && char_stack_peek(stack) != '(') {
                problem->expression[pos++] = char_stack_pop(stack);
                problem->expression[pos++] = ' ';
            }
            if (!char_stack_is_empty(stack)) {
                char_stack_pop(stack);
            }
        }
        else if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/' || line[i] == '^') {
            while (!char_stack_is_empty(stack) &&
                   priority(char_stack_peek(stack)) >= priority(line[i])) {
                problem->expression[pos++] = char_stack_pop(stack);
                problem->expression[pos++] = ' ';
            }
            char_stack_push(stack, line[i]);
        }
        i++;
    }

    while (!char_stack_is_empty(stack)) {
        problem->expression[pos++] = char_stack_pop(stack);
        problem->expression[pos++] = ' ';
    }

    problem->expression[pos] = '\0';
}

double evaluate_postfix(QUEUE *problem) {
    DOUBLE_STACK nums;
    double_stack_create(&nums, 100);
    int i = 0;

    while (problem->expression[i] != '\0') {
        if (problem->expression[i] == ' ') {
            i++;
            continue;
        }

        if (my_isdigit(problem->expression[i]) ||
            (problem->expression[i] == '-' && my_isdigit(problem->expression[i+1]))) {
            char num_str[50];
            int j = 0;

            if (problem->expression[i] == '-') {
                num_str[j++] = problem->expression[i++];
            }

            while (my_isdigit(problem->expression[i]) || problem->expression[i] == '.') {
                num_str[j++] = problem->expression[i++];
            }
            num_str[j] = '\0';

            double num = atof(num_str);
            double_stack_push(&nums, num);
            continue;
        }

        if (problem->expression[i] == '+' || problem->expression[i] == '-' ||
            problem->expression[i] == '*' || problem->expression[i] == '/' ||
            problem->expression[i] == '^') {
            double b = double_stack_pop(&nums);
            double a = double_stack_pop(&nums);
            double_stack_push(&nums, calculate(a, b, problem->expression[i]));
        }
        i++;
    }

    double result = double_stack_pop(&nums);
    free(nums.queue);
    return result;
}

void remove_spaces(char *line) {
    int i = 0, j = 0;
    while (line[i]) {
        if (line[i] != ' ') {
            line[j++] = line[i];
        }
        i++;
    }
    line[j] = '\0';
}

void validate_expression(const char *line, const char *filename) {
    int i = 0;
    int paren_count = 0;

    while (line[i] != '\0') {
        if (!my_isdigit(line[i]) && line[i] != '+' && line[i] != '-' &&
            line[i] != '*' && line[i] != '/' && line[i] != '^' &&
            line[i] != '(' && line[i] != ')' && line[i] != '.' && line[i] != ' ') {
            printf("Недопустимый символ: %c\n", line[i]);
            error_in_file(i);
            exit(1);
        }

        if (line[i] == '(') paren_count++;
        if (line[i] == ')') paren_count--;

        if (paren_count < 0) {
            puts("Несбалансированные скобки");
            error_in_file(i);
            exit(1);
        }

        i++;
    }

    if (paren_count != 0) {
        puts("Несбалансированные скобки");
        exit(1);
    }
}

void solve_expression(const char *filename) {
    FILE *file = fopen(filename, "rt");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, file);
    fclose(file);

    if (read <= 1) {
        puts("Файл пуст");
        free(line);
        exit(1);
    }

    if (line[read-1] == '\n') {
        line[read-1] = '\0';
    }

    remove_spaces(line);
    validate_expression(line, filename);

    STACK_CHAR op_stack;
    QUEUE problem;
    problem.size = my_strlen(line) * 2;
    problem.expression = (char*)malloc(problem.size);

    infix_to_postfix(&problem, line, &op_stack);
    double result = evaluate_postfix(&problem);

    FILE *out = fopen("answer.txt", "wt");
    if (out) {
        fprintf(out, "Результат: %.2lf\n", result);
        fclose(out);
    }

    free(line);
    free(problem.expression);
    free(op_stack.queue);
}
