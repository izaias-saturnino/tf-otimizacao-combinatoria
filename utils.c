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

void getNodesAjancencyList(int nodeCount, int colorCount, int** graph, int* weights, int* coloration, int** nodeAjacencyList, int* lastAdjacentNodePos){
    for (int i = 0; i < nodeCount; i++)
    {
        lastAdjacentNodePos[i] = 0;
    }
    for (int i = 0; i < nodeCount; i++)
    {
        int firstNode = graph[i][0];
        int secondNode = graph[i][1];

        nodeAjacencyList[firstNode][lastAdjacentNodePos[firstNode]] = secondNode;
        lastAdjacentNodePos[firstNode]++;

        nodeAjacencyList[secondNode][lastAdjacentNodePos[secondNode]] = firstNode;
        lastAdjacentNodePos[secondNode]++;
    }
    for (int i = 0; i < nodeCount; i++)
    {
        if(lastAdjacentNodePos[i] < nodeCount){
            nodeAjacencyList[i][lastAdjacentNodePos[i]] = END_OF_LIST;
        }
    }
}

void getEmptyColoration(int nodeCount, int* coloration){
    for(int i = 0; i < nodeCount; i++){
        coloration[i] = UNDEFINED;
    }
}

void getAvaliableColors(int** nodeAjacencyList, int* coloration, int nodeCount, int colorCount, int node, int* avaliableColors){
    
    for (int i = 0; i < colorCount; i++)
    {
        avaliableColors[i] = 0;
    }
    
    for(int i = 0; i < nodeCount; i++){
        for(int j = 0; j < nodeCount; j++){
            if(nodeAjacencyList[i][j] == END_OF_LIST){
                break;
            }
            int currentNode = nodeAjacencyList[i][j];
            int currentColor = coloration[currentNode];
            avaliableColors[currentColor]++;
        }
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