#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack implementation
int stack[MAX], top = -1;

void push(int x) {
    stack[++top] = x;
}

int pop() {
    return stack[top--];
}

int main() {
    int N, K;
    int tickets[MAX], result[MAX];
    
    printf("Enter number of people (N): ");
    scanf("%d", &N);
    
    printf("Enter K (number to reverse): ");
    scanf("%d", &K);
    
    printf("Enter ticket numbers:\n");
    for (int i = 0; i < N; i++) {
        scanf("%d", &tickets[i]);
    }
    
    // Step 1: Push first K elements into stack
    for (int i = 0; i < K; i++) {
        push(tickets[i]);
    }
    
    // Step 2: Pop from stack to result (reverses order)
    int idx = 0;
    while (top != -1) {
        result[idx++] = pop();
    }
    
    // Step 3: Copy remaining elements as-is
    for (int i = K; i < N; i++) {
        result[idx++] = tickets[i];
    }
    
    // Final output
    printf("Reordered line:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    return 0;
}
