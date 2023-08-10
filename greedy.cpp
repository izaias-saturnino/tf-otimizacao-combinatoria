
#include "utils.hpp"
#include "greedy.hpp"

int getNodeBestStepColor(int nodeCount, int colorCount, int** nodeAdjacencyList, float* weights, int* coloration, float* totalColorWeights, int node, int* avaliableColors){
    if(coloration[node] != UNDEFINED){
        return coloration[node];
    }
    int* nodeAvaliableColors = &avaliableColors[node*colorCount];
    int nodeBestColor = getLowestAvaliableColor(totalColorWeights, nodeAvaliableColors, colorCount);

    if (nodeBestColor == UNDEFINED)
    {
        //recolor until the graph is consistent following some heuristic
    }
    
    return nodeBestColor;
}

int greedyConstruction(int nodeCount, int colorCount, int** nodeAdjacencyList, float* weights, int* coloration, float* totalColorWeights, int* adjacentNodeQuantity, int* avaliableColors){

    cout << "start of greedyConstruction\n";

    for (int i = 0; i < colorCount; i++)
    {
        totalColorWeights[i] = 0;
    }

    //used by greedy coloring along with adjacent node count
    int avaliableColorQuantity[nodeCount] = {colorCount};

    //priority queue ((avaliableColorQuantity, adjacentNodeCount) : node)
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, ComparePairs> orderedNodes;

    bool coloredNodes[nodeCount] = {false};
    
    int totalColoredNodes = 0;

    int returnValue = 0;

    while(totalColoredNodes < nodeCount){

        int randomNodeIndex = rand() % (nodeCount-totalColoredNodes);

        int randomNode = UNDEFINED;

        for (int i = 0; i < nodeCount; i++)
        {
            if (randomNodeIndex == 0)
            {
                randomNode = i;
                break;
            }
            randomNodeIndex--;
        }

        int color = getNodeBestStepColor(nodeCount, colorCount, nodeAdjacencyList, weights, coloration, totalColorWeights, randomNode, avaliableColors);
        updateNodeColor(avaliableColors, nodeCount, coloration, nodeAdjacencyList, color, randomNode, adjacentNodeQuantity[randomNode], colorCount);    
        coloredNodes[randomNode] = true;

        totalColoredNodes++;

        //add nodes to priority queue
        int adjacentNodesNumber = adjacentNodeQuantity[randomNode];
        for (int i = 0; i < adjacentNodesNumber; i++)
        {
            int currentAdjacentNode = nodeAdjacencyList[randomNode][i];
            if (coloredNodes[currentAdjacentNode]){
                continue;
            }
            int random = rand();
            orderedNodes.push({{adjacentNodeQuantity[currentAdjacentNode], random}, currentAdjacentNode});
        }

        //while prioroty queue is not empty
        while (!orderedNodes.empty()){

            //select one of the best nodes
            pair<pair<int, int>, int> top_item = orderedNodes.top();

            if(coloredNodes[top_item.second]){
                continue;
            }

            orderedNodes.pop();

            int node = top_item.second;

            int color = getNodeBestStepColor(nodeCount, colorCount, nodeAdjacencyList, weights, coloration, totalColorWeights, node, avaliableColors);
            updateNodeColor(avaliableColors, nodeCount, coloration, nodeAdjacencyList, color, node, adjacentNodeQuantity[node], colorCount);
            coloredNodes[node] = true;

            totalColoredNodes++;

            //add nodes to priority queue
            int adjacentNodesNumber = adjacentNodeQuantity[node];
            for (int i = 0; i < adjacentNodesNumber; i++)
            {
                int currentAdjacentNode = nodeAdjacencyList[node][i];
                if (coloredNodes[currentAdjacentNode]){
                    continue;
                }
                int random = rand();
                orderedNodes.push({{adjacentNodeQuantity[currentAdjacentNode], random}, currentAdjacentNode});
            }
        }
    }

    //check for valid coloration

    bool valid = false;

    while (!valid)
    {
        valid = true;

        int startNode = UNDEFINED;

        for (int i = 0; i < nodeCount; i++)
        {
            if (coloration[i] == UNDEFINED || coloration[i] >= colorCount)
            {
                valid = false;
                startNode = i;
                break;
            }
        }
        if (valid)
        {
            break;
        }
        else{
            //recolor starting from startNode

            //remove this error code and the break if using the recoloration above
            //printf("ERROR: expected valid coloration\n");
            break;
        }
    }

    cout << "end of greedyConstruction\n";

    return returnValue;
}