#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define V 100

typedef struct {
    int u;
    int v;
} Edge;


int edgeExists(Edge edges[], int count, int u, int v)
{
    if (u > v) {
        int temp = u;
        u = v;
        v = temp;
    }
    for (int i = 0; i < count; i++) {
        if (edges[i].u == u && edges[i].v == v) {
            return 1;
        }
    }
    return 0;
}
void generateEdges(Edge edges[], int edgeCount)
{
    int count = 0;

    while (count < edgeCount) {

        int u = rand() % V;
        int v = rand() % V;

        if (u == v)
            continue;

        if (u > v) {
            int temp = u;
            u = v;
            v = temp;
        }

        if (edgeExists(edges, count, u, v))
            continue;

        edges[count].u = u;
        edges[count].v = v;

        count++;
    }
}