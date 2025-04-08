//
// Created by qr1tiooo on 29.03.2025.
//

#ifndef LAB11_FUNCTIONS_H
#define LAB11_FUNCTIONS_H

#endif //LAB11_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"

void setNumber(int* number);
struct stack* push(struct stack *top, int n);
struct stack* fillStack();
void show(const struct stack* top);
struct stack* pop(struct stack* top);
int countOfElement(struct stack* s, int num);
void showCommonElements(struct stack *s1, struct stack *s2);
int getBottom(struct stack *s);
struct stack* fillStackUp();
struct stack* fillStackDown();
struct stack* mergeStacksDescending(struct stack *s1, struct stack *s2);
void initNumStack(NumStack *s, int capacity);
void initOpStack(OpStack *s, int capacity);
int isNumStackEmpty(NumStack *s);
void pushNum(NumStack *s, double value);
void pushOp(OpStack *s, char op);
double popNum(NumStack *s);
char popOp(OpStack *s);
char peekOp(OpStack *s);
int precedence(char op);
double applyOp(double a, double b, char op, int *error);
int checkParentheses(const char *expr, int *error_pos);
int validateExpression(const char *expr, int *error_pos);
double evaluateExpression(const char *expr, int *error_pos, int *error);
