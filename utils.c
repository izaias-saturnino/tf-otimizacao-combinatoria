//Changes the value of nodeAjancencyList to have a list of ajacent nodes for each node. Each list of ajacent nodes is terminated by -1.
void getNodesAjancencyList(int nodeCount, int colorCount, int** graph, int* weights, int* coloration, int** nodeAjacencyList){
    int lastAdjacentNodePos[nodeCount];
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

//Changes the value of avaliableColors to an array with the avaliableColors. The array position is one when the color is avaliable and 0 if its not
void getAvaliableColors(int** nodeAjacencyList, int* coloration, int nodeCount, int colorCount, int node, int* avaliableColors){
    for (int i = 0; i < colorCount; i++)
    {
        avaliableColors[i] = 1;
    }
    
    for(int i = 0; i < nodeCount; i++){
        for(int j = 0; j < nodeCount; j++){
            if(nodeAjacencyList[i][j] == -1){
                break;
            }
            int currentColor = coloration[nodeAjacencyList[i][j]];
            avaliableColors[currentColor] = 0;
        }
    }
}

int isColorAvaliable(int** nodeAjacencyList, int* coloration, int nodeCount, int colorCount, int node, int color){
    int avaliableColors[colorCount];
    
    for (int i = 0; i < colorCount; i++)
    {
        avaliableColors[i] = 1;
    }
    
    for(int i = 0; i < nodeCount; i++){
        for(int j = 0; j < nodeCount; j++){
            if(nodeAjacencyList[i][j] == -1){
                break;
            }
            int currentColor = coloration[nodeAjacencyList[i][j]];
            avaliableColors[currentColor] = 0;
            if(currentColor == color){
                break;
            }
        }
    }
    return avaliableColors[color];
}