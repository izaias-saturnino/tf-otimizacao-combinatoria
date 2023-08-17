#include "utils.hpp"

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

    for (int i = 0; i < edgeCount; i++){
        int firstNode;
        int secondNode;
        scanf("%d", &firstNode);
        scanf("%d", &secondNode);

        edges[i][0] = firstNode;
        edges[i][1] = secondNode;
    }

    int currentColorationPointer[nodeCount] = {UNDEFINED};
    
    for (int i = 0; i < nodeCount; i++)
    {
        scanf("%d", &currentColorationPointer[i]);
    }
    
    //check if solution is valid

    //check for full coloration
    bool full = true;

    for (int i = 0; i < nodeCount; i++)
    {
        if (currentColorationPointer[i] == UNDEFINED || currentColorationPointer[i] >= colorCount)
        {
            full = false;
            cout << "ERROR: coloration[" << i << "] is UNDEFINED\n";
        }
    }

    if(!full){
        cout << "ERROR: expected full coloration\n";
    }
    //end of check for full coloration

    bool satisfies = true;
    for (int i = 0; i < edgeCount; i++)
    {
        int firstNode = edges[i][0];
        int secondNode = edges[i][1];
        if (currentColorationPointer[firstNode] == currentColorationPointer[secondNode])
        {
            satisfies = false;
            cout << "ERROR: node " << firstNode << " has the same color as node " << secondNode << " and both nodes are adjacent\n";
        }
    }

    if (!satisfies)
    {
        cout << "ERROR: coloration does not satisfy restrictions\n";
    }
    //end of solution verification
    
    return 0;
}
