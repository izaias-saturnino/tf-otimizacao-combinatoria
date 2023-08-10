#include "grasp.hpp"
#include "greedy.hpp"
#include "utils.hpp"
#include "neighbours.hpp"

float grasp(int nodeCount, int colorCount, int** nodeAjacencyList, float* weights, int* coloration, int* adjacentNodeListLength, unordered_set<pair<int, int>, TupleHash>* adjacencyHash){
    float totalColorWeights[colorCount];
    float maxValue = numeric_limits<float>::infinity();

    //The cell[node][color] is equal to the number of adjacent nodes with the same color
    int avaliableColors[nodeCount][colorCount];

    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < colorCount; j++)
        {
            avaliableColors[i][j] = 0;
        }
    }

    cout << "start of greedyConstruction\n";

    int returnValue = UNDEFINED;
    while(returnValue == UNDEFINED){
        //remake greedy construction
        returnValue = greedyConstruction(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights, adjacentNodeListLength, &avaliableColors[0][0]);
    }

    for (int i = 0; i < nodeCount; i++)
    {
        cout << "node: " << i << ". color: " << coloration[i] << "\n";
    }

    cout << "end of greedyConstruction\n";

    maxValue = totalColorWeights[0];

    for(int i = 0; i < colorCount; i++){
        if(maxValue < totalColorWeights[i]){
            maxValue = totalColorWeights[i];
        }
    }

    float totalColorWeightsCopy[colorCount];

    for (int i = 0; i < colorCount; i++)
    {
        totalColorWeightsCopy[i] = totalColorWeights[i];
    }

    int colorationCopy[nodeCount];

    for (int i = 0; i < nodeCount; i++)
    {
        colorationCopy[i] = coloration[i];
    }

    int* currentColorationPointer = colorationCopy;
    float* currenttotalColorWeightsPointer = totalColorWeightsCopy;
    
    float oldMaxValue = maxValue;

    do{
        cout << "neighbourhood search iteration\n";
        
        oldMaxValue = maxValue;
        maxValue = getBestNeighbour(nodeCount, colorCount, nodeAjacencyList, totalColorWeights, coloration, oldMaxValue, weights, &avaliableColors[0][0], adjacencyHash, adjacentNodeListLength);

        if (maxValue < oldMaxValue)
        {
            //get changes
        }
        
        for (int i = 0; i < nodeCount; i++)
        {
            cout << "node: " << i << ". color: " << coloration[i] << "\n";
        }
    } while (maxValue < oldMaxValue);

    cout << "end of neighbourhood search\n";

    for (int i = 0; i < nodeCount; i++)
    {
        cout << "node: " << i << ". color: " << coloration[i] << "\n";
    }
    
    return maxValue;
}