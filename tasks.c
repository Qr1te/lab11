//
// Created by qr1tiooo on 03.04.2025.
//

#include "tasks.h"
#include "functions.h"

void printCommon(){
    printf("Stack 1:\n");
    struct stack *stack1 = fillStack();
    printf("Stack 2:\n");
    struct stack *stack2 = fillStack();
    showCommonElements(stack1, stack2);
    puts("Press any key to return..."), _getch();
}
void merge(){
    struct stack *stack1 = fillStackDown();
    struct stack *stack2 = fillStackUp();

    printf("Stack 1 (descending):\n");
    show(stack1);
    printf("Stack 2 (ascending):\n");
    show(stack2);

    struct stack *stack3 = mergeStacksDescending(stack1, stack2);
    printf("Merged stack (descending):\n");
    show(stack3);
    puts("Press any key to return..."), _getch();
}
void calculator() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");


    char line[256];
    while (fgets(line, sizeof(line), input)) {
        line[strcspn(line, "\n")] = '\0';

        int error_pos = 0;
        if (!validateExpression(line, &error_pos)) {
            fprintf(output, "Error n position %d\n", error_pos + 1);
            continue;
        }

        int error = 0;
        double result = evaluateExpression(line, &error_pos, &error);

        if (error) {
            fprintf(output, "Error in position  %d\n", error_pos + 1);
        } else {
            fprintf(output, "%.2f\n", result);
        }
    }
    printf("Result in output.txt\n");
    puts("Press any key to return..."), _getch();
    fclose(input);
    fclose(output);

}
void menu(){

    int answer;
    do {
        system("cls");
        answer = 0;
        printf("Choose what u want to do\n");
        printf("1. show common elements of 2 stacks.\n2. merge 2 stacks\n3. calculator \n4.Exit.\n");

        while (answer < '1' || answer > '4') answer = _getch();
        if (answer == '1'){
            printCommon();
        }
        else if (answer == '2') {
            merge();
        }
        else if (answer == '3') {
            calculator();
        }
    } while (answer != '4');
}