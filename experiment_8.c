#include <stdio.h>
#include <stdlib.h>

#define MAX 20

// Adjacency Matrix
int adjMatrix[MAX][MAX];

// Adjacency List
struct Node {
    int vertex;
    struct Node* next;
};
struct Node* adjList[MAX];

// Queue for BFS
int queue[MAX], front = -1, rear = -1;

void enqueue(int v) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = v;
}
int dequeue() {
    if (front == -1) return -1;
    int v = queue[front++];
    if (front > rear) front = rear = -1;
    return v;
}

// Add edge to adjacency matrix
void addEdgeMatrix(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1; // for undirected graph
}

// Add edge to adjacency list
void addEdgeList(int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = u;
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

// DFS
void DFSUtil(int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", v);

    for (struct Node* temp = adjList[v]; temp != NULL; temp = temp->next) {
        if (!visited[temp->vertex]) {
            DFSUtil(temp->vertex, visited);
        }
    }
}

// BFS
void BFS(int start, int n) {
    int visited[MAX] = {0};
    enqueue(start);
    visited[start] = 1;

    while (front != -1) {
        int v = dequeue();
        printf("%d ", v);

        for (struct Node* temp = adjList[v]; temp != NULL; temp = temp->next) {
            if (!visited[temp->vertex]) {
                enqueue(temp->vertex);
                visited[temp->vertex] = 1;
            }
        }
    }
}

int main() {
    int n, e, u, v, source;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adjMatrix[i][j] = 0;

    // Initialize adjacency list
    for (int i = 0; i < n; i++)
        adjList[i] = NULL;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        addEdgeMatrix(u, v);
        addEdgeList(u, v);
    }

    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", adjMatrix[i][j]);
        printf("\n");
    }

    printf("\nAdjacency List:\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", i);
        struct Node* temp = adjList[i];
        while (temp) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }

    printf("\nEnter source vertex for traversal: ");
    scanf("%d", &source);

    int visited[MAX] = {0};
    printf("\nDFS Traversal: ");
    DFSUtil(source, visited);

    printf("\nBFS Traversal: ");
    BFS(source, n);

    return 0;
}
