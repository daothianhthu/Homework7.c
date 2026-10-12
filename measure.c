#include <stdio.h>
#include <stddef.h>

void printCaseReport(
    int caseNumber,
    const char *graphType,
    const char *representation,
    size_t memoryBytes,
    int insertComparisons,
    int deleteComparisons,
    int connectivityComparisons,
    int adjacentComparisons
) {
    printf("\nCase %d : %s Graph - %s\n",
           caseNumber, graphType, representation);

    printf("Memory                         : %zu Bytes\n",
           memoryBytes);

    printf("Edge insertion comparisons     : %d\n",
           insertComparisons);

    printf("Edge deletion comparisons      : %d\n",
           deleteComparisons);

    printf("Connectivity check comparisons : %d\n",
           connectivityComparisons);

    printf("Adjacent vertices comparisons  : %d\n",
           adjacentComparisons);
}