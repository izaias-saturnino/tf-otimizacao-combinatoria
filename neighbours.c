#include "neighbours.h"
#include "utils.h"

int getColorChangesValue(int* coloration, int firstNodeNewColor, int secondNodeNewColor, int firstNode, int secondNode, int* totalColorWeights, int maxColorValue, int* weights, int colorCount, int* maxColor){

    int firstNodeCurrentColor = coloration[firstNode];
    int secondNodeCurrentColor = coloration[secondNode];

    totalColorWeights[firstNodeCurrentColor] -= weights[firstNode];
    totalColorWeights[firstNodeNewColor] += weights[firstNode];

    totalColorWeights[secondNodeCurrentColor] -= weights[secondNode];
    totalColorWeights[secondNodeNewColor] += weights[secondNode];

    maxColorValue = totalColorWeights[firstNodeCurrentColor];

    for(int i = 0; i < colorCount; i++){
        if(totalColorWeights[i] > maxColorValue){
            maxColorValue = totalColorWeights[i];
            *maxColor = i;
        }
    }
    return maxColorValue;
}

int getBestNeighbour(int nodeCount, int colorCount, int** nodeAjacencyList, int* totalColorWeights, int* coloration, int maxColorValue, int* weights, int* firstNode, int* secondNode, int* firstColor, int* secondColor, int* maxColor, int** avaliableColors){
    if(colorCount == 1){
        return maxColorValue;
    }
    if(nodeCount < 3){
        return maxColorValue;
    }

    *maxColor = UNDEFINED;

    int bestFirstNodeIterator = 0;
    int bestSecondNodeIterator = 1;
    int bestFirstNodeColorIterator = 0;
    int bestSecondNodeColorIterator = 1;

    int totalColorWeightsCopy[colorCount];

    for(int firstNodeIterator = 0; firstNodeIterator < nodeCount; firstNodeIterator++){
        int* firstNodeAvaliableColors = avaliableColors[firstNodeIterator];
        for(int secondNodeIterator = 0; secondNodeIterator < nodeCount; secondNodeIterator++){
            int* secondNodeAvaliableColors = avaliableColors[secondNodeIterator];
            
            bool nodes_adjacent = areNodesAdjacent(firstNodeIterator, secondNodeIterator, nodeAjacencyList, nodeCount);
            
            for(int firstNodeColorIterator = 0; firstNodeColorIterator < colorCount; firstNodeColorIterator++){
                for(int secondNodeColorIterator = 0; secondNodeColorIterator < colorCount; secondNodeColorIterator++){
                    
                    if(nodes_adjacent){
                        if(firstNodeColorIterator == secondNodeColorIterator){
                            continue;
                        }
                        firstNodeAvaliableColors[secondNodeColorIterator] -= 1;
                        secondNodeAvaliableColors[firstNodeColorIterator] -= 1;
                    }
                    
                    if(!firstNodeAvaliableColors[firstNodeColorIterator]){
                        if(!secondNodeAvaliableColors[secondNodeColorIterator]){
                            int maxColorCopy = *maxColor;
                            if(firstNodeColorIterator != maxColorCopy && secondNodeColorIterator != maxColorCopy && maxColorCopy != UNDEFINED){
                                continue;
                            }
                            int newMaxColor = UNDEFINED;

                            {
                                int firstNodeCurrentColor = coloration[firstNodeIterator];
                                int secondNodeCurrentColor = coloration[secondNodeIterator];

                                totalColorWeightsCopy[firstNodeCurrentColor] = totalColorWeights[firstNodeCurrentColor];
                                totalColorWeightsCopy[firstNodeColorIterator] = totalColorWeights[firstNodeColorIterator];

                                totalColorWeightsCopy[secondNodeCurrentColor] = totalColorWeights[secondNodeCurrentColor];
                                totalColorWeightsCopy[secondNodeColorIterator] = totalColorWeights[secondNodeColorIterator];
                            }

                            int newValue = getColorChangesValue(coloration, firstNodeColorIterator, secondNodeColorIterator, firstNodeIterator, secondNodeIterator, totalColorWeightsCopy, maxColorValue, weights, colorCount, newMaxColor);
                            
                            if(newValue < maxColorValue){
                                maxColorValue = newValue;
                                *maxColor = newMaxColor;

                                bestFirstNodeIterator = firstNodeIterator;
                                bestSecondNodeIterator = secondNodeIterator;
                                bestFirstNodeColorIterator = firstNodeColorIterator;
                                bestSecondNodeColorIterator = secondNodeColorIterator;
                            }
                        }
                    }
                }
            }
        }
    }

    {
        int firstNodeCurrentColor = coloration[bestFirstNodeIterator];
        int secondNodeCurrentColor = coloration[bestSecondNodeIterator];

        totalColorWeights[firstNodeCurrentColor] = totalColorWeightsCopy[firstNodeCurrentColor];
        totalColorWeights[bestFirstNodeColorIterator] = totalColorWeightsCopy[bestFirstNodeColorIterator];

        totalColorWeights[secondNodeCurrentColor] = totalColorWeightsCopy[secondNodeCurrentColor];
        totalColorWeights[bestSecondNodeColorIterator] = totalColorWeightsCopy[bestSecondNodeColorIterator];
    }

    *firstNode = bestFirstNodeIterator;
    *secondNode = bestSecondNodeIterator;
    *firstColor = bestFirstNodeColorIterator;
    *secondColor = bestSecondNodeColorIterator;

    return maxColorValue;
}