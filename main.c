#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

#define V 100

typedef struct {
    int u;
    int v;
} Edge;

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

/* Functions from graph.c */
void generateEdges(Edge edges[], int edgeCount);

/* Functions from matrix.c */
void initMatrix(int matrix[V][V]);
void addMatrixEdge(int matrix[V][V], int u, int v,
                   int *comparisons);
void deleteMatrixEdge(int matrix[V][V], int u, int v,
                      int *comparisons);
int hasMatrixEdge(int matrix[V][V], int u, int v,
                  int *comparisons);
void printMatrixNeighbors(int matrix[V][V], int u,
                          int *comparisons);

/* Functions from list.c */
void initList(Node *adj[]);
void addListEdge(Node *adj[], int u, int v,
                 int *comparisons);
void deleteListEdge(Node *adj[], int u, int v,
                    int *comparisons);
int hasListEdge(Node *adj[], int u, int v,
                int *comparisons);
void printListNeighbors(Node *adj[], int u,
                        int *comparisons);
void freeList(Node *adj[]);

/* Function from measure.c */
void printCaseReport(
    int caseNumber,
    const char *graphType,
    const char *representation,
    size_t memoryBytes,
    int insertComparisons,
    int deleteComparisons,
    int connectivityComparisons,
    int adjacentComparisons
);

void runGraphCase(Edge edges[], int edgeCount,
                  const char *graphType,
                  int firstCaseNumber) {

    int matrix[V][V];
    Node *adj[V];

    /* Initialize both representations */
    initMatrix(matrix);
    initList(adj);

    /* Comparison counters */
    int matrixInsert = 0;
    int listInsert = 0;

    int matrixDelete = 0;
    int listDelete = 0;

    int matrixConnectivity = 0;
    int listConnectivity = 0;

    int matrixAdjacent = 0;
    int listAdjacent = 0;

    /* 1. Insert the same edges into Matrix and List */
    for (int i = 0; i < edgeCount; i++) {
        addMatrixEdge(matrix, edges[i].u, edges[i].v,
                      &matrixInsert);

        addListEdge(adj, edges[i].u, edges[i].v,
                    &listInsert);
    }

    /* 2. Check whether the first edge exists */
    int u = edges[0].u;
    int v = edges[0].v;

    int matrixFound = hasMatrixEdge(
        matrix, u, v, &matrixConnectivity
    );

    int listFound = hasListEdge(
        adj, u, v, &listConnectivity
    );

    printf("\n%s graph: %d vertices, %d edges\n",
           graphType, V, edgeCount);

    printf("Matrix found edge: %d\n", matrixFound);
    printf("List found edge: %d\n", listFound);

    /* 3. Traverse the neighbors of vertex 0 */
    printMatrixNeighbors(matrix, 0, &matrixAdjacent);
    printListNeighbors(adj, 0, &listAdjacent);
/* 4. Measure memory before deletion */
size_t matrixMemory = sizeof(matrix);

size_t listMemory =
    sizeof(adj) + (size_t)(2 * edgeCount) * sizeof(Node);

/* 5. Delete the same existing edge from both */
deleteMatrixEdge(matrix, u, v, &matrixDelete);
deleteListEdge(adj, u, v, &listDelete);

    /* 6. Print Matrix report */
    printCaseReport(
        firstCaseNumber,
        graphType,
        "Matrix",
        matrixMemory,
        matrixInsert,
        matrixDelete,
        matrixConnectivity,
        matrixAdjacent
    );

    /* 7. Print List report */
    printCaseReport(
        firstCaseNumber + 1,
        graphType,
        "List",
        listMemory,
        listInsert,
        listDelete,
        listConnectivity,
        listAdjacent
    );

    /* 8. Release allocated list nodes */
    freeList(adj);
}

int main(void) {
    srand((unsigned int)time(NULL));

    /* Sparse graph: 100 edges */
    Edge sparseEdges[100];
    generateEdges(sparseEdges, 100);

    runGraphCase(
        sparseEdges, 100, "Sparse", 1
    );

    /* Dense graph: 4000 edges */
    Edge denseEdges[4000];
    generateEdges(denseEdges, 4000);

    runGraphCase(
        denseEdges, 4000, "Dense", 3
    );

    return 0;
}