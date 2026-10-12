#include <stdio.h>
#include <stdlib.h>

#define V 100

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

Node *adj[V];
void initList(Node *adj[]) {
    for (int i = 0; i < V; i++) {
        adj[i] = NULL;
    }
}
Node *createNode(int vertex) {
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->vertex = vertex;
    newNode->next = NULL;

    return newNode;
}
int hasListEdge(Node *adj[], int u, int v, int *comparisons) {
     if (u < 0 || u >= V ||
        v < 0 || v >= V || u == v) {
        return 0;
    }

    Node *current = adj[u];

    while (current != NULL) {
        (*comparisons)++;

        if (current->vertex == v) {
            return 1;
        }

        current = current->next;
    }
    return 0;
}
void addListEdge(Node *adj[], int u, int v,int *comparisons) {
     if (u < 0 || u >= V ||
        v < 0 || v >= V || u == v) {
        return;
    }
    if(hasListEdge(adj,u,v,comparisons))
     return;

    Node *newNode = createNode(v);
    newNode->next = adj[u];
    adj[u] = newNode;

    newNode = createNode(u);
    newNode->next = adj[v];
    adj[v] = newNode;
}



int removeFromList(Node *adj[], int u, int v,
                   int *comparisons) {
     if (u < 0 || u >= V ||
        v < 0 || v >= V || u == v) {
        return 0;
    }
    Node *current = adj[u];
    Node *previous = NULL;

    while (current != NULL) {
        (*comparisons)++;

        if (current->vertex == v) {
            if (previous == NULL) {
                adj[u] = current->next;
            } else {
                previous->next = current->next;
            }

            free(current);
            return 1;
        }

        previous = current;
        current = current->next;
    }

    return 0;
}

void deleteListEdge(Node *adj[], int u, int v,
                    int *comparisons) {
                         if (u < 0 || u >= V ||
        v < 0 || v >= V || u == v) {
        return;
    }

    removeFromList(adj, u, v, comparisons);
    removeFromList(adj, v, u, comparisons);
}

void printListNeighbors(Node *adj[], int u,
                        int *comparisons) {
    if (u < 0 || u >= V) {
    return;
}
    Node *current = adj[u];

    printf("Neighbors of %d: ", u);

    while (current != NULL) {
        printf("%d ", current->vertex);
        (*comparisons)++;
        current = current->next;
    }

    printf("\n");
}

void freeList(Node *adj[]) {
    for (int i = 0; i < V; i++) {
        Node *current = adj[i];

        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }

        adj[i] = NULL;
    }
}