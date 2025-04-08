//
// Created by qr1tioo on 29.03.2025.
//

#ifndef LAB11_STACK_H
#define LAB11_STACK_H

#endif //LAB11_STACK_H
struct stack{
    int n;
    struct stack *next;
};

typedef struct {
    double *data;
    int top;
    int capacity;
} NumStack;

typedef struct {
    char *data;
    int top;
    int capacity;
} OpStack;