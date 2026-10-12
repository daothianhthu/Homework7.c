
#include <stdio.h>
#define V 100

void initMatrix(int matrix[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            matrix[i][j] = 0;
        }
    }
}
int validVertices(int u, int v) {
    return u >= 0 && u < V &&
           v >= 0 && v < V &&
           u != v;
}

void addMatrixEdge(int matrix[V][V], int u, int v, int *comparisons) {
    if(!validVertices(u,v)) return;

    (*comparisons)++;
    if(matrix[u][v]==0){
    matrix[u][v] = 1;
    matrix[v][u] = 1;
    }
}

void deleteMatrixEdge(int matrix[V][V], int u, int v,int *comparisons) {
     if (!validVertices(u, v)) {
        return;
    }
    (*comparisons)++;
    if(matrix[u][v]==1){
    matrix[u][v] = 0;
    matrix[v][u] = 0;
    }
}

int hasMatrixEdge(int matrix[V][V], int u, int v,int *comparisons) {
    if (!validVertices(u, v)) {
        return 0;
    }
    (*comparisons)++;
    return matrix[u][v] == 1;
}

void printMatrixNeighbors(int matrix[V][V], int vertex,int* comparisons) {
    printf("Neighbors of %d: ", vertex);

    for (int i = 0; i < V; i++) {
        (*comparisons)++;
        if (matrix[vertex][i] == 1) {
            printf("%d ", i);
        }
    }

    printf("\n");
}