#ifndef _GREEDY_H_
#define _GREEDY_H_

#include <queue>

struct CompareNodes {
    bool operator()(const pair<pair<int, int>, int>& p1, const pair<pair<int, int>, int>& p2) {
        if (p1.first.first == p2.first.first)
        {
            return p1.first.second < p2.first.second;
        }
        else{
            return p1.first.first < p2.first.first;
        }
    }
};

//selects the node coloration with the lowest maxValue in this step. returns the selected color if coloring was possible and UNDEFINED if it was not. updates the avaliableColors matrix
int getNodeBestStepColor(int colorCount, float* totalColorWeights, int node, int* avaliableColors);

//selects the node coloration with the lowest number of conflicts. if there is more than one coloration with the lowest number of conflicts, the one with lowest total weights is selected
int getNodeRecolorationColor(int colorCount, int** nodeAdjacencyList, int* coloration, float* totalColorWeights, int node, int adjacentNodeQuantity, int* recolorationCount);

//colors the graph following the getNodeBestStepColor() heuristic. returns UNDEFINED if was not able to construct following the heuristic
int greedyConstruction(int nodeCount, int colorCount, int** nodeAjacencyList, float* weights, int* coloration, float* totalColorWeights, int* adjacentNodeQuantity, int* avaliableColors, clock_t t0, float max_time);

#endif /* _GREEDY_H_ */