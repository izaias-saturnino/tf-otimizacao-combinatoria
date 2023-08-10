#include "utils.hpp"
#include <chrono>
#include <thread>

int getLowestAvaliableColor(float* totalColorWeights, int* avaliableColors, int colorCount){
    int lowestAvaliableColor = UNDEFINED;
    int lowestTotalColorWeights = 0;
    for (int i = 0; i < colorCount; i++)
    {
        if(avaliableColors[i] == 0){
            if(lowestAvaliableColor == UNDEFINED){
                lowestTotalColorWeights = totalColorWeights[i];
                lowestAvaliableColor = i;
            }
            else if(totalColorWeights[i] < lowestTotalColorWeights){
                lowestTotalColorWeights = totalColorWeights[i];
                lowestAvaliableColor = i;
            }
        }
    }
    return lowestAvaliableColor;
}

void printVectorAsMatrix(int* vector, int rowCount, int colCount){
    cout << "matrix print\n";
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            cout << vector[i*colCount + j] << " ";
        }
        cout << "\n";
    }
}

void updateNodeColor(int* avaliableColors, int nodeCount, int* coloration, int** nodeAjacencyList, int nodeBestColor, int node, int adjacentNodesCount, int colorCount, float* totalColorWeights, float* weights){
    //this_thread::sleep_for(chrono::seconds(5));
    if(nodeBestColor == UNDEFINED){
        return;
    }
    printVectorAsMatrix(avaliableColors, nodeCount, colorCount);

    int firstNodeColor = coloration[node];
    cout << "node: " << node << ". ";
    cout << "firstNodeColor: " << firstNodeColor << ". ";
    cout << "nodeBestColor: " << nodeBestColor << "\n";

    if (firstNodeColor != UNDEFINED)
    {
        totalColorWeights[firstNodeColor] -= weights[node];
    }
    totalColorWeights[nodeBestColor] += weights[node];
    
    
    for(int adjacentNodeIndex = 0; adjacentNodeIndex < adjacentNodesCount; adjacentNodeIndex++){
        int adjacentNode = nodeAjacencyList[node][adjacentNodeIndex];

        cout << "totalColorWeights[firstNodeColor]: " << totalColorWeights[firstNodeColor] << ". ";
        cout << "totalColorWeights[nodeBestColor]: " << totalColorWeights[nodeBestColor] << "\n";

        if(firstNodeColor != UNDEFINED){
            avaliableColors[adjacentNode*colorCount + firstNodeColor]--;
        }
        avaliableColors[adjacentNode*colorCount + nodeBestColor]++;

        cout << "totalColorWeights[firstNodeColor]: " << totalColorWeights[firstNodeColor] << ". ";
        cout << "totalColorWeights[nodeBestColor]: " << totalColorWeights[nodeBestColor] << "\n";

        cout << "adjacentNode: " << adjacentNode << "\n";
    }
    printVectorAsMatrix(avaliableColors, nodeCount, colorCount);
    coloration[node] = nodeBestColor;
}