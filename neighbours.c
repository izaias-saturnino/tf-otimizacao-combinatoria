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
}

//Changes the values of firstNode, secondNode, firstColor, secondColor to the values of the best neighbour for the current graph. Returns the new maxColorValue
int getBestNeighbour(int nodeCount, int colorCount, int** nodeAjacencyList, int* totalColorWeights, int* coloration, int maxColorValue, int* weights, int* firstNode, int* secondNode, int* firstColor, int* secondColor){
    if(colorCount < 3){
        return;
    }
    if(nodeCount < 3){
        return;
    }
    *firstNode = 0;
    *secondNode = 1;
    *firstColor = 0;
    *secondColor = 1;
    int maxColor = -1;
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
                            if(firstNodeColorIterator != maxColor && secondNodeColorIterator != maxColor && maxColor != -1){
                                continue;
                            }
                            int newMaxColor = -1;
                            int newValue = getColorChangesValue(coloration, firstNodeColorIterator, secondNodeColorIterator, firstNodeIterator, secondNodeIterator, totalColorWeights, maxColorValue, weights, colorCount, newMaxColor);
                            if(newValue < maxColorValue){
                                *firstNode = firstNodeIterator;
                                *secondNode = secondNodeIterator;
                                *firstColor = firstNodeColorIterator;
                                *secondColor = secondNodeColorIterator;
                                maxColorValue = newValue;
                                maxColor = newMaxColor;
                            }
                        }
                    }
                }
            }
        }
    }
    return maxColorValue;
}