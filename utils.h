#ifndef _UTILS_H_
#define _UTILS_H_

#define bool int
#define false 0
#define true 1

#define UNDEFINED -1
#define END_OF_LIST -2

//returns lowest color in terms of total weight
int getLowestColor(int* totalColorWeights, int colorCount);

//returns lowest avaliable color in terms of total weight. returns UNDEFINED if no color is avaliable
int getLowestAvaliableColor(int* totalColorWeights, int* avaliableColors, int colorCount);

//TODO
//its a "copy" of getLowestAvaliableColor()
//only code it if its going to be used
//returns highest avaliable color in terms of total weight
int getHighestAvaliableColor(int* totalColorWeights, int* avaliableColors);

//TODO
//its a "copy" of getLowestAvaliableColor() and getHighestAvaliableColor()
//only code it if its going to be used
//returns array with lowest and highest avaliable color in terms of total weight
int* getLowestAndHighestAvaliableColor(int* totalColorWeights, int* avaliableColors);

//changes the values of nodeAjancencyList to have a list of ajacent nodes for each node. Each list of ajacent nodes is terminated by END_OF_LIST. also changes the values of adjacentNodeListLength to indicate the length of each list
void getNodesAjancencyList(int nodeCount, int colorCount, int** graph, int* weights, int* coloration, int** nodeAjacencyList, int* adjacentNodeListLength);

//changes the value of coloration to an array full of UNDEFINED values
void getEmptyColoration(int nodeCount, int* coloration);

//returns true if nodes are adjacent
int areNodesAdjacent(int firstNode, int secondNode, int** nodeAjacencyList, int nodeCount);

//changes the color of the node and changes the avaliableColors matrix for consistency
void updateNodeColor(int** avaliableColors, int nodeCount, int* coloration, int** nodeAjacencyList, int nodeBestColor, int node);

#endif /* _UTILS_H_ */