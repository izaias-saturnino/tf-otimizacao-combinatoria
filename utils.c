#include "utils.h"

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
        if(!avaliableColors[i]){
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

void getNodesAjancencyList(int nodeCount, int colorCount, int** graph, int* weights, int* coloration, int** nodeAjacencyList, int* adjacentNodeListLength){
    for (int i = 0; i < nodeCount; i++)
    {
        adjacentNodeListLength[i] = 0;
    }
    for (int i = 0; i < nodeCount; i++)
    {
        int firstNode = graph[i][0];
        int secondNode = graph[i][1];

        nodeAjacencyList[firstNode][adjacentNodeListLength[firstNode]] = secondNode;
        adjacentNodeListLength[firstNode]++;

        nodeAjacencyList[secondNode][adjacentNodeListLength[secondNode]] = firstNode;
        adjacentNodeListLength[secondNode]++;
    }
    for (int i = 0; i < nodeCount; i++)
    {
        if(adjacentNodeListLength[i] < nodeCount){
            nodeAjacencyList[i][adjacentNodeListLength[i]] = END_OF_LIST;
        }
    }
}

void getEmptyColoration(int nodeCount, int* coloration){
    for(int i = 0; i < nodeCount; i++){
        coloration[i] = UNDEFINED;
    }
}

bool areNodesAdjacent(int firstNode, int secondNode, int** nodeAjacencyList, int nodeCount){
    int i = firstNode;
    bool areAdjacent = false;
    for(int j = 0; j < nodeCount; j++){
        int currentNode = nodeAjacencyList[i][j];
        if(currentNode == END_OF_LIST){
            break;
        }
        if(currentNode == secondNode){
            areAdjacent = true;
            break;
        }
    }
    return areAdjacent;
}

void updateNodeColor(int** avaliableColors, int nodeCount, int* coloration, int** nodeAjacencyList, int nodeBestColor, int node){
    for(int adjacentNodeIndex = 0; adjacentNodeIndex < nodeCount; adjacentNodeIndex++){
        int adjacentNode = nodeAjacencyList[node][adjacentNodeIndex];
        if(adjacentNode == END_OF_LIST){
            break;
        }
        int firstNodeColor = coloration[node];
        if(firstNodeColor != UNDEFINED){
            avaliableColors[adjacentNode][firstNodeColor]--;
        }
        avaliableColors[adjacentNode][nodeBestColor]++;
    }
    coloration[node] = nodeBestColor;
}