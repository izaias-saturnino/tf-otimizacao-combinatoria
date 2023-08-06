#ifndef _GREEDY_H_
#define _GREEDY_H_

//selects the node coloration with the lowest maxValue in this step. Returns the selected color if coloring was possible and UNDEFINED if it was not. updates the avaliableColors matrix
int getNodeBestStepColor(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration, int* totalColorWeights, int node, int** avaliableColors);

//colors every adjacent node following the getNodeBestStepColor() heuristic. returns UNDEFINED if the adjacent nodes could not be colored
int colorAdjacentNodes(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration, int* totalColorWeights, int node, int adjacentNodesCount, int** avaliableColors);

//colors the graph following the getNodeBestStepColor() heuristic. returns UNDEFINED if was not able to construct following the heuristic
int greedyConstruction(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration, int* totalColorWeights, int* adjacentNodeQuantity, int** avaliableColors);

#endif /* _GREEDY_H_ */