
#include "utils.hpp"
#include "greedy.hpp"

int getNodeBestStepColor(int colorCount, float* totalColorWeights, int node, int* avaliableColors){
    int* nodeAvaliableColors = &(avaliableColors[node*colorCount]);
    int nodeBestColor = getLowestAvaliableColor(totalColorWeights, nodeAvaliableColors, colorCount);
    
    return nodeBestColor;
}

int getNodeRecolorationColor(int colorCount, int** nodeAdjacencyList, int* coloration, float* totalColorWeights, int node, int adjacentNodeQuantity, int* recolorationCount){

    int bestColor = 0;
    
    int adjacentNodeColorOccurance[colorCount] = {0};

    recolorationCount[node*colorCount + coloration[node]]++;

    for (int i = 0; i < adjacentNodeQuantity; i++)
    {
        int currentAdjacentNode = nodeAdjacencyList[node][i];
        int currentAdjacentNodeColor = coloration[currentAdjacentNode];
        adjacentNodeColorOccurance[currentAdjacentNodeColor]++;
    }
    for (int i = 0; i < colorCount; i++)
    {
        if (recolorationCount[node*colorCount + i] < recolorationCount[node*colorCount + bestColor])
        {
            bestColor = i;
        }
        else if (recolorationCount[node*colorCount + i] == recolorationCount[node*colorCount + bestColor])
        {
            if (adjacentNodeColorOccurance[i] < adjacentNodeColorOccurance[bestColor])
            {
                bestColor = i;
            }
            else if (adjacentNodeColorOccurance[i] == adjacentNodeColorOccurance[bestColor])
            {
                int random = rand() % colorCount;
                if (random == 0)
                {
                    bestColor = i;
                }
            }
        }
    }

    return bestColor;
}

int greedyConstruction(int nodeCount, int colorCount, int** nodeAdjacencyList, float* weights, int* coloration, float* totalColorWeights, int* adjacentNodeQuantity, int* avaliableColors, clock_t t0){

    for (int i = 0; i < colorCount; i++)
    {
        totalColorWeights[i] = 0;
    }

    //used by greedy coloring along with adjacent node count
    int avaliableColorQuantity[nodeCount] = {colorCount};

    //priority queue ((adjacentNodeCount, random) : node)
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, CompareNodes> orderedNodes;

    bool coloredNodes[nodeCount] = {false};
    
    int totalColoredNodes = 0;

    int returnValue = 0;

    int recolorationCountMatrix[nodeCount][colorCount] = {0};
    int* recolorationCount = &(recolorationCountMatrix[0][0]);

    while(totalColoredNodes < nodeCount){

        //start with a random node
        int node = UNDEFINED;
        int randomNodeIndex = rand() % (nodeCount-totalColoredNodes);

        for (int i = 0; i < nodeCount; i++)
        {
            if (coloredNodes[i] == false)
            {
                if (randomNodeIndex == 0)
                {
                    node = i;
                    break;
                }
                randomNodeIndex--;
            }
        }
        
        //old
        //cout << "random node pos: " << node << "\n";

        //TODO change random for weights[node] to see if there are better results
        int random = rand();
        orderedNodes.push({{adjacentNodeQuantity[node], random}, node});

        //while prioroty queue is not empty
        do{
            clock_t t_diff = clock() - t0;
            double time_taken = ((double)t_diff)/CLOCKS_PER_SEC;

            if(time_taken > TIMEOUT){
                return UNDEFINED;
            }

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
                //cout << "node recoloration\n";
                color = getNodeRecolorationColor(colorCount, nodeAdjacencyList, coloration, totalColorWeights, node, adjacentNodeQuantity[node], recolorationCount);
                
                int adjacentNodesNumber = adjacentNodeQuantity[node];
                for (int i = 0; i < adjacentNodesNumber; i++)
                {
                    int currentAdjacentNode = nodeAdjacencyList[node][i];
                    if (coloration[currentAdjacentNode] == color)
                    {
                        updateNodeColor(avaliableColors, coloration, nodeAdjacencyList, UNDEFINED, currentAdjacentNode, adjacentNodeQuantity[currentAdjacentNode], colorCount, totalColorWeights, weights, totalColoredNodes, coloredNodes);
                        //TODO change random for weights[node] to see if there are better results
                        int random = rand();
                        orderedNodes.push({{adjacentNodeQuantity[currentAdjacentNode], random}, currentAdjacentNode});
                    }
                }
            }

            updateNodeColor(avaliableColors, coloration, nodeAdjacencyList, color, node, adjacentNodeQuantity[node], colorCount, totalColorWeights, weights, totalColoredNodes, coloredNodes);

            //add adjacent nodes to priority queue
            int adjacentNodesNumber = adjacentNodeQuantity[node];
            for (int i = 0; i < adjacentNodesNumber; i++)
            {
                int currentAdjacentNode = nodeAdjacencyList[node][i];
                if (coloredNodes[currentAdjacentNode]){
                    continue;
                }
                //TODO change random for weights[node] to see if there are better results
                int random = rand();
                orderedNodes.push({{adjacentNodeQuantity[currentAdjacentNode], random}, currentAdjacentNode});
            }

            //cout << "coloration:\n";

            for (int i = 0; i < nodeCount; i++)
            {
                //cout << coloration[i] << " ";
            }

            //cout << "\n";
            

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