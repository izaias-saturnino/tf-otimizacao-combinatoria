
#include "utils.hpp"
#include "greedy.hpp"

int getNodeBestStepColor(int nodeCount, int colorCount, int** nodeAjacencyList, float* weights, int* coloration, int* totalColorWeights, int node, int* avaliableColors){
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

int greedyConstruction(int nodeCount, int colorCount, int** nodeAjacencyList, float* weights, int* coloration, int* totalColorWeights, int* adjacentNodeQuantity, int* avaliableColors){

    for (int i = 0; i < colorCount; i++)
    {
        totalColorWeights[i] = 0;
    }

    //used by greedy coloring along with adjacent node count
    int avaliableColorQuantity[nodeCount] = {colorCount};

    //priority queue ((avaliableColorQuantity, adjacentNodeCount) : node)
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, ComparePairs> orderedNodes;

    bool coloredNodes[nodeCount] = {false};

    //add nodes to priority queue
    for (int i = 0; i < nodeCount; i++)
    {
        orderedNodes.push({{avaliableColorQuantity[i], adjacentNodeQuantity[i]}, i});
    }
    
    int totalColoredNodes = 0;

    int returnValue = 0;

    while(totalColoredNodes < nodeCount){

        int randomNodeIndex = rand() % colorCount-totalColoredNodes;

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

        int color = getNodeBestStepColor(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights, randomNode, avaliableColors);
        updateNodeColor(avaliableColors, nodeCount, coloration, nodeAjacencyList, color, randomNode, adjacentNodeQuantity[randomNode], colorCount);    
        coloredNodes[randomNode] = true;

        totalColoredNodes++;

        //while prioroty queue is not empty
        while (!orderedNodes.empty()){

            //select one of the best nodes
            pair<pair<int, int>, int> top_item = orderedNodes.top();

            while (!orderedNodes.empty() && coloredNodes[top_item.second]){
                orderedNodes.pop();
                if (coloredNodes[orderedNodes.top().second])
                {
                    top_item = orderedNodes.top();
                }
            }

            if (coloredNodes[top_item.second]){
                break;
            }

            //restart random coloration of node if a new connected component has been reached
            if(top_item.first.first == colorCount){
                break;
            }

            orderedNodes.pop();

            int node = top_item.second;

            int color = getNodeBestStepColor(nodeCount, colorCount, nodeAjacencyList, weights, coloration, totalColorWeights, node, avaliableColors);
            updateNodeColor(avaliableColors, nodeCount, coloration, nodeAjacencyList, color, node, adjacentNodeQuantity[node], colorCount);
            coloredNodes[node] = true;

            totalColoredNodes++;
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
            printf("ERROR: expected valid coloration");
            break;
        }
    }

    return returnValue;
}