
#include "utils.hpp"
#include "greedy.hpp"

int getNodeBestStepColor(int colorCount, float* totalColorWeights, int node, int* avaliableColors){
    int* nodeAvaliableColors = &(avaliableColors[node*colorCount]);
    int nodeBestColor = getLowestAvaliableColor(totalColorWeights, nodeAvaliableColors, colorCount);
    
    return nodeBestColor;
}

int getNodeRecolorationColor(int colorCount, int** nodeAdjacencyList, int* coloration, float* totalColorWeights, int node, int adjacentNodeQuantity){

    int bestColor = 0;
    
    int adjacentNodeColorOccurance[colorCount] = {0};

    for (int i = 0; i < adjacentNodeQuantity; i++)
    {
        int currentAdjacentNode = nodeAdjacencyList[node][i];
        int currentAdjacentNodeColor = coloration[currentAdjacentNode];
        adjacentNodeColorOccurance[currentAdjacentNodeColor]++;
    }
    for (int i = 0; i < colorCount; i++)
    {
        if (adjacentNodeColorOccurance[i] < adjacentNodeColorOccurance[bestColor])
        {
            bestColor = i;
        }
        else if (totalColorWeights[i] < totalColorWeights[bestColor])
        {
            bestColor = i;
        }
    }

    return bestColor;
}

int greedyConstruction(int nodeCount, int colorCount, int** nodeAdjacencyList, float* weights, int* coloration, float* totalColorWeights, int* adjacentNodeQuantity, int* avaliableColors){

    for (int i = 0; i < colorCount; i++)
    {
        totalColorWeights[i] = 0;
    }

    //used by greedy coloring along with adjacent node count
    int avaliableColorQuantity[nodeCount] = {colorCount};

    //priority queue ((avaliableColorQuantity, adjacentNodeCount) : node)
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, CompareNodes> orderedNodes;

    bool coloredNodes[nodeCount] = {false};
    
    int totalColoredNodes = 0;

    int returnValue = 0;

    while(totalColoredNodes < nodeCount){

        //start with a random node
        int node = UNDEFINED;
        int randomNodeIndex = rand() % (nodeCount-totalColoredNodes);

        for (int i = 0; i < nodeCount; i++)
        {
            if (randomNodeIndex == 0)
            {
                node = i;
                break;
            }
            randomNodeIndex--;
        }

        int random = rand();
        orderedNodes.push({{adjacentNodeQuantity[node], random}, node});

        //while prioroty queue is not empty
        do{
            //select one of the best non colored avaliable nodes randomly and start coloring the graph from it
            pair<pair<int, int>, int> top_item = orderedNodes.top();

            orderedNodes.pop();

            if(coloredNodes[top_item.second]){
                continue;
            }

            int node = top_item.second;

            int color = getNodeBestStepColor(colorCount, totalColorWeights, node, avaliableColors);

            if (color == UNDEFINED)
            {
                color = getNodeRecolorationColor(colorCount, nodeAdjacencyList, coloration, totalColorWeights, node, adjacentNodeQuantity[node]);
                
                int adjacentNodesNumber = adjacentNodeQuantity[node];
                for (int i = 0; i < adjacentNodesNumber; i++)
                {
                    int currentAdjacentNode = nodeAdjacencyList[node][i];
                    if (coloration[currentAdjacentNode] == color)
                    {
                        updateNodeColor(avaliableColors, coloration, nodeAdjacencyList, UNDEFINED, currentAdjacentNode, adjacentNodeQuantity[currentAdjacentNode], colorCount, totalColorWeights, weights);
                        coloredNodes[currentAdjacentNode] = false;
                        int random = rand();
                        orderedNodes.push({{adjacentNodeQuantity[currentAdjacentNode], random}, currentAdjacentNode});
                    }
                }
            }

            updateNodeColor(avaliableColors, coloration, nodeAdjacencyList, color, node, adjacentNodeQuantity[node], colorCount, totalColorWeights, weights);
            coloredNodes[node] = true;

            totalColoredNodes++;

            //add adjacent nodes to priority queue
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
        }while(!orderedNodes.empty());
        //if there are nodes left, start the process again
    }

    //check for valid coloration

    bool valid = true;

    for (int i = 0; i < nodeCount; i++)
    {
        if (coloration[i] == UNDEFINED || coloration[i] >= colorCount)
        {
            valid = false;
            break;
        }
    }

    if(!valid){
        cout << "ERROR: expected valid coloration\n";
        returnValue = UNDEFINED;
    }

    return returnValue;
}