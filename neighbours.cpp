#include "neighbours.hpp"
#include "utils.hpp"

int getColorChangesValue(int* coloration, int firstNodeNewColor, int secondNodeNewColor, int firstNode, int secondNode, int* totalColorWeights, int maxColorValue, float* weights, int colorCount, int* maxColor){

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

int getBestNeighbour(int nodeCount, int colorCount, int** nodeAjacencyList, int* totalColorWeights, int* coloration, int maxColorValue, float* weights, int* avaliableColors, unordered_set<pair<int, int>, TupleHash>* adjacencyHash, int* adjacentNodeQuantity){
    if(colorCount == 1){
        return maxColorValue;
    }
    if(nodeCount < 3){
        return maxColorValue;
    }

    int maxColor = UNDEFINED;

    int bestFirstNodeIterator = 0;
    int bestSecondNodeIterator = 1;

    int bestFirstNodeColorIterator = 0;
    int bestSecondNodeColorIterator = 1;

    int totalColorWeightsCopy[colorCount];

    for(int firstNodeIterator = 0; firstNodeIterator < nodeCount; firstNodeIterator++){
        int* firstNodeAvaliableColors = &avaliableColors[firstNodeIterator*colorCount];
        for(int secondNodeIterator = 0; secondNodeIterator < nodeCount; secondNodeIterator++){
            int* secondNodeAvaliableColors = &avaliableColors[secondNodeIterator*colorCount];
            
            auto pair = make_pair(firstNodeIterator,secondNodeIterator);
            bool nodes_adjacent = (*adjacencyHash).find(pair) != (*adjacencyHash).end();
            
            for(int firstNodeColorIterator = 0; firstNodeColorIterator < colorCount; firstNodeColorIterator++){
                for(int secondNodeColorIterator = 0; secondNodeColorIterator < colorCount; secondNodeColorIterator++){
                    
                    if(nodes_adjacent){
                        if(firstNodeColorIterator == secondNodeColorIterator){
                            continue;
                        }
                        firstNodeAvaliableColors[secondNodeColorIterator] -= 1;
                        secondNodeAvaliableColors[firstNodeColorIterator] -= 1;
                    }
                    
                    if(firstNodeAvaliableColors[firstNodeColorIterator] == 0){
                        if(secondNodeAvaliableColors[secondNodeColorIterator] == 0){
                            if(firstNodeColorIterator != maxColor && secondNodeColorIterator != maxColor && maxColor != UNDEFINED){
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

                            int newValue = getColorChangesValue(coloration, firstNodeColorIterator, secondNodeColorIterator, firstNodeIterator, secondNodeIterator, totalColorWeightsCopy, maxColorValue, weights, colorCount, &newMaxColor);
                            
                            if(newValue < maxColorValue){
                                maxColorValue = newValue;
                                maxColor = newMaxColor;

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

    updateNodeColor(avaliableColors, nodeCount, coloration, nodeAjacencyList, bestFirstNodeColorIterator, bestFirstNodeIterator, adjacentNodeQuantity[bestFirstNodeIterator], colorCount);
    updateNodeColor(avaliableColors, nodeCount, coloration, nodeAjacencyList, bestSecondNodeColorIterator, bestSecondNodeIterator, adjacentNodeQuantity[bestSecondNodeIterator], colorCount);

    return maxColorValue;
}