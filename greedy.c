#include <time.h>
#include <stdlib.h>
#include "utils.h"
#include "greedy.h"

int getNodeBestStepColor(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration, int* totalColorWeights, int node, int** avaliableColors){
    if(coloration[node] != UNDEFINED){
        return coloration[node];
    }
    int* nodeAvaliableColors = avaliableColors[node];
    int nodeBestColor = getLowestAvaliableColor(totalColorWeights, nodeAvaliableColors, colorCount);

    return nodeBestColor;
}

int colorAdjacentNodes(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration, int* totalColorWeights, int node, int adjacentNodesCount, int** avaliableColors){
    int i = node;

    int firstAdjacentNodePos = rand() % adjacentNodesCount;

    int firstAdjacentNode = nodeAjacencyList[i][firstAdjacentNodePos];

    int color = getNodeBestStepColor(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights, firstAdjacentNode, avaliableColors);

    if(color == UNDEFINED){
        return color;
    }

    for(int j = 0; j < nodeCount; j++){
        int currentNode = nodeAjacencyList[i][j];
        if(currentNode == END_OF_LIST){
            break;
        }
        color = getNodeBestStepColor(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights, currentNode, avaliableColors);

        updateNodeAvaliableColors(avaliableColors, nodeCount, coloration, nodeAjacencyList, color, node);
        coloration[node] = color;

        if(color == UNDEFINED){
            break;
        }
        else{
            totalColorWeights[color] += weights[currentNode];
        }
    }
    return color;
}

int greedyConstruction(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration, int* totalColorWeights, int* adjacentNodeQuantity, int** avaliableColors){

    for (int i = 0; i < colorCount; i++)
    {
        totalColorWeights[i] = 0;
    }
    
    srand(time(NULL));

    bool toColorAdjacentNodes[nodeCount];

    for (int i = 0; i < nodeCount; i++)
    {
        toColorAdjacentNodes[i] = false;
    }

    int firstNodeToColor = rand() % nodeCount;
    toColorAdjacentNodes[firstNodeToColor] = true;

    bool coloredAdjacentNodes[nodeCount];

    for (int i = 0; i < nodeCount; i++)
    {
        coloredAdjacentNodes[i] = false;
    }

    int totalColoredAdjacentNodes = 1;
    int oldTotalColoredAdjacentNodes = 0;

    int returnValue = 0;

    while(totalColoredAdjacentNodes < nodeCount){

        if(totalColoredAdjacentNodes <= oldTotalColoredAdjacentNodes){
            int nodesLeft = 0;

            for (int i = 0; i < nodeCount; i++)
            {
                nodesLeft += toColorAdjacentNodes[i];
            }
            
            if(nodesLeft == 0){
                int node;
                for (node = 0; node < nodeCount; node++)
                {
                    if(coloredAdjacentNodes[node] == false){
                        break;
                    }
                }
                
                int color = getLowestColor(totalColorWeights, colorCount);

                updateNodeAvaliableColors(avaliableColors, nodeCount, coloration, nodeAjacencyList, color, node);
                coloration[node] = color;
                totalColorWeights[color] += weights[node];

                toColorAdjacentNodes[node] = true;
            }

            oldTotalColoredAdjacentNodes = totalColoredAdjacentNodes;
        }

        for (int i = 0; i < nodeCount; i++)
        {
            if(toColorAdjacentNodes[i]){
                returnValue = colorAdjacentNodes(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights, i, adjacentNodeQuantity[i], avaliableColors);
                if(returnValue < 0){
                    break;
                }
                totalColoredAdjacentNodes++;
                toColorAdjacentNodes[i] = false;
                coloredAdjacentNodes[i] = true;

                //add adjacent nodes to toColorAdjacentNodes
                for (int j = 0; j < nodeCount; j++)
                {
                    int currentNode = nodeAjacencyList[i][j];
                    if(currentNode == END_OF_LIST){
                        break;
                    }
                    if(coloredAdjacentNodes[currentNode] == false){
                        toColorAdjacentNodes[currentNode] = true;
                    }
                }
            }
        }
        if(returnValue < 0){
            break;
        }
    }
    return returnValue;
}