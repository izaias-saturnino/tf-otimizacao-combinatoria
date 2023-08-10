#include "neighbours.hpp"
#include "utils.hpp"

float getColorChangesValue(int* coloration, int firstNodeNewColor, int secondNodeNewColor, int firstNode, int secondNode, float* totalColorWeights, float* weights, int colorCount){

    int firstNodeCurrentColor = coloration[firstNode];
    int secondNodeCurrentColor = coloration[secondNode];

    totalColorWeights[firstNodeCurrentColor] -= weights[firstNode];
    totalColorWeights[firstNodeNewColor] += weights[firstNode];

    totalColorWeights[secondNodeCurrentColor] -= weights[secondNode];
    totalColorWeights[secondNodeNewColor] += weights[secondNode];

    float maxColorValue = totalColorWeights[0];

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

    int bestFirstNodeIterator = 0;
    int bestSecondNodeIterator = 1;

    int bestFirstNodeColorIterator = 0;
    int bestSecondNodeColorIterator = 1;

    float totalColorWeightsCopy[colorCount];

    //cout << "getBestNeighbour\n";

    for(int firstNodeIterator = 0; firstNodeIterator < nodeCount; firstNodeIterator++){
        int* firstNodeAvaliableColors = &avaliableColors[firstNodeIterator*colorCount];
        for(int secondNodeIterator = 0; secondNodeIterator < nodeCount; secondNodeIterator++){
            //cout << "start\n";
            //cout << "firstNodeIterator: " << firstNodeIterator << ". ";
            //cout << "secondNodeIterator: " << secondNodeIterator << "\n";
            if (firstNodeIterator == secondNodeIterator)
            {
                continue;
            }

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

                            for(int i = 0; i < colorCount; i++){
                                totalColorWeightsCopy[i] = totalColorWeights[i];
                            }

                            float newValue = getColorChangesValue(coloration, firstNodeColorIterator, secondNodeColorIterator, firstNodeIterator, secondNodeIterator, totalColorWeightsCopy, weights, colorCount);

                            //cout << "getColorChangesValue\n";
                            //cout << "firstNodeIterator: " << firstNodeIterator << ". ";
                            //cout << "secondNodeIterator: " << secondNodeIterator << ". ";
                            //cout << "firstNodeColorIterator: " << firstNodeColorIterator << ". ";
                            //cout << "secondNodeColorIterator: " << secondNodeColorIterator << "\n";
                            
                            if(newValue < maxColorValue){
                                maxColorValue = newValue;

                                //cout << "update\n";

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
        totalColorWeights[firstNodeCurrentColor] -= weights[bestFirstNodeIterator];
        totalColorWeights[bestFirstNodeColorIterator] += weights[bestFirstNodeIterator];

        totalColorWeights[secondNodeCurrentColor] -= weights[bestSecondNodeIterator];
        totalColorWeights[bestSecondNodeColorIterator] += weights[bestSecondNodeIterator];

        //cout << "firstNode: " << bestFirstNodeIterator << ". ";
        //cout << "color: " << firstNodeCurrentColor << ". ";
        //cout << "newColor: " << bestFirstNodeColorIterator << "\n";

        //cout << "secondNode: " << bestSecondNodeIterator << ". ";
        //cout << "color: " << secondNodeCurrentColor << ". ";
        //cout << "newColor: " << bestSecondNodeColorIterator << "\n";
    }

    updateNodeColor(avaliableColors, nodeCount, coloration, nodeAjacencyList, bestFirstNodeColorIterator, bestFirstNodeIterator, adjacentNodeQuantity[bestFirstNodeIterator], colorCount, totalColorWeights, weights);
    updateNodeColor(avaliableColors, nodeCount, coloration, nodeAjacencyList, bestSecondNodeColorIterator, bestSecondNodeIterator, adjacentNodeQuantity[bestSecondNodeIterator], colorCount, totalColorWeights, weights);

    return maxColorValue;
}