#include <stdio.h>
#include <ctype.h>   // for isdigit, isalpha
#include <string.h>  // for strlen
#include <stdlib.h>  // for exit

#define MAX 100

// Stack for operators
char stack[MAX];
int top = -1;

void push(char c) {
    if (top == MAX - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

char peek() {
    return stack[top];
}

int isEmpty() {
    return top == -1;
}

// Precedence function
int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

// Convert infix to postfix
void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    for (i = 0; i < strlen(infix); i++) {
        char c = infix[i];

        // If operand, add to postfix
        if (isalnum(c)) {
            postfix[k++] = c;
        }
        // If '(', push to stack
        else if (c == '(') {
            push(c);
        }
        // If ')', pop until '('
        else if (c == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[k++] = pop();
            }
            pop(); // remove '('
        }
        // If operator
        else {
            while (!isEmpty() && precedence(peek()) >= precedence(c)) {
                postfix[k++] = pop();
            }
            push(c);
        }
    }

    // Pop remaining operators
    while (!isEmpty()) {
        postfix[k++] = pop();
    }
    postfix[k] = '\0';
}

// Stack for evaluation
int evalStack[MAX];
int evalTop = -1;

void evalPush(int val) {
    evalStack[++evalTop] = val;
}

int evalPop() {
    return evalStack[evalTop--];
}

// Evaluate postfix expression
int evaluatePostfix(char postfix[]) {
    int i;
    for (i = 0; i < strlen(postfix); i++) {
        char c = postfix[i];

        if (isdigit(c)) {
            evalPush(c - '0'); // convert char to int
        } else {
            int val2 = evalPop();
            int val1 = evalPop();
            switch (c) {
                case '+': evalPush(val1 + val2); break;
                case '-': evalPush(val1 - val2); break;
                case '*': evalPush(val1 * val2); break;
                case '/': evalPush(val1 / val2); break;
                case '^': {
                    int res = 1;
                    for (int j = 0; j < val2; j++) res *= val1;
                    evalPush(res);
                    break;
                }
            }
        }
    }
    return evalPop();
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression (operands single letters or digits): ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    // Only works if operands are digits (e.g., 5+6*2)
    int result = evaluatePostfix(postfix);
    printf("Evaluation result: %d\n", result);

    return 0;
}
