
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

int greedyConstruction(int nodeCount, int colorCount, int** nodeAdjacencyList, float* weights, int* coloration, float* totalColorWeights, int* adjacentNodeQuantity, int* avaliableColors, clock_t t0, float max_time){

    for (int i = 0; i < colorCount; i++)
    {
        totalColorWeights[i] = 0;
    }

    //priority queue ((adjacentNodeCount, random) : node)
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, CompareNodes> orderedNodes;
    bool inOrderedNodes[nodeCount] = {false};

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
        if (!inOrderedNodes[node])
        {
            int random = rand();
            orderedNodes.push({{adjacentNodeQuantity[node], random}, node});
            inOrderedNodes[node] = true;
        }

        //while prioroty queue is not empty
        do{
            clock_t t_diff = clock() - t0;
            float time_taken = ((float)t_diff)/CLOCKS_PER_SEC;

            if(time_taken > max_time){
                return UNDEFINED;
            }

            //select one of the best non colored avaliable nodes randomly and start coloring the graph from it
            pair<pair<int, int>, int> top_item = orderedNodes.top();

            orderedNodes.pop();

            if(coloredNodes[top_item.second]){
                inOrderedNodes[node] = false;
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
                        if (!inOrderedNodes[currentAdjacentNode])
                        {
                            int random = rand();
                            orderedNodes.push({{adjacentNodeQuantity[currentAdjacentNode], random}, currentAdjacentNode});
                            inOrderedNodes[currentAdjacentNode] = true;
                        }
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
                if (!inOrderedNodes[currentAdjacentNode])
                {
                    int random = rand();
                    orderedNodes.push({{adjacentNodeQuantity[currentAdjacentNode], random}, currentAdjacentNode});
                    inOrderedNodes[currentAdjacentNode] = true;
                }
            }

            //cout << "coloration:\n";

            //for (int i = 0; i < nodeCount; i++)
            //{
                //cout << coloration[i] << " ";
            //}

            //cout << "\n";
            
            inOrderedNodes[node] = false;
        }while(!orderedNodes.empty());
        //if there are nodes left, start the process again
    }

    //check for full coloration
    //bool valid = true;

    //for (int i = 0; i < nodeCount; i++)
    //{
    //    if (coloration[i] == UNDEFINED || coloration[i] >= colorCount)
    //    {
    //        valid = false;
    //        cout << "ERROR: coloration[" << i << "] is UNDEFINED\n";
    //    }
    //}

    //if(!valid){
    //    cout << "ERROR: expected full coloration\n";
    //    returnValue = UNDEFINED;
    //}
    //end of check for full coloration

    return returnValue;
}