//returns lowest color in terms of total weight
int getLowestColor(int* totalColorWeights, int colorCount){
    int lowestAvaliableColor = -1;
    int lowestTotalColorWeights = 0;
    for (int i = 0; i < colorCount; i++)
    {
        if(lowestAvaliableColor == -1){
            lowestAvaliableColor = i;
            lowestTotalColorWeights = totalColorWeights[i];
        }
        else if(lowestTotalColorWeights > totalColorWeights[i]){
            lowestAvaliableColor = i;
            lowestTotalColorWeights = totalColorWeights[i];
        }
    }
    return lowestAvaliableColor;
}

//returns lowest avaliable color in terms of total weight
int getLowestAvaliableColor(int* totalColorWeights, int* avaliableColors, int colorCount){
    int lowestAvaliableColor = -1;
    int lowestTotalColorWeights = 0;
    for (int i = 0; i < colorCount; i++)
    {
        if(!avaliableColors[i]){
            if(lowestAvaliableColor == -1){
                lowestAvaliableColor = i;
                lowestTotalColorWeights = totalColorWeights[i];
            }
            else if(lowestTotalColorWeights > totalColorWeights[i]){
                lowestAvaliableColor = i;
                lowestTotalColorWeights = totalColorWeights[i];
            }
        }
    }
    return lowestAvaliableColor;
}

//returns highest avaliable color in terms of total weight
int getHighestAvaliableColor(int* totalColorWeights, int* avaliableColors){
    //TODO
    //its a copy of the function above
    //only code it if its going to be used
    return 0;
}

//returns array with lowest and highest avaliable color in terms of total weight
int* getLowestAndHighestAvaliableColor(int* totalColorWeights, int* avaliableColors){
    //TODO
    //its a copy of the two functions above
    //only code it if its going to be used
    return 0;
}

//Changes the value of nodeAjancencyList to have a list of ajacent nodes for each node. Each list of ajacent nodes is terminated by -1.
void getNodesAjancencyList(int nodeCount, int colorCount, int** graph, int* weights, int* coloration, int** nodeAjacencyList, int* lastAdjacentNodePos){
    for (int i = 0; i < nodeCount; i++)
    {
        lastAdjacentNodePos[i] = 0;
    }
    for (int i = 0; i < nodeCount; i++)
    {
        int firstNode = graph[i][0];
        int secondNode = graph[i][1];

        nodeAjacencyList[firstNode][lastAdjacentNodePos[firstNode]] = secondNode;
        lastAdjacentNodePos[firstNode]++;

        nodeAjacencyList[secondNode][lastAdjacentNodePos[secondNode]] = firstNode;
        lastAdjacentNodePos[secondNode]++;
    }
    for (int i = 0; i < nodeCount; i++)
    {
        if(lastAdjacentNodePos[i] < nodeCount){
            nodeAjacencyList[i][lastAdjacentNodePos[i]] = -1;
        }
    }
}

//Changes the value of coloration to an array full of negative ones
void getEmptyColoration(int nodeCount, int* coloration){
    for(int i = 0; i < nodeCount; i++){
        coloration[i] = -1;
    }
}

//Changes the value of avaliableColors to an array with the avaliableColors. The array position is equal to the number of adjacent nodes with the same color as the array position
void getAvaliableColors(int** nodeAjacencyList, int* coloration, int nodeCount, int colorCount, int node, int* avaliableColors){
    
    for (int i = 0; i < colorCount; i++)
    {
        avaliableColors[i] = 0;
    }
    
    for(int i = 0; i < nodeCount; i++){
        for(int j = 0; j < nodeCount; j++){
            if(nodeAjacencyList[i][j] == -1){
                break;
            }
            int currentNode = nodeAjacencyList[i][j];
            int currentColor = coloration[currentNode];
            avaliableColors[currentColor]++;
        }
    }
}

int areNodesAdjacent(int firstNode, int secondNode, int** nodeAjacencyList, int nodeCount){
    int i = firstNode;
    int areAdjacent = 0;
    for(int j = 0; j < nodeCount; j++){
        int currentNode = nodeAjacencyList[i][j];
        if(currentNode == -1){
            break;
        }
        if(currentNode == secondNode){
            areAdjacent = 1;
            break;
        }
    }
    return areAdjacent;
}