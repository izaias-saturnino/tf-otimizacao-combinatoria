#include "utils.hpp"
#include "neighbours.hpp"

int main() {
    //read instance
    int nodeCount = 0;
    int edgeCount = 0;
    int colorCount = 0;
    float minimal_possible_max_value = numeric_limits<float>::infinity()*-1;

    scanf("%d", &nodeCount);
    scanf("%d", &edgeCount);
    scanf("%d", &colorCount);

    float weights[nodeCount];

    //reading weights
    for(int i = 0; i < nodeCount; i++){
        scanf("%f", &weights[i]);
        if (minimal_possible_max_value < weights[i])
        {
            minimal_possible_max_value = weights[i];
        }
    }

    //reading edges
    int edges[edgeCount][2];

    int adjacentNodeListLength[nodeCount];
    int adjacentNodeListInitCounter[nodeCount];
    int* nodeAjacencyList[nodeCount];

    for (int i = 0; i < edgeCount; i++){
        int firstNode;
        int secondNode;
        scanf("%d", &firstNode);
        scanf("%d", &secondNode);

        edges[i][0] = firstNode;
        edges[i][1] = secondNode;

        adjacentNodeListLength[firstNode]++;
        adjacentNodeListLength[secondNode]++;
    }

    //creating hash for edges
    const size_t expectedNumElements = edgeCount*2; // Set your expected number of elements

    // Calculate an appropriate initial capacity based on expectedNumElements
    const size_t initialCapacity = max(static_cast<size_t>(expectedNumElements / 0.7), static_cast<size_t>(10));

    // An unordered_set with custom hash function and initial capacity
    unordered_set<pair<int, int>, TupleHash> adjacencyHash(initialCapacity);

    //creating array for each node to fill the nodeAjacencyLists with the adjacent nodes numbers
    for (int i = 0; i < nodeCount; i++)
    {
        int nodeListLength = adjacentNodeListLength[i];
        nodeAjacencyList[i] = new int[nodeListLength];
    }

    //filling the hash with the edges
    for (int i = 0; i < edgeCount; i++)
    {
        int firstNode = edges[i][0];
        int secondNode = edges[i][1];

        adjacencyHash.insert(make_pair(firstNode, secondNode));
        adjacencyHash.insert(make_pair(secondNode, firstNode));

        //filling the nodeAjacencyList with the edges
        nodeAjacencyList[firstNode][adjacentNodeListInitCounter[firstNode]] = secondNode;
        adjacentNodeListInitCounter[firstNode]++;

        nodeAjacencyList[secondNode][adjacentNodeListInitCounter[secondNode]] = firstNode;
        adjacentNodeListInitCounter[secondNode]++;
    }

    float totalColorWeights[colorCount] = {0.0};
    int coloration[nodeCount] = {UNDEFINED};

    int avaliableColors[nodeCount][colorCount];

    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < colorCount; j++)
        {
            avaliableColors[i][j] = 0;
        }
    }
    
    for (int i = 0; i < nodeCount; i++)
    {
        scanf("%d", &coloration[i]);
        totalColorWeights[coloration[i]] += weights[i];
        int adjacentNodeCount = adjacentNodeListLength[i];
        for (int j = 0; j < adjacentNodeCount; j++)
        {
            int currentAdjacentNode = nodeAjacencyList[i][j];
            avaliableColors[currentAdjacentNode][coloration[i]]++;
        }
    }

    clock_t t0 = clock();

    int colorationCopy[nodeCount];
    float totalColorWeightsCopy[colorCount];

    float maxValue = totalColorWeights[0];

    for (int i = 0; i < colorCount; i++)
    {
        if (maxValue < totalColorWeights[i])
        {
            maxValue = totalColorWeights[i];
        }
        
    }

    float oldMaxValue = maxValue;

    int firstNode, secondNode, firstColor, secondColor = UNDEFINED;
    
    do{
        clock_t t_diff = clock() - t0;
        float time_taken = ((float)t_diff)/CLOCKS_PER_SEC;

        if(time_taken > TIMEOUT){
            break;
        }

        //cout << "neighbourhood search iteration\n";

        for (int i = 0; i < nodeCount; i++)
        {
            colorationCopy[i] = coloration[i];
        }

        for (int i = 0; i < colorCount; i++)
        {
            totalColorWeightsCopy[i] = totalColorWeights[i];
        }
        
        oldMaxValue = maxValue;
        maxValue = getBestNeighbour(nodeCount, colorCount, nodeAjacencyList, totalColorWeights, coloration, oldMaxValue, weights, &avaliableColors[0][0], &adjacencyHash, adjacentNodeListLength, firstNode, secondNode, firstColor, secondColor);
        
        //printVectorAsMatrix(&avaliableColors[0][0], nodeCount, colorCount);

        if (maxValue < oldMaxValue)
        {
            for (int i = 0; i < nodeCount; i++)
            {
                //cout << "node: " << i << ". color: " << coloration[i] << "\n";
            }
        }

    } while (maxValue < oldMaxValue);
    
    return 0;
}