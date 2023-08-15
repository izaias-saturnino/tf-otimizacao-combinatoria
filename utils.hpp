#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <stdio.h>
#include <tuple>
#include <functional>
#include <unordered_set>
#include <limits>
#include <time.h>

#define UNDEFINED -1
#define TIMEOUT 3600*12

using namespace std;

struct TupleHash {
    template <typename T, typename U>
    size_t operator()(const pair<T, U>& p) const {
        size_t h1 = hash<T>{}(p.first);
        size_t h2 = hash<U>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

//returns lowest avaliable color in terms of total weight. returns UNDEFINED if no color is avaliable
int getLowestAvaliableColor(double* totalColorWeights, int* avaliableColors, int colorCount);

//TODO
//its a "copy" of getLowestAvaliableColor()
//only code it if its going to be used
//returns highest avaliable color in terms of total weight
int getHighestAvaliableColor(double* totalColorWeights, int* avaliableColors);

//TODO
//its a "copy" of getLowestAvaliableColor() and getHighestAvaliableColor()
//only code it if its going to be used
//returns array with lowest and highest avaliable color in terms of total weight
int* getLowestAndHighestAvaliableColor(double* totalColorWeights, int* avaliableColors);

//changes the color of the node and changes the avaliableColors matrix for consistency
void updateNodeColor(int* avaliableColors, int* coloration, int** nodeAjacencyList, int nodeBestColor, int node, int adjacentNodesCount, int colorCount, double* totalColorWeights, double* weights, int& totalColoredNodes, bool* coloredNodes);
//changes the color of the node and changes the avaliableColors matrix for consistency
void updateNodeColor(int* avaliableColors, int* coloration, int** nodeAjacencyList, int nodeBestColor, int node, int adjacentNodesCount, int colorCount, double* totalColorWeights, double* weights);

void printVectorAsMatrix(int* vector, int rowCount, int colCount);

#endif /* _UTILS_H_ */