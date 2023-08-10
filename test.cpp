#include "utils.hpp"
#include "greedy.hpp"
#include "neighbours.hpp"
#include "grasp.hpp"

int main() {

    int passedTests = 0;
    int totalTests = 0;

    //getLowestAvaliableColorT1
    {
        int colorCount = 0;

        float totalColorWeights[colorCount] = {0};
        int avaliableColors[colorCount] = {0};

        int lowestAvaliableColor = getLowestAvaliableColor(totalColorWeights, avaliableColors, colorCount);

        if (lowestAvaliableColor == UNDEFINED)
        {
            cout << "getLowestAvaliableColorT1: passed\n";
            passedTests++;
        }
        else{
            cout << "\nERROR: expected " << UNDEFINED << " but got " << lowestAvaliableColor << "\n\n";
        }
        totalTests++;
    }

    //getLowestAvaliableColorT2
    {
        int colorCount = 1;

        float totalColorWeights[colorCount] = {0};
        int avaliableColors[colorCount] = {0};

        int lowestAvaliableColor = getLowestAvaliableColor(totalColorWeights, avaliableColors, colorCount);

        if (lowestAvaliableColor == 0)
        {
            cout << "getLowestAvaliableColorT2: passed\n";
            passedTests++;
        }
        else{
            cout << "\nERROR: expected " << 0 << " but got " << lowestAvaliableColor << "\n\n";
        }
        totalTests++;
    }

    //getLowestAvaliableColorT3
    {
        int colorCount = 2;

        float totalColorWeights[colorCount] = {0, 1};
        int avaliableColors[colorCount] = {0, 1};

        int lowestAvaliableColor = getLowestAvaliableColor(totalColorWeights, avaliableColors, colorCount);

        if (lowestAvaliableColor == 0)
        {
            cout << "getLowestAvaliableColorT3: passed\n";
            passedTests++;
        }
        else{
            cout << "\nERROR: expected " << 0 << " but got " << lowestAvaliableColor << "\n\n";
        }
        totalTests++;
    }
    
    //getLowestAvaliableColorT4
    {
        int colorCount = 2;

        float totalColorWeights[colorCount] = {0, 1};
        int avaliableColors[colorCount] = {1, 0};

        int lowestAvaliableColor = getLowestAvaliableColor(totalColorWeights, avaliableColors, colorCount);

        if (lowestAvaliableColor == 1)
        {
            cout << "getLowestAvaliableColorT4: passed\n";
            passedTests++;
        }
        else{
            cout << "\nERROR: expected " << 1 << " but got " << lowestAvaliableColor << "\n\n";
        }
        totalTests++;
    }

    //getLowestAvaliableColorT5
    {
        int colorCount = 3;

        float totalColorWeights[colorCount] = {1, 1, 1};
        int avaliableColors[colorCount] = {1, 1, 1};

        int lowestAvaliableColor = getLowestAvaliableColor(totalColorWeights, avaliableColors, colorCount);

        if (lowestAvaliableColor == UNDEFINED)
        {
            cout << "getLowestAvaliableColorT5: passed\n";
            passedTests++;
        }
        else{
            cout << "\nERROR: expected " << UNDEFINED << " but got " << lowestAvaliableColor << "\n\n";
        }
        totalTests++;
    }

    //getLowestAvaliableColorT6
    {
        int colorCount = 3;

        float totalColorWeights[colorCount] = {1, 2, 3};
        int avaliableColors[colorCount] = {2, 1, 0};

        int lowestAvaliableColor = getLowestAvaliableColor(totalColorWeights, avaliableColors, colorCount);

        if (lowestAvaliableColor == 2)
        {
            cout << "getLowestAvaliableColorT6: passed\n";
            passedTests++;
        }
        else{
            cout << "\nERROR: expected " << 2 << " but got " << lowestAvaliableColor << "\n\n";
        }
        totalTests++;
    }

    //updateNodeColorT1
    {
        int nodeCount = 3;
        int colorCount = 2;

        int coloration[nodeCount] = {-1, -1, -1};

        int* nodeAjacencyList[nodeCount];
        nodeAjacencyList[0] = new int[1]{1};
        nodeAjacencyList[1] = new int[2]{0, 2};
        nodeAjacencyList[2] = new int[1]{1};

        int nodeBestColor = 0;
        int node = 1;
        int adjacentNodesCount = 2;

        float totalColorWeights[colorCount] = {1, 2, 3};
        int avaliableColors[node*colorCount] =
        {
            0, 0,
            0, 0,
            0, 0
        };

        updateNodeColor(avaliableColors, nodeCount, coloration, nodeAjacencyList, nodeBestColor, node, adjacentNodesCount, colorCount);

        for (int i = 0; i < nodeCount*colorCount; i++)
        {
            //cout << "pos: " << i << " value: " << avaliableColors[i] << "\n";
        }
        

        if (coloration[node] == 0 && avaliableColors[0] == 1 && avaliableColors[4] == 1)
        {
            cout << "updateNodeColorT1: passed\n";
            passedTests++;
        }
        else{
            cout << "\nERROR\n\n";
        }
        totalTests++;
    }

    //updateNodeColorT2
    {
        int nodeCount = 3;
        int colorCount = 2;

        int coloration[nodeCount] = {-1, -1, -1};

        int* nodeAjacencyList[nodeCount];
        nodeAjacencyList[0] = new int[1]{1};
        nodeAjacencyList[1] = new int[2]{0, 2};
        nodeAjacencyList[2] = new int[1]{1};

        int nodeBestColor = 1;
        int node = 1;
        int adjacentNodesCount = 2;

        float totalColorWeights[colorCount] = {1, 2, 3};
        int avaliableColors[node*colorCount] =
        {
            1, 0,
            0, 0,
            1, 0
        };

        updateNodeColor(avaliableColors, nodeCount, coloration, nodeAjacencyList, nodeBestColor, node, adjacentNodesCount, colorCount);

        for (int i = 0; i < nodeCount*colorCount; i++)
        {
            //cout << "pos: " << i << " value: " << avaliableColors[i] << "\n";
        }

        if (coloration[node] == 1 && avaliableColors[0] == 1 && avaliableColors[1] == 1 && avaliableColors[4] == 1 && avaliableColors[5] == 1)
        {
            cout << "updateNodeColorT2: passed\n";
            passedTests++;
        }
        else{
            cout << "\nERROR\n\n";
        }
        totalTests++;
    }

    //updateNodeColorT3
    {
        int nodeCount = 3;
        int colorCount = 2;

        int coloration[nodeCount] = {1, 0, 1};

        int* nodeAjacencyList[nodeCount];
        nodeAjacencyList[0] = new int[1]{1};
        nodeAjacencyList[1] = new int[2]{0, 2};
        nodeAjacencyList[2] = new int[1]{1};

        int nodeBestColor = 1;
        int node = 1;
        int adjacentNodesCount = 2;

        float totalColorWeights[colorCount] = {1, 2, 3};
        int avaliableColors[node*colorCount] =
        {
            0, 0,
            0, 0,
            0, 0
        };

        updateNodeColor(avaliableColors, nodeCount, coloration, nodeAjacencyList, nodeBestColor, node, adjacentNodesCount, colorCount);

        for (int i = 0; i < nodeCount*colorCount; i++)
        {
            //cout << "pos: " << i << " value: " << avaliableColors[i] << "\n";
        }

        if (coloration[node] == 1 && avaliableColors[0] == -1 && avaliableColors[1] == 1 && avaliableColors[4] == -1 && avaliableColors[5] == 1)
        {
            cout << "updateNodeColorT3: passed\n";
            passedTests++;
        }
        else{
            cout << "\nERROR\n\n";
        }
        totalTests++;
    }

    

    cout << passedTests << "/" << totalTests << " tests passed\n";
    if (passedTests != totalTests)
    {
        cout << "please verify the errors\n";
    }

    return 0;
}
