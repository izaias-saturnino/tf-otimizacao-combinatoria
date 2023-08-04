//Returns the new max color value based on the old values.
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

//Changes the values of firstNode, secondNode, firstColor, secondColor to the values of the best neighbour for the current graph. Returns the new maxColorValue
int getBestNeighbour(int nodeCount, int colorCount, int** nodeAjacencyList, int* totalColorWeights, int* coloration, int maxColorValue, int* weights, int* firstNode, int* secondNode, int* firstColor, int* secondColor, int* maxColor){
    if(colorCount == 1){
        return maxColorValue;
    }
    if(nodeCount < 3){
        return maxColorValue;
    }
    *firstNode = 0;
    *secondNode = 1;
    *firstColor = 0;
    *secondColor = 1;
    *maxColor = -1;

    int bestFirstNodeIterator = -1;
    int bestSecondNodeIterator = -1;
    int bestFirstNodeColorIterator = -1;
    int bestSecondNodeColorIterator = -1;

    int totalColorWeightsCopy[colorCount];

    for(int firstNodeIterator = 0; firstNodeIterator < nodeCount; firstNodeIterator++){
        int firstNodeAvaliableColors[colorCount];
        getAvaliableColors(nodeAjacencyList, coloration, nodeCount, colorCount, firstNodeIterator, firstNodeAvaliableColors);
        for(int secondNodeIterator = 0; secondNodeIterator < nodeCount; secondNodeIterator++){
            int secondNodeAvaliableColors[colorCount];
            getAvaliableColors(nodeAjacencyList, coloration, nodeCount, colorCount, secondNodeIterator, secondNodeAvaliableColors);
            
            int nodes_adjacent = areNodesAdjacent(firstNodeIterator, secondNodeIterator);
            
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
                            if(firstNodeColorIterator != maxColorCopy && secondNodeColorIterator != maxColorCopy && maxColorCopy != -1){
                                continue;
                            }
                            int newMaxColor = -1;

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
                                *firstNode = firstNodeIterator;
                                *secondNode = secondNodeIterator;
                                *firstColor = firstNodeColorIterator;
                                *secondColor = secondNodeColorIterator;
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

    return maxColorValue;
}