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

void updateNodeColor(int* avaliableColors, int nodeCount, int* coloration, int** nodeAjacencyList, int nodeBestColor, int node, int adjacentNodesCount, int colorCount, float* totalColorWeights, float* weights){
    //this_thread::sleep_for(chrono::seconds(5));
    if(nodeBestColor == UNDEFINED){
        return;
    }
    for(int adjacentNodeIndex = 0; adjacentNodeIndex < adjacentNodesCount; adjacentNodeIndex++){
        int adjacentNode = nodeAjacencyList[node][adjacentNodeIndex];

        int firstNodeColor = coloration[node];
        if(firstNodeColor != UNDEFINED){
            avaliableColors[adjacentNode*colorCount + firstNodeColor]--;
            totalColorWeights[firstNodeColor] -= weights[node];
        }
        avaliableColors[adjacentNode*colorCount + nodeBestColor]++;
        totalColorWeights[nodeBestColor] += weights[node];
    }
    coloration[node] = nodeBestColor;
}