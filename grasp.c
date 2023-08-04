#include "greedy.h"

int grasp(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration){
    int totalColorWeights[colorCount];
    int maxValueInit = 0;
    int maxValue = 0;

    int error = -1;
    while(error == -1){
        error = greedyConstruction(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights);
    }

    for(int i = 0; i < colorCount; i++){
        if(!maxValueInit){
            maxValue = totalColorWeights[i];
            maxValueInit = 1;
        }
        else if(maxValue < totalColorWeights[i]){
            maxValue = totalColorWeights[i];
        }
    }

    int newMaxValue = maxValue + 1;

    int firstNode[1];
    int secondNode[1];
    int firstColor[1];
    int secondColor[1];
    int maxColor[1];

    if(maxValueInit == 0){
        printf("ERROR: expected value of maxValueInit is 1\n");
    }

    while(maxValue != newMaxValue){
        newMaxValue = maxValue;
        newMaxValue = getBestNeighbour(nodeCount, colorCount, nodeAjacencyList, totalColorWeights, coloration, maxValue, weights, firstNode, secondNode, firstColor, secondColor, maxColor);
    }

    return maxValue;
}