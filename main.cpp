#include "utils.hpp"
#include "grasp.hpp"

int main(int argc, char* argv[]) {

    float max_time = 60.0f;

    float max_greedy_time = max_time/10;

    srand(time(NULL));

    if (argc < 5){
        cout << "Usage:\n";
        cout << "./cmb <filename> <total_timeout> <seed> <initial_solution_timeout>\n";
        cout << "Where total_timeout and initial_solution_timeout are real numbers and seed is an integer\n";
        cout << "\n";
    }
    if (argc < 2){
        cout << "File name not provided\n";
    }
    if (argc < 3){
        cout << "Max time in seconds not provided. Running for 60 seconds.\n";
    }
    else{
        max_time = atof(argv[2]);
    }
    if (argc < 4){
        cout << "Seed not provided. Using time as default seed.\n";
    }
    else{
        srand(atoi(argv[3]));
    }
    if (argc < 5){
        cout << "Max greedy time in seconds not provided. Running greedy construction with total_timeout/10 seconds.\n";
    }
    else{
        max_greedy_time = atof(argv[4]);
    }


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
    unordered_set<pair<int, int>, TupleHash> adjacencyHash(initialCapacity);

    //creaating list for edges
    int adjacentNodeListLength[nodeCount] = {0};
    int adjacentNodeListInitCounter[nodeCount] = {0};
    int* nodeAjacencyList[nodeCount];

    //reading edges
    {
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

            adjacencyHash.insert(make_pair(firstNode, secondNode));
            adjacencyHash.insert(make_pair(secondNode, firstNode));

            //filling the nodeAjacencyList with the edges
            nodeAjacencyList[firstNode][adjacentNodeListInitCounter[firstNode]] = secondNode;
            adjacentNodeListInitCounter[firstNode]++;

            nodeAjacencyList[secondNode][adjacentNodeListInitCounter[secondNode]] = firstNode;
            adjacentNodeListInitCounter[secondNode]++;
        }
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

    while(maxValue != minimal_possible_max_value){

        //clear currentColorationPointer to reuse in GRASP
        for (int i = 0; i < nodeCount; i++)
        {
            currentColorationPointer[i] = UNDEFINED;
        }

        t_diff = clock() - t0;
        float time_taken = ((float)t_diff)/CLOCKS_PER_SEC;

        cout << "time taken for GRASP iteration in seconds: " << time_taken << "\n";

        if(time_taken > max_time){
            cout << "timeout\n";
            break;
        }

        float newMaxValue = grasp(nodeCount, colorCount, nodeAjacencyList, weights, currentColorationPointer, adjacentNodeListLength, &adjacencyHash, t0, max_time, max_greedy_time/*, &edges[0][0], edgeCount*/);

        //check if solution is valid

        //check for full coloration
        //bool full = true;

        //for (int i = 0; i < nodeCount; i++)
        //{
        //    if (currentColorationPointer[i] == UNDEFINED || currentColorationPointer[i] >= colorCount)
        //    {
        //        full = false;
        //        cout << "ERROR: coloration[" << i << "] is UNDEFINED\n";
        //    }
        //}

        //if(!full){
        //    cout << "ERROR: expected full coloration\n";
        //}
        //end of check for full coloration

        //bool satisfies = true;
        //for (int i = 0; i < edgeCount; i++)
        //{
        //    int firstNode = edges[i][0];
        //    int secondNode = edges[i][1];
        //    if (currentColorationPointer[firstNode] == currentColorationPointer[secondNode])
        //    {
        //        satisfies = false;
        //        cout << "ERROR: node " << firstNode << " has the same color as node " << secondNode << " and both nodes are adjacent\n";
        //    }
        //}

        //if (!satisfies)
        //{
        //    cout << "ERROR: coloration does not satisfy restrictions\n";
        //}
        //end of solution verification

        cout << "newMaxValue: " << newMaxValue <<"\n";

        if(newMaxValue < maxValue){
            cout << "bestMaxValue: " << newMaxValue <<"\n";
            maxValue = newMaxValue;
            int* maxColorationPointerCopy = maxColorationPointer;
            maxColorationPointer = currentColorationPointer;
            currentColorationPointer = maxColorationPointerCopy;
        }
    }

    if (argc >= 2)
    {
        std::string filename = argv[1];
        std::ofstream outputFile(filename);
        outputFile << "finalMaxValue: " << maxValue <<"\n";
        outputFile << "coloration:\n";
        for (int i = 0; i < nodeCount; i++)
        {
            outputFile << maxColorationPointer[i] << " ";
        }
        outputFile.close();
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
