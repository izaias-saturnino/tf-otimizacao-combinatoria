#include "greedy.h"
#include "utils.h"
#include "neighbours.h"

int grasp(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration, int* adjacentNodeListLength){
    int totalColorWeights[colorCount];
    bool maxValueInit = false;
    int maxValue = 0;

    //The cell[node][color] is equal to the number of adjacent nodes with the same color
    int avaliableColors[nodeCount][colorCount];

    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < colorCount; j++)
        {
            avaliableColors[i][j] = 0;
        }
    }

    int returnValue = UNDEFINED;
    while(returnValue == UNDEFINED){
        returnValue = greedyConstruction(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights, adjacentNodeListLength, avaliableColors);
    }

    for(int i = 0; i < colorCount; i++){
        if(!maxValueInit){
            maxValue = totalColorWeights[i];
            maxValueInit = true;
        }
        else if(maxValue < totalColorWeights[i]){
            maxValue = totalColorWeights[i];
        }
    }

    int newMaxValue = maxValue + 1;

    if(!maxValueInit){
        printf("ERROR: expected value for maxValueInit: true\n");
    }

    while(maxValue != newMaxValue){
        newMaxValue = maxValue;
        newMaxValue = getBestNeighbour(nodeCount, colorCount, nodeAjacencyList, totalColorWeights, coloration, maxValue, weights, avaliableColors);
    }

    return maxValue;
}