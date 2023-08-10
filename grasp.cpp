#include "grasp.hpp"
#include "greedy.hpp"
#include "utils.hpp"
#include "neighbours.hpp"

float grasp(int nodeCount, int colorCount, int** nodeAjacencyList, float* weights, int* coloration, int* adjacentNodeListLength, unordered_set<pair<int, int>, TupleHash>* adjacencyHash){
    float totalColorWeights[colorCount];
    bool maxValueInit = false;
    float maxValue = 0;

    //The cell[node][color] is equal to the number of adjacent nodes with the same color
    int avaliableColors[nodeCount][colorCount];

    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < colorCount; j++)
        {
            avaliableColors[i][j] = 0;
        }
    }

    //cout << "start of greedyConstruction\n";

    int returnValue = UNDEFINED;
    while(returnValue == UNDEFINED){
        //remake greedy construction
        returnValue = greedyConstruction(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights, adjacentNodeListLength, &avaliableColors[0][0]);
    }

    for (int i = 0; i < nodeCount; i++)
    {
        //cout << "node: " << i << ". color: " << coloration[i] << "\n";
    }

    //cout << "end of greedyConstruction\n";

    for(int i = 0; i < colorCount; i++){
        if(!maxValueInit){
            maxValue = totalColorWeights[i];
            maxValueInit = true;
        }
        else if(maxValue < totalColorWeights[i]){
            maxValue = totalColorWeights[i];
        }
    }

    float newMaxValue = maxValue - 1;

    if(!maxValueInit){
        cout << "ERROR: expected value for maxValueInit: true\n";
    }

    while(maxValue != newMaxValue){
        maxValue = newMaxValue;
        newMaxValue = getBestNeighbour(nodeCount, colorCount, nodeAjacencyList, totalColorWeights, coloration, maxValue, weights, &avaliableColors[0][0], adjacencyHash, adjacentNodeListLength);
    }

    for (int i = 0; i < nodeCount; i++)
    {
        //cout << "node: " << i << ". color: " << coloration[i] << "\n";
    }

    //cout << "end of neighbourhood search\n";
    
    return maxValue;
}