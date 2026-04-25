#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int heap[MAX];
int size = 0;

// Swap utility
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify (Max Heap)
void heapify(int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < size && heap[left] > heap[largest])
        largest = left;
    if (right < size && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapify(largest);
    }
}

// Insert into heap
void insert(int key) {
    if (size == MAX) {
        printf("Heap overflow!\n");
        return;
    }
    heap[size] = key;
    int i = size;
    size++;

    // Fix heap property
    while (i != 0 && heap[(i-1)/2] < heap[i]) {
        swap(&heap[i], &heap[(i-1)/2]);
        i = (i-1)/2;
    }
}

// Peek (Max element)
int peek() {
    if (size == 0) {
        printf("Heap is empty!\n");
        return -1;
    }
    return heap[0];
}

// Extract Max
int extractMax() {
    if (size <= 0) return -1;
    if (size == 1) {
        size--;
        return heap[0];
    }

    int root = heap[0];
    heap[0] = heap[size-1];
    size--;
    heapify(0);

    return root;
}

// Delete element at index
void deleteKey(int i) {
    if (i >= size) return;
    heap[i] = heap[0] + 1; // increase value beyond root
    while (i != 0 && heap[(i-1)/2] < heap[i]) {
        swap(&heap[i], &heap[(i-1)/2]);
        i = (i-1)/2;
    }
    extractMax();
}

// Display heap
void display() {
    for (int i = 0; i < size; i++)
        printf("%d ", heap[i]);
    printf("\n");
}

// Driver code
int main() {
    insert(20);
    insert(15);
    insert(30);
    insert(40);
    insert(10);

    printf("Heap elements: ");
    display();

    printf("Peek (Max): %d\n", peek());

    printf("Extracted Max: %d\n", extractMax());
    printf("Heap after extraction: ");
    display();

    deleteKey(1);
    printf("Heap after deletion: ");
    display();

    return 0;
}
