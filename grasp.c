#include "greedy.h"

int grasp(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration){
    int totalColorWeights[colorCount];
    int maxValueInit = 0;
    int maxValue = 0;

    int error = -1;
    while(error = -1){
        error = greedyConstruction(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights);
        if(error == -1){
            continue;
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
    }
    return maxValue;
}