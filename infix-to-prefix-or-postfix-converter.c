#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char x) {
    stack[++top] = x;
}

char pop() {
    if (top == -1)
        return -1;
    else
        return stack[top--];
}

int priority(char x) {
    if (x == '(')
        return 0;
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/' || x == '%')
        return 2;
    return 0;
}

void infixToPostfix(char exp[]) {
    char *e, x;
    e = exp;

    while (*e != '\0') {
        if (isalnum(*e))
            printf("%c", *e);
        else if (*e == '(')
            push(*e);
        else if (*e == ')') {
            while ((x = pop()) != '(')
                printf("%c", x);
        } else {
            while (priority(stack[top]) >= priority(*e))
                printf("%c", pop());
            push(*e);
        }
        e++;
    }

    while (top != -1) {
        printf("%c", pop());
    }
}

void reverse(char exp[]) {
    int i, j;
    char temp;
    int len = strlen(exp);

    for (i = 0, j = len - 1; i < j; i++, j--) {
        temp = exp[i];
        exp[i] = exp[j];
        exp[j] = temp;
    }
}

void swapBrackets(char exp[]) {
    for (int i = 0; exp[i]; i++) {
        if (exp[i] == '(')
            exp[i] = ')';
        else if (exp[i] == ')')
            exp[i] = '(';
    }
}

void infixToPrefix(char exp[]) {
    reverse(exp);
    swapBrackets(exp);

    printf("\nPrefix Expression: ");
    infixToPostfix(exp);
}

int main() {
    char exp[MAX];

    printf("Enter Infix Expression: ");
    scanf("%s", exp);

    printf("\nPostfix Expression: ");
    infixToPostfix(exp);

    strcpy(exp, exp);
    infixToPrefix(exp);

    return 0;
}