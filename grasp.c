#include "greedy.h"
#include "utils.h"

int grasp(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration, int* adjacentNodeQuantity){
    int totalColorWeights[colorCount];
    bool maxValueInit = false;
    int maxValue = 0;

    int returnValue = UNDEFINED;
    while(returnValue == UNDEFINED){
        returnValue = greedyConstruction(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights, adjacentNodeQuantity);
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

    int firstNode;
    int secondNode;
    int firstColor;
    int secondColor;
    int maxColor;

    if(!maxValueInit){
        printf("ERROR: expected value for maxValueInit: true\n");
    }

    while(maxValue != newMaxValue){
        newMaxValue = maxValue;
        newMaxValue = getBestNeighbour(nodeCount, colorCount, nodeAjacencyList, totalColorWeights, coloration, maxValue, weights, &firstNode, &secondNode, &firstColor, &secondColor, &maxColor);
    }

    return maxValue;
}