//
// Created by qr1tiooo on 29.03.2025.
//

#include "functions.h"

void setNumber(int* number)
{
    int isInvalid = 0;
    do {
        isInvalid = 0;
        int i = 0;
        *number = 0;
        char digits[10];
        scanf("%s", digits);
        int negative = 1;
        if(digits[0] == '-'){negative = -1;i++;}
        do {
            if (digits[i] < '0' || digits[i] > '9') {
                printf("Enter a valid number\n");
                isInvalid = 1;
                while(getchar()!='\n');
                break;
            }
            else {*number = *number * 10 + digits[i] - '0'; }
        } while(digits[++i] != 0);
        *number *= negative;
    }while(isInvalid == 1);
    rewind(stdin);
}

struct stack* push(struct stack *top, int n){
    struct stack *ptr = malloc(sizeof(struct stack));
    ptr->n = n;
    ptr->next = top;
    return ptr;
}
struct stack* pop(struct stack* top){
    if(top == NULL)
        return top;
    struct stack* ptr_next = top->next;
    free(top);
    return ptr_next;
}

struct stack* fillStack(){
    printf("Enter size of stack\n");
    int size ;
    setNumber(&size);
    struct stack *top = NULL;
    printf("Enter elements of stack\n");
    while(size != 0){
        int temp;
        setNumber(&temp);
        top = push(top, temp);
        size--;
    }
    return top;
}
void show(const struct stack* top){
    const struct stack* curr = top;
    printf("Content of stack:\n");
    while(curr != NULL){
        printf("%d\n", curr->n);
        curr = curr->next;
    }
}

int countOfElement(struct stack *s, int num) {
    int count = 0;
    while (s != NULL) {
        if (s->n == num)
            count++;
        s = s->next;
    }
    return count;
}
void showCommonElements(struct stack *s1, struct stack *s2) {
    printf("Elements from stack2 that appear in stack1 more than 2 times:\n");
    while (s2 != NULL) {
        int current = s2->n;
        if (countOfElement(s1, current) > 2) {
            printf("%d ", current);
        }
        s2 = s2->next;
    }
    printf("\n");
}

struct stack* fillStackUp(){
    printf("Enter size of ascending stack:\n");
    int size;
    setNumber(&size);
    if (size <= 0) return NULL;

    printf("Enter elements in ASCENDING order:\n");
    int prev = INT_MIN, current;
    struct stack *top = NULL;

    for (int i = 0; i < size; i++) {
        setNumber(&current);
        while (current <= prev) {
            printf("Error: Input must be in STRICT ASCENDING order!\n");
            pop(top);
            setNumber(&current);
        }
        top = push(top, current);
        prev = current;
    }
    return top;
}
int getBottom(struct stack *s) {
    if (s == NULL) {
        return INT_MIN;
    }
    while (s->next != NULL) {
        s = s->next;
    }
    return s->n;
}

struct stack* fillStackDown(){
    printf("Enter size of descending stack:\n");
    int size;
    setNumber(&size);
    if (size <= 0) return NULL;

    printf("Enter elements in DESCENDING order:\n");
    int prev = INT_MAX, current;
    struct stack *top = NULL;

    for (int i = 0; i < size; i++) {
        setNumber(&current);
        while (current >= prev) {
            printf("Error: Input must be in STRICT DESCENDING order!\n");
            pop(top);
            setNumber(&current);
        }
        top = push(top, current);
        prev = current;
    }
    return top;
}
struct stack* mergeStacksDescending(struct stack *s1, struct stack *s2) {
    struct stack *result = NULL;

    while (1) {
        int val1 = 0;
        if (s1 != NULL) {
            val1 = getBottom(s1);
        }
        int val2 = 0;
        if (s2 != NULL) {
            val2 = s2->n;
        }

        if (s1 == NULL && s2 == NULL) {
            break;
        }

        if (val1 >= val2) {
            struct stack *prev = NULL;
            struct stack *curr = s1;
            while (curr->next != NULL) {
                prev = curr;
                curr = curr->next;
            }

            result = push(result, curr->n);

            if (prev != NULL) {
                prev->next = NULL;
            } else {
                s1 = NULL;
            }
            free(curr);
        } else {
            result = push(result, s2->n);
            s2 = pop(s2);
        }
    }
    return result;
}

void initNumStack(NumStack *s, int capacity) {
    s->data = (double*)malloc(capacity * sizeof(double));
    s->top = -1;
    s->capacity = capacity;
}


void initOpStack(OpStack *s, int capacity) {
    s->data = (char*)malloc(capacity * sizeof(char));
    s->top = -1;
    s->capacity = capacity;
}

