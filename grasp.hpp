#ifndef _GRASP_H_
#define _GRASP_H_

#include <unordered_set>
#include "utils.hpp"

//returns the max value after one iteration of the grasp meta heuristic. changes the value of the coloration array to the local minimum values
int grasp(int nodeCount, int colorCount, int** nodeAjacencyList, float* weights, int* coloration, int* adjacentNodeListLength, unordered_set<pair<int, int>, TupleHash>* ajacencyHash);

#endif /* _GRASP_H_ */