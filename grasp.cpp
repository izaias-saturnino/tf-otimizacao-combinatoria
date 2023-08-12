#include "grasp.hpp"
#include "greedy.hpp"
#include "utils.hpp"
#include "neighbours.hpp"

float grasp(int nodeCount, int colorCount, int** nodeAjacencyList, float* weights, int* coloration, int* adjacentNodeListLength, unordered_set<unsigned long long>* adjacencyHash, clock_t t0){
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

    //cout << "start of greedyConstruction\n";

    int returnValue = greedyConstruction(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights, adjacentNodeListLength, &avaliableColors[0][0], t0);

    if (returnValue == UNDEFINED)
    {
        return maxValue;
    }

    for (int i = 0; i < nodeCount; i++)
    {
        //cout << "node: " << i << ". color: " << coloration[i] << "\n";
    }

    for (int i = 0; i < colorCount; i++)
    {
        //old
        //cout << "totalColorWeights[" << i << "]: " << totalColorWeights[i] << "\n";
    }

    //cout << "end of greedyConstruction\n";

    maxValue = totalColorWeights[0];

    for(int i = 0; i < colorCount; i++){
        if(maxValue < totalColorWeights[i]){
            maxValue = totalColorWeights[i];
        }
    }

    //cout << "maxValue: " << maxValue << "\n";

    float totalColorWeightsCopy[colorCount];

    int colorationCopy[nodeCount];
    
    float oldMaxValue = maxValue;

    int firstNode, secondNode, firstColor, secondColor = UNDEFINED;

    do{
        clock_t t_diff = clock() - t0;
        double time_taken = ((double)t_diff)/CLOCKS_PER_SEC;

        if(time_taken > TIMEOUT){
            break;
        }

        //cout << "neighbourhood search iteration\n";

        for (int i = 0; i < nodeCount; i++)
        {
            colorationCopy[i] = coloration[i];
        }

        for (int i = 0; i < colorCount; i++)
        {
            totalColorWeightsCopy[i] = totalColorWeights[i];
        }
        
        oldMaxValue = maxValue;
        maxValue = getBestNeighbour(nodeCount, colorCount, nodeAjacencyList, totalColorWeights, coloration, oldMaxValue, weights, &avaliableColors[0][0], adjacencyHash, adjacentNodeListLength, firstNode, secondNode, firstColor, secondColor);
        
        //printVectorAsMatrix(&avaliableColors[0][0], nodeCount, colorCount);

        if (maxValue < oldMaxValue)
        {
            for (int i = 0; i < nodeCount; i++)
            {
                //cout << "node: " << i << ". color: " << coloration[i] << "\n";
            }
        }

    } while (maxValue < oldMaxValue);

    //cout << "end of neighbourhood search\n";

    cout << "grasp iteration coloration:\n";

    for (int i = 0; i < nodeCount; i++)
    {
        cout << coloration[i] << " ";
    }
    cout << "\n";
    
    return maxValue;
}