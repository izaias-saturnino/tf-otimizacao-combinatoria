#ifndef _NEIGHBOURS_H_
#define _NEIGHBOURS_H_

#include "utils.hpp"

//returns the max color value of one neighbour
float getColorChangesValue(int* coloration, int firstNodeNewColor, int secondNodeNewColor, int firstNode, int secondNode, float* totalColorWeights, float* weights, int colorCount);

//changes the values of coloration and totalColorWeights to the values of the best neighbour for the current graph. returns the best maxColorValue of all neighbours
float getBestNeighbour(int nodeCount, int colorCount, int** nodeAjacencyList, float* totalColorWeights, int* coloration, float maxColorValue, float* weights, int* avaliableColors, unordered_set<pair<int, int>, TupleHash>* adjacencyHash, int* adjacentNodeQuantity, int& firstNode, int& secondNode, int& firstColor, int& secondColor);

#endif /* _NEIGHBOURS_H_ */