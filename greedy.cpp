#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "utils.hpp"
#include "greedy.hpp"

int getNodeBestStepColor(int nodeCount, int colorCount, int** nodeAjacencyList, float* weights, int* coloration, int* totalColorWeights, int node, int* avaliableColors){
    if(coloration[node] != UNDEFINED){
        return coloration[node];
    }
    int* nodeAvaliableColors = &avaliableColors[node*colorCount];
    int nodeBestColor = getLowestAvaliableColor(totalColorWeights, nodeAvaliableColors, colorCount);

    return nodeBestColor;
}

int colorAdjacentNodes(int nodeCount, int colorCount, int** nodeAjacencyList, float* weights, int* coloration, int* totalColorWeights, int node, int adjacentNodesCount, int* avaliableColors){
    int i = node;

    int firstAdjacentNodePos = rand() % adjacentNodesCount;

    int firstAdjacentNode = nodeAjacencyList[i][firstAdjacentNodePos];

    int color = getNodeBestStepColor(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights, firstAdjacentNode, avaliableColors);

    if(color == UNDEFINED){
        return color;
    }

    for(int j = 0; j < adjacentNodesCount; j++){
        int currentNode = nodeAjacencyList[i][j];

        color = getNodeBestStepColor(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights, currentNode, avaliableColors);

        updateNodeColor(avaliableColors, nodeCount, coloration, nodeAjacencyList, color, node, adjacentNodesCount, colorCount);

        if(color == UNDEFINED){
            break;
        }
        else{
            totalColorWeights[color] += weights[currentNode];
        }
    }
    return color;
}

int greedyConstruction(int nodeCount, int colorCount, int** nodeAjacencyList, float* weights, int* coloration, int* totalColorWeights, int* adjacentNodeQuantity, int* avaliableColors){

    for (int i = 0; i < colorCount; i++)
    {
        totalColorWeights[i] = 0;
    }

    bool toColorAdjacentNodes[nodeCount] = {false};

    int firstNodeToColor = rand() % nodeCount;
    toColorAdjacentNodes[firstNodeToColor] = true;

    bool coloredAdjacentNodes[nodeCount] = {false};

    int totalColoredAdjacentNodes = 1;
    int oldTotalColoredAdjacentNodes = 0;

    int returnValue = 0;

    while(totalColoredAdjacentNodes < nodeCount){

        if(totalColoredAdjacentNodes <= oldTotalColoredAdjacentNodes){
            int nodesLeft = nodeCount - totalColoredAdjacentNodes;
            
            int newNodeToColorIndex = rand() % nodesLeft;

            int newNodeToColor = UNDEFINED;

            for(int i = 0; i < nodeCount; i++){
                if(coloredAdjacentNodes[i] == 0){
                    if(newNodeToColorIndex == 0){
                        newNodeToColor = i;
                        break;
                    }
                    newNodeToColorIndex--;
                }
            }

            if(newNodeToColor == UNDEFINED){
                printf("ERROR");
                break;
            }

            int color = getLowestColor(totalColorWeights, colorCount);

            updateNodeColor(avaliableColors, nodeCount, coloration, nodeAjacencyList, color, newNodeToColor, adjacentNodeQuantity[newNodeToColor], colorCount);
            totalColorWeights[color] += weights[newNodeToColor];

            toColorAdjacentNodes[newNodeToColor] = true;
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
                for (int j = 0; j < adjacentNodeQuantity[i]; j++)
                {
                    int currentNode = nodeAjacencyList[i][j];

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