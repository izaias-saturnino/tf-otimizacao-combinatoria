#include "neighbours.hpp"
#include "utils.hpp"

float getColorChangesValue(int* coloration, int firstNodeNewColor, int secondNodeNewColor, int firstNode, int secondNode, float* totalColorWeights, int maxColorValue, float* weights, int colorCount){

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
        }
    }
    return maxColorValue;
}

float getBestNeighbour(int nodeCount, int colorCount, int** nodeAjacencyList, float* totalColorWeights, int* coloration, float maxColorValue, float* weights, int* avaliableColors, unordered_set<pair<int, int>, TupleHash>* adjacencyHash, int* adjacentNodeQuantity){
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

    float totalColorWeightsCopy[colorCount];

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

                            {
                                int firstNodeCurrentColor = coloration[firstNodeIterator];
                                int secondNodeCurrentColor = coloration[secondNodeIterator];

                                totalColorWeightsCopy[firstNodeCurrentColor] = totalColorWeights[firstNodeCurrentColor];
                                totalColorWeightsCopy[firstNodeColorIterator] = totalColorWeights[firstNodeColorIterator];

                                totalColorWeightsCopy[secondNodeCurrentColor] = totalColorWeights[secondNodeCurrentColor];
                                totalColorWeightsCopy[secondNodeColorIterator] = totalColorWeights[secondNodeColorIterator];
                            }

                            float newValue = getColorChangesValue(coloration, firstNodeColorIterator, secondNodeColorIterator, firstNodeIterator, secondNodeIterator, totalColorWeightsCopy, maxColorValue, weights, colorCount);
                            
                            if(newValue < maxColorValue){
                                maxColorValue = newValue;

                                for(int i = 0; i < colorCount; i++){
                                    if(totalColorWeights[i] == maxColorValue){
                                        maxColor = i;
                                    }
                                }

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
        //read old colors
        int firstNodeCurrentColor = coloration[bestFirstNodeIterator];
        int secondNodeCurrentColor = coloration[bestSecondNodeIterator];

        //calculate new color weights
        totalColorWeights[firstNodeCurrentColor] = totalColorWeightsCopy[firstNodeCurrentColor];
        totalColorWeights[bestFirstNodeColorIterator] = totalColorWeightsCopy[bestFirstNodeColorIterator];

        totalColorWeights[secondNodeCurrentColor] = totalColorWeightsCopy[secondNodeCurrentColor];
        totalColorWeights[bestSecondNodeColorIterator] = totalColorWeightsCopy[bestSecondNodeColorIterator];

        //cout << "firstNode: " << bestFirstNodeIterator << ". ";
        //cout << "color: " << firstNodeCurrentColor << ". ";
        //cout << "newColor: " << bestFirstNodeColorIterator << "\n";

        //cout << "secondNode: " << bestSecondNodeIterator << ". ";
        //cout << "color: " << secondNodeCurrentColor << ". ";
        //cout << "newColor: " << bestSecondNodeColorIterator << "\n";
    }

    updateNodeColor(avaliableColors, nodeCount, coloration, nodeAjacencyList, bestFirstNodeColorIterator, bestFirstNodeIterator, adjacentNodeQuantity[bestFirstNodeIterator], colorCount, totalColorWeights, weights);
    updateNodeColor(avaliableColors, nodeCount, coloration, nodeAjacencyList, bestSecondNodeColorIterator, bestSecondNodeIterator, adjacentNodeQuantity[bestSecondNodeIterator], colorCount, totalColorWeights, weights);

    if (maxColor == UNDEFINED)
    {
        maxColorValue = numeric_limits<float>::infinity()*-1;
    }
    
    return maxColorValue;
}