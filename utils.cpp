#include "utils.hpp"

int getLowestColor(int* totalColorWeights, int colorCount){
    int lowestAvaliableColor = UNDEFINED;
    int lowestTotalColorWeights = 0;
    for (int i = 0; i < colorCount; i++)
    {
        if(lowestAvaliableColor == UNDEFINED){
            lowestAvaliableColor = i;
            lowestTotalColorWeights = totalColorWeights[i];
        }
        else if(lowestTotalColorWeights > totalColorWeights[i]){
            lowestAvaliableColor = i;
            lowestTotalColorWeights = totalColorWeights[i];
        }
    }
    return lowestAvaliableColor;
}

int getLowestAvaliableColor(int* totalColorWeights, int* avaliableColors, int colorCount){
    int lowestAvaliableColor = UNDEFINED;
    int lowestTotalColorWeights = 0;
    for (int i = 0; i < colorCount; i++)
    {
        if(avaliableColors[i] == 0){
            if(lowestAvaliableColor == UNDEFINED){
                lowestAvaliableColor = i;
                lowestTotalColorWeights = totalColorWeights[i];
            }
            else if(lowestTotalColorWeights > totalColorWeights[i]){
                lowestAvaliableColor = i;
                lowestTotalColorWeights = totalColorWeights[i];
            }
        }
    }
    return lowestAvaliableColor;
}

void getEmptyColoration(int nodeCount, int* coloration){
    for(int i = 0; i < nodeCount; i++){
        coloration[i] = UNDEFINED;
    }
}

void updateNodeColor(int* avaliableColors, int nodeCount, int* coloration, int** nodeAjacencyList, int nodeBestColor, int node, int adjacentNodesCount, int colorCount){
    if(nodeBestColor == UNDEFINED){
        return;
    }
    for(int adjacentNodeIndex = 0; adjacentNodeIndex < adjacentNodesCount; adjacentNodeIndex++){
        int adjacentNode = nodeAjacencyList[node][adjacentNodeIndex];

        int firstNodeColor = coloration[node];
        if(firstNodeColor != UNDEFINED){
            avaliableColors[adjacentNode*colorCount + firstNodeColor]--;
        }
        avaliableColors[adjacentNode*colorCount + nodeBestColor]++;
    }
    coloration[node] = nodeBestColor;
}