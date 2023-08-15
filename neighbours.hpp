#ifndef _NEIGHBOURS_H_
#define _NEIGHBOURS_H_

#include "utils.hpp"

//returns the max color value of one neighbour
double getColorChangesValue(int* coloration, int firstNodeNewColor, int secondNodeNewColor, int firstNode, int secondNode, double* totalColorWeights, double* weights, int colorCount);

//changes the values of coloration and totalColorWeights to the values of the best neighbour for the current graph. returns the best maxColorValue of all neighbours
double getBestNeighbour(int nodeCount, int colorCount, int** nodeAjacencyList, double* totalColorWeights, int* coloration, double maxColorValue, double* weights, int* avaliableColors, unordered_set<pair<int, int>, TupleHash>* adjacencyHash, int* adjacentNodeQuantity, int& firstNode, int& secondNode, int& firstColor, int& secondColor);

#endif /* _NEIGHBOURS_H_ */