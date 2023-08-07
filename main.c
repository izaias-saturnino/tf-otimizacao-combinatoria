#include <stdio.h>
#include <time.h>
#include "utils.h"
#include "grasp.h"

#define TIMEOUT 10

int main (int argc, char **argv)
{
    //read instance
    int nodeCount = 0;
    int edgeCount = 0;
    int colorCount = 0;

    scanf("%d", &nodeCount);
    scanf("%d", &edgeCount);
    scanf("%d", &colorCount);

    float weights[nodeCount];

    for(int i = 0; i < nodeCount; i++){
        scanf("%f", &weights[i]);
    }

    int adjacentNodeListLength[nodeCount];
    int nodeAjacencyList[nodeCount][nodeCount];
    int nodeAjacencyMatrix[nodeCount][nodeCount];

    for (int i = 0; i < nodeCount; i++)
    {
        adjacentNodeListLength[i] = 0;
    }

    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < nodeCount; j++){
            nodeAjacencyMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < edgeCount; i++)
    {
        int firstNode;
        int secondNode;
        scanf("%d", &firstNode);
        scanf("%d", &secondNode);

        nodeAjacencyList[firstNode][adjacentNodeListLength[firstNode]] = secondNode;
        adjacentNodeListLength[firstNode]++;

        nodeAjacencyList[secondNode][adjacentNodeListLength[secondNode]] = firstNode;
        adjacentNodeListLength[secondNode]++;

        nodeAjacencyMatrix[firstNode][secondNode] = 1;
        nodeAjacencyMatrix[secondNode][firstNode] = 1;
    }
    for (int i = 0; i < nodeCount; i++)
    {
        if(adjacentNodeListLength[i] < nodeCount){
            nodeAjacencyList[i][adjacentNodeListLength[i]] = END_OF_LIST;
        }
    }
    //finish reading instance

    int maxColoration[nodeCount];

    for (int i = 0; i < nodeCount; i++)
    {
        maxColoration[i] = UNDEFINED;
    }

    int currentColoration[nodeCount];
    int* maxColorationPointer = maxColoration;
    int* currentColorationPointer = currentColoration;

    clock_t t0, t_diff;
    t0 = clock();

    bool timeout = false;

    bool maxValueInit = false;
    float maxValue = 0;

    while(!timeout){

        for (int i = 0; i < nodeCount; i++)
        {
            currentColorationPointer[i] = UNDEFINED;
        }

        t_diff = clock() - t0;
        double time_taken = ((double)t_diff)/CLOCKS_PER_SEC;

        float newMaxValue = grasp(nodeCount, colorCount, nodeAjacencyList, weights, currentColorationPointer, adjacentNodeListLength, nodeAjacencyMatrix);

        if(!maxValueInit){
            maxValue = newMaxValue;
            maxValueInit = true;
        }
        else if(newMaxValue < maxValue){
            maxValue = newMaxValue;
            int* maxColorationPointerCopy = maxColorationPointer;
            maxColorationPointer = currentColorationPointer;
            currentColorationPointer = maxColorationPointerCopy;
        }

        if(time_taken > TIMEOUT){
            timeout = true;
        }
    }

    printf("%f", maxValue);

    for (int i = 0; i < nodeCount; i++)
    {
        printf("node: %d, color: %d\n", i, maxColorationPointer[i]);
    }
    
    return 0;
}
