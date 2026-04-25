#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// -------------------- LINEAR PROBING --------------------
int hashLinear(int key) {
    return key % TABLE_SIZE;
}

void insertLinear(int table[], int key) {
    int index = hashLinear(key);
    int i = 0;
    while (table[(index + i) % TABLE_SIZE] != -1) {
        i++;
    }
    table[(index + i) % TABLE_SIZE] = key;
}

int searchLinear(int table[], int key) {
    int index = hashLinear(key);
    int i = 0;
    while (table[(index + i) % TABLE_SIZE] != -1) {
        if (table[(index + i) % TABLE_SIZE] == key)
            return (index + i) % TABLE_SIZE;
        i++;
    }
    return -1;
}

void deleteLinear(int table[], int key) {
    int pos = searchLinear(table, key);
    if (pos != -1) table[pos] = -1;
}

// -------------------- QUADRATIC PROBING --------------------
int hashQuadratic(int key) {
    return key % TABLE_SIZE;
}

void insertQuadratic(int table[], int key) {
    int index = hashQuadratic(key);
    int i = 0;
    while (table[(index + i*i) % TABLE_SIZE] != -1) {
        i++;
    }
    table[(index + i*i) % TABLE_SIZE] = key;
}

int searchQuadratic(int table[], int key) {
    int index = hashQuadratic(key);
    int i = 0;
    while (table[(index + i*i) % TABLE_SIZE] != -1) {
        if (table[(index + i*i) % TABLE_SIZE] == key)
            return (index + i*i) % TABLE_SIZE;
        i++;
    }
    return -1;
}

void deleteQuadratic(int table[], int key) {
    int pos = searchQuadratic(table, key);
    if (pos != -1) table[pos] = -1;
}

// -------------------- DOUBLE HASHING --------------------
int hash1(int key) {
    return key % TABLE_SIZE;
}
int hash2(int key) {
    return 7 - (key % 7); // secondary hash
}

void insertDouble(int table[], int key) {
    int index = hash1(key);
    int step = hash2(key);
    int i = 0;
    while (table[(index + i*step) % TABLE_SIZE] != -1) {
        i++;
    }
    table[(index + i*step) % TABLE_SIZE] = key;
}

int searchDouble(int table[], int key) {
    int index = hash1(key);
    int step = hash2(key);
    int i = 0;
    while (table[(index + i*step) % TABLE_SIZE] != -1) {
        if (table[(index + i*step) % TABLE_SIZE] == key)
            return (index + i*step) % TABLE_SIZE;
        i++;
    }
    return -1;
}

void deleteDouble(int table[], int key) {
    int pos = searchDouble(table, key);
    if (pos != -1) table[pos] = -1;
}

// -------------------- SEPARATE CHAINING --------------------
struct Node {
    int key;
    struct Node* next;
};

struct Node* chain[TABLE_SIZE];

int hashChain(int key) {
    return key % TABLE_SIZE;
}

void insertChain(int key) {
    int index = hashChain(key);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->next = chain[index];
    chain[index] = newNode;
}

int searchChain(int key) {
    int index = hashChain(key);
    struct Node* temp = chain[index];
    while (temp) {
        if (temp->key == key) return index;
        temp = temp->next;
    }
    return -1;
}

void deleteChain(int key) {
    int index = hashChain(key);
    struct Node* temp = chain[index];
    struct Node* prev = NULL;
    while (temp) {
        if (temp->key == key) {
            if (prev) prev->next = temp->next;
            else chain[index] = temp->next;
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

// -------------------- DISPLAY --------------------
void displayTable(int table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != -1)
            printf("%d ", table[i]);
        else
            printf("NULL ");
    }
    printf("\n");
}

void displayChain() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d -> ", i);
        struct Node* temp = chain[i];
        while (temp) {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// -------------------- MAIN --------------------
int main() {
    int linear[TABLE_SIZE], quadratic[TABLE_SIZE], doubleHash[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        linear[i] = quadratic[i] = doubleHash[i] = -1;
        chain[i] = NULL;
    }

    // Example insertions
    insertLinear(linear, 15);
    insertLinear(linear, 25);
    insertLinear(linear, 35);

    insertQuadratic(quadratic, 15);
    insertQuadratic(quadratic, 25);
    insertQuadratic(quadratic, 35);

    insertDouble(doubleHash, 15);
    insertDouble(doubleHash, 25);
    insertDouble(doubleHash, 35);

    insertChain(15);
    insertChain(25);
    insertChain(35);

    printf("\nLinear Probing Table:\n");
    displayTable(linear);

    printf("\nQuadratic Probing Table:\n");
    displayTable(quadratic);

    printf("\nDouble Hashing Table:\n");
    displayTable(doubleHash);

    printf("\nSeparate Chaining Table:\n");
    displayChain();

    return 0;
}