int isNumStackEmpty(NumStack *s) {
    return s->top == -1;
}

int isOpStackEmpty(OpStack *s) {
    return s->top == -1;
}

void pushNum(NumStack *s, double value) {
    if (s->top == s->capacity - 1) {
        s->capacity *= 2;
        s->data = (double*)realloc(s->data, s->capacity * sizeof(double));
    }
    s->data[++s->top] = value;
}

void pushOp(OpStack *s, char op) {
    if (s->top == s->capacity - 1) {
        s->capacity *= 2;
        s->data = (char*)realloc(s->data, s->capacity * sizeof(char));
    }
    s->data[++s->top] = op;
}


double popNum(NumStack *s) {
    if (isNumStackEmpty(s)) return NAN;
    return s->data[s->top--];
}


char popOp(OpStack *s) {
    if (isOpStackEmpty(s)) return '\0';
    return s->data[s->top--];
}

char peekOp(OpStack *s) {
    if (isOpStackEmpty(s)) return '\0';
    return s->data[s->top];
}

int precedence(char op) {
    switch(op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
    }
}

double applyOp(double a, double b, char op, int *error) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0.0) {
                *error = 1;
                return NAN;
            }
            return a / b;
        default: return NAN;
    }
}

int checkParentheses(const char *expr, int *error_pos) {
    int balance = 0;
    for (int i = 0; expr[i]; i++) {
        if (expr[i] == '(') balance++;
        else if (expr[i] == ')') {
            balance--;
            if (balance < 0) {
                *error_pos = i;
                return 0;
            }
        }
    }
    if (balance != 0) {
        *error_pos = (int)strlen(expr);
        return 0;
    }
    return 1;
}

int validateExpression(const char *expr, int *error_pos) {
    int len = (int)strlen(expr);
    if (len == 0) {
        *error_pos = 0;
        return 0;
    }

    if (!checkParentheses(expr, error_pos)) {
        return 0;
    }


    for (int i = 0; i < len; i++) {
        if (!isdigit(expr[i]) && expr[i] != '.' &&
            expr[i] != '+' && expr[i] != '-' && expr[i] != '*' && expr[i] != '/' &&
            expr[i] != '(' && expr[i] != ')' && expr[i] != ' ') {
            *error_pos = i;
            return 0;
        }
    }


    for (int i = 0; i < len - 1; i++) {
        if ((expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') &&
            (expr[i+1] == '+' || expr[i+1] == '-' || expr[i+1] == '*' || expr[i+1] == '/')) {
            *error_pos = i+1;
            return 0;
        }
    }

    return 1;
}

double evaluateExpression(const char *expr, int *error_pos, int *error) {
    NumStack numStack;
    OpStack opStack;
    initNumStack(&numStack, 16);
    initOpStack(&opStack, 16);

    int i = 0;
    while (expr[i]) {
        if (expr[i] == ' ') {
            i++;
            continue;
        }

        if (expr[i] == '(') {
            pushOp(&opStack, expr[i]);
            i++;
        }
        else if (expr[i] == ')') {
            while (!isOpStackEmpty(&opStack) && peekOp(&opStack) != '(') {
                double b = popNum(&numStack);
                double a = popNum(&numStack);
                char op = popOp(&opStack);
                pushNum(&numStack, applyOp(a, b, op, error));
                if (*error) {
                    *error_pos = i;
                    free(numStack.data);
                    free(opStack.data);
                    return NAN;
                }
            }
            popOp(&opStack);
            i++;
        }
        else if (isdigit(expr[i]) || expr[i] == '.') {
            char *end;
            double num = strtod(&expr[i], &end);
            pushNum(&numStack, num);
            i = end - expr;
        }
        else {
            while (!isOpStackEmpty(&opStack) && precedence(peekOp(&opStack)) >= precedence(expr[i])) {
                double b = popNum(&numStack);
                double a = popNum(&numStack);
                char op = popOp(&opStack);
                pushNum(&numStack, applyOp(a, b, op, error));
                if (*error) {
                    *error_pos = i;
                    free(numStack.data);
                    free(opStack.data);
                    return NAN;
                }
            }
            pushOp(&opStack, expr[i]);
            i++;
        }
    }

    while (!isOpStackEmpty(&opStack)) {
        double b = popNum(&numStack);
        double a = popNum(&numStack);
        char op = popOp(&opStack);
        pushNum(&numStack, applyOp(a, b, op, error));
        if (*error) {
            *error_pos = i;
            free(numStack.data);
            free(opStack.data);
            return NAN;
        }
    }

    double result = popNum(&numStack);
    free(numStack.data);
    free(opStack.data);
    return result;
}

