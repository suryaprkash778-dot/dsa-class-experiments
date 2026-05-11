#include <stdio.h>

// Function to perform Binary Search
int binarySearch(int arr[], int n, int key) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            return mid; // Key found
        }
        else if (arr[mid] > key) {
            right = mid - 1; // Search left half
        }
        else {
            left = mid + 1; // Search right half
        }
    }
    return -1; // Key not found
}

// Recursive Binary Search Function
int binarySearchRecursive(int arr[], int left, int right, int key) {
    if (left > right) {
        return -1; // Base case: key not found
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == key) {
        return mid; // Key found
    }
    else if (arr[mid] > key) {
        return binarySearchRecursive(arr, left, mid - 1, key); // Search left half
    }
    else {
        return binarySearchRecursive(arr, mid + 1, right, key); // Search right half
    }
}

int main() {
    int n, key;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter sorted elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter key to search: ");
    scanf("%d", &key);

    int result = binarySearch(arr, n, key);

    if (result != -1)
        printf("Key %d found at position %d\n", key, result + 1); // +1 for 1-based index
    else
        printf("Key %d not found in the array\n", key);

    return 0;
}
