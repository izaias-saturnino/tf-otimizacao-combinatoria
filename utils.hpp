#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <stdio.h>
#include <functional>
#include <unordered_set>
#include <limits>
#include <time.h>
#include <queue>

#define UNDEFINED -1
#define TIMEOUT 20

using namespace std;

//returns lowest avaliable color in terms of total weight. returns UNDEFINED if no color is avaliable
int getLowestAvaliableColor(float* totalColorWeights, int* avaliableColors, int colorCount);

//TODO
//its a "copy" of getLowestAvaliableColor()
//only code it if its going to be used
//returns highest avaliable color in terms of total weight
int getHighestAvaliableColor(float* totalColorWeights, int* avaliableColors);

//TODO
//its a "copy" of getLowestAvaliableColor() and getHighestAvaliableColor()
//only code it if its going to be used
//returns array with lowest and highest avaliable color in terms of total weight
int* getLowestAndHighestAvaliableColor(float* totalColorWeights, int* avaliableColors);

//changes the color of the node and changes the avaliableColors matrix for consistency
void updateNodeColor(int* avaliableColors, int* coloration, int** nodeAjacencyList, int nodeBestColor, int node, int adjacentNodesCount, int colorCount, float* totalColorWeights, float* weights);

void printVectorAsMatrix(int* vector, int rowCount, int colCount);

#endif /* _UTILS_H_ */