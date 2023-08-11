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

float getBestNeighbour(int nodeCount, int colorCount, int** nodeAjacencyList, float* totalColorWeights, int* coloration, float maxColorValue, float* weights, int* avaliableColors, unordered_set<pair<int, int>, TupleHash>* adjacencyHash, int* adjacentNodeQuantity, int& firstNode, int& secondNode, int& firstColor, int& secondColor){

    if(colorCount == 1){
        return maxColorValue;
    }
    if(nodeCount < 3){
        return maxColorValue;
    }

    bool maxColorValueInit = false;

    int bestFirstNodeIterator = 0;
    int bestSecondNodeIterator = 1;

    int bestFirstNodeColorIterator = 0;
    int bestSecondNodeColorIterator = 1;

    float totalColorWeightsCopy[colorCount];

    //cout << "getBestNeighbour\n";

    for(int firstNodeIterator = 0; firstNodeIterator < nodeCount; firstNodeIterator++){
        int* firstNodeAvaliableColors = &(avaliableColors[firstNodeIterator*colorCount]);
        for(int secondNodeIterator = 0; secondNodeIterator < nodeCount; secondNodeIterator++){
            //cout << "start\n";
            //cout << "firstNodeIterator: " << firstNodeIterator << ". ";
            //cout << "secondNodeIterator: " << secondNodeIterator << "\n";
            if (firstNodeIterator == secondNodeIterator)
            {
                continue;
            }

            int* secondNodeAvaliableColors = &(avaliableColors[secondNodeIterator*colorCount]);
            
            auto pair = make_pair(firstNodeIterator,secondNodeIterator);
            bool nodes_adjacent = (*adjacencyHash).find(pair) != (*adjacencyHash).end();
            
            for(int firstNodeColorIterator = 0; firstNodeColorIterator < colorCount; firstNodeColorIterator++){
                for(int secondNodeColorIterator = 0; secondNodeColorIterator < colorCount; secondNodeColorIterator++){
                    
                    bool extraColorFirstNode = firstNodeAvaliableColors[firstNodeColorIterator] == 1 && coloration[secondNodeIterator] == firstNodeColorIterator && nodes_adjacent;
                    bool extraColorSecondNode = secondNodeAvaliableColors[secondNodeColorIterator] == 1 && coloration[firstNodeIterator] == secondNodeColorIterator && nodes_adjacent;

                    if(firstNodeAvaliableColors[firstNodeColorIterator] == 0 || extraColorFirstNode){
                        if(secondNodeAvaliableColors[secondNodeColorIterator] == 0 || extraColorSecondNode){

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

                                //cout << "maxColorValue: " << maxColorValue << ". ";
                                //cout << "newValue: " << newValue << "\n";

                                maxColorValue = newValue;
                                maxColorValueInit = true;

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

        firstNode = bestFirstNodeIterator;
        firstColor = bestFirstNodeColorIterator;
        secondNode = bestSecondNodeIterator;
        secondNode = bestSecondNodeColorIterator;

        cout << "firstNode: " << bestFirstNodeIterator << ". ";
        cout << "color: " << firstNodeCurrentColor << ". ";
        cout << "newColor: " << bestFirstNodeColorIterator << "\n";

        cout << "secondNode: " << bestSecondNodeIterator << ". ";
        cout << "color: " << secondNodeCurrentColor << ". ";
        cout << "newColor: " << bestSecondNodeColorIterator << "\n";
    }

    if (maxColorValueInit)
    {
        updateNodeColor(avaliableColors, coloration, nodeAjacencyList, bestFirstNodeColorIterator, bestFirstNodeIterator, adjacentNodeQuantity[bestFirstNodeIterator], colorCount, totalColorWeights, weights);
        updateNodeColor(avaliableColors, coloration, nodeAjacencyList, bestSecondNodeColorIterator, bestSecondNodeIterator, adjacentNodeQuantity[bestSecondNodeIterator], colorCount, totalColorWeights, weights);
    }

    cout << "new maxColorValue: " << maxColorValue << "\n";

    return maxColorValue;
}