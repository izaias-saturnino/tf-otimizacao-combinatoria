#include "utils.hpp"
#include "grasp.hpp"

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

    //creating hash for edges
    const size_t expectedNumElements = edgeCount*2; // Set your expected number of elements

    // Calculate an appropriate initial capacity based on expectedNumElements
    const size_t initialCapacity = max(static_cast<size_t>(expectedNumElements / 0.7), static_cast<size_t>(10));

    // An unordered_set with custom hash function and initial capacity
    unordered_set<unsigned long long> adjacencyHash(initialCapacity);

    //creaating list for edges
    int adjacentNodeListLength[nodeCount] = {0};
    int adjacentNodeListInitCounter[nodeCount] = {0};
    int* nodeAjacencyList[nodeCount];

    //reading edges
    int edges[edgeCount][2];

    for (int i = 0; i < edgeCount; i++){
        int firstNode;
        int secondNode;
        scanf("%d", &firstNode);
        scanf("%d", &secondNode);

        edges[i][0] = firstNode;
        edges[i][1] = secondNode;

        //updating edges number for each node
        adjacentNodeListLength[firstNode]++;
        adjacentNodeListLength[secondNode]++;
    }

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

        long firstPair = ((unsigned long long) firstNode) || (((unsigned long long) secondNode) << 16);
        long secondPair = ((unsigned long long) secondNode) || (((unsigned long long) firstNode) << 16);

        adjacencyHash.insert(firstPair);
        adjacencyHash.insert(secondPair);

        //filling the nodeAjacencyList with the edges
        nodeAjacencyList[firstNode][adjacentNodeListInitCounter[firstNode]] = secondNode;
        adjacentNodeListInitCounter[firstNode]++;

        nodeAjacencyList[secondNode][adjacentNodeListInitCounter[secondNode]] = firstNode;
        adjacentNodeListInitCounter[secondNode]++;
    }
    //finish reading instance

    int maxColoration[nodeCount] = {UNDEFINED};

    int currentColoration[nodeCount];
    int* maxColorationPointer = maxColoration;
    int* currentColorationPointer = currentColoration;

    clock_t t0, t_diff;
    t0 = clock();

    bool timeout = false;

    float maxValue = numeric_limits<float>::infinity();
    float newMaxValue;

    srand(time(NULL));

    while(maxValue != minimal_possible_max_value){

        //clear currentColorationPointer to reuse in GRASP
        for (int i = 0; i < nodeCount; i++)
        {
            currentColorationPointer[i] = UNDEFINED;
        }

        t_diff = clock() - t0;
        double time_taken = ((double)t_diff)/CLOCKS_PER_SEC;

        cout << "time in seconds: " << time_taken << "\n";

        if(time_taken > TIMEOUT){
            cout << "timeout\n";
            break;
        }

        float newMaxValue = grasp(nodeCount, colorCount, nodeAjacencyList, weights, currentColorationPointer, adjacentNodeListLength, &adjacencyHash, t0);

        cout << "newMaxValue: " << newMaxValue <<"\n";

        if(newMaxValue < maxValue){
            cout << "bestMaxValue: " << newMaxValue <<"\n";
            maxValue = newMaxValue;
            int* maxColorationPointerCopy = maxColorationPointer;
            maxColorationPointer = currentColorationPointer;
            currentColorationPointer = maxColorationPointerCopy;
        }
    }

    cout << "finalMaxValue: " << maxValue <<"\n";

    cout << "final coloration:\n";
    for (int i = 0; i < nodeCount; i++)
    {
        cout << maxColorationPointer[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
