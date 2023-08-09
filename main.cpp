#include <stdio.h>
#include <time.h>
#include <iostream>
#include <unordered_set>
#include "utils.hpp"
#include "grasp.hpp"

#define TIMEOUT 10

int main() {
    //read instance
    int nodeCount = 0;
    int edgeCount = 0;
    int colorCount = 0;

    scanf("%d", &nodeCount);
    scanf("%d", &edgeCount);
    scanf("%d", &colorCount);

    float weights[nodeCount];

    //reading weights
    for(int i = 0; i < nodeCount; i++){
        scanf("%f", &weights[i]);
    }

    //creating hash for edges
    const std::size_t expectedNumElements = edgeCount*2; // Set your expected number of elements

    // Calculate an appropriate initial capacity based on expectedNumElements
    const std::size_t initialCapacity = std::max(static_cast<std::size_t>(expectedNumElements / 0.7), static_cast<std::size_t>(10));

    // An unordered_set with custom hash function and initial capacity
    std::unordered_set<std::pair<int, int>, TupleHash> adjacencyHash(initialCapacity);

    //creaating list for edges
    int adjacentNodeListLength[nodeCount] = {0};
    int adjacentNodeListInit[nodeCount] = {0};
    int* nodeAjacencyList[nodeCount];

    //reading edges
    int edges[edgeCount][2];

    for (int i = 0; i < edgeCount; i++){
        int firstNode;
        int secondNode;
        scanf("%d", &firstNode);
        scanf("%d", &secondNode);

        edges[i][0] = firstNode;
        edges[i][1] = secondNode;

        //updating edges number for each node
        adjacentNodeListLength[firstNode]++;
        adjacentNodeListLength[secondNode]++;
    }

    //creating array for each node to fill the nodeAjacencyLists with the adjacent nodes numbers
    for (int i = 0; i < nodeCount; i++)
    {
        int nodeListLength = adjacentNodeListLength[i];
        nodeAjacencyList[i] = new int[nodeListLength];
    }

    //filling the hash with the edges
    for (int i = 0; i < edgeCount; i++)
    {
        int firstNode = edges[i][0];
        int secondNode = edges[i][1];

        adjacencyHash.insert(std::make_pair(firstNode, secondNode));
        adjacencyHash.insert(std::make_pair(secondNode, firstNode));

        //filling the nodeAjacencyList with the edges
        nodeAjacencyList[firstNode][adjacentNodeListInit[firstNode]] = secondNode;
        adjacentNodeListInit[firstNode]++;

        nodeAjacencyList[secondNode][adjacentNodeListInit[secondNode]] = firstNode;
        adjacentNodeListInit[secondNode]++;
    }
    //finish reading instance

    int maxColoration[nodeCount] = {UNDEFINED};

    int currentColoration[nodeCount];
    int* maxColorationPointer = maxColoration;
    int* currentColorationPointer = currentColoration;

    clock_t t0, t_diff;
    t0 = clock();

    bool timeout = false;

    bool maxValueInit = false;
    float maxValue = 0;

    while(!timeout){

        //clear currentColorationPointer to reuse in GRASP
        for (int i = 0; i < nodeCount; i++)
        {
            currentColorationPointer[i] = UNDEFINED;
        }

        t_diff = clock() - t0;
        double time_taken = ((double)t_diff)/CLOCKS_PER_SEC;

        float newMaxValue = grasp(nodeCount, colorCount, nodeAjacencyList, weights, currentColorationPointer, adjacentNodeListLength, &adjacencyHash);

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
