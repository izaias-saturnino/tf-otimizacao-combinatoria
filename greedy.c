#include <time.h>
#include <stdlib.h>
#include "utils.h"

//Selects the node coloration with the lowest maxValue in this step. Returns the selected color if coloring was possible and -1 if it was not.
int colorNode(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration, int* totalColorWeights, int node){
    if(coloration[node] != -1){
        return coloration[node];
    }
    int nodeAvaliableColors[colorCount];
    getAvaliableColors(nodeAjacencyList, coloration, nodeCount, colorCount, node, nodeAvaliableColors);
    int nodeBestColor = getLowestAvaliableColor(totalColorWeights, nodeAvaliableColors, colorCount);
    return nodeBestColor;
}

//Colors every adjacent node following the colorNode() heuristic. returns -1 if the adjacent nodes could not be colored
int colorAdjacentNodes(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration, int* totalColorWeights, int node){
    int color = 0;
    int i = node;
    for(int j = 0; j < nodeCount; j++){
        int currentNode = nodeAjacencyList[i][j];
        if(currentNode == -1){
            break;
        }
        color = colorNode(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights, currentNode);
        if(color == -1){
            break;
        }
        else{
            totalColorWeights[color] += weights[currentNode];
        }
    }
    return color;
}

//colors the graph following the colorNode heuristic. returns -1 if was not able to construct following the heuristic
int greedyConstruction(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration, int* totalColorWeights){

    for (int i = 0; i < colorCount; i++)
    {
        totalColorWeights[i] = 0;
    }
    
    srand(time(NULL));

    int coloredAdjacentNodes[nodeCount];

    for (int i = 0; i < nodeCount; i++)
    {
        coloredAdjacentNodes[i] = 0;
    }

    int toColorAdjacentNodes[nodeCount];

    for (int i = 0; i < nodeCount; i++)
    {
        toColorAdjacentNodes[i] = 0;
    }

    int error = 0;

    int totalColoredAdjacentNodes = 0;

    while(totalColoredAdjacentNodes < nodeCount){

        int nodesLeft = 0;

        for (int i = 0; i < nodeCount; i++)
        {
            nodesLeft += toColorAdjacentNodes[i];
        }
        
        if(nodesLeft == 0){
            int node;
            for (node = 0; node < nodeCount; node++)
            {
                if(coloredAdjacentNodes[node] == 0){
                    break;
                }
            }
            
            int color = getLowestColor(totalColorWeights, colorCount);

            coloration[node] = color;
            totalColorWeights[color] += weights[node];

            toColorAdjacentNodes[node] = 1;
        }

        for (int i = 0; i < nodeCount; i++)
        {
            if(toColorAdjacentNodes[i]){
                error = colorAdjacentNodes(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights, i);
                if(error == -1){
                    break;
                }
                totalColoredAdjacentNodes++;
                toColorAdjacentNodes[i] = 0;
                coloredAdjacentNodes[i] = 1;
                for (int j = 0; j < nodeCount; j++)
                {
                    int currentNode = nodeAjacencyList[i][j];
                    if(currentNode != -1){
                        if(coloredAdjacentNodes[currentNode] == 0){
                            toColorAdjacentNodes[currentNode] = 1;
                        }
                    }
                }
            }
        }
        if(error == -1){
            break;
        }
    }
    return error;
}