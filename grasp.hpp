#ifndef _GRASP_H_
#define _GRASP_H_

#include "utils.hpp"

//returns the max value after one iteration of the grasp meta heuristic. changes the value of the coloration array to the local minimum values
float grasp(int nodeCount, int colorCount, int** nodeAjacencyList, float* weights, int* coloration, int* adjacentNodeListLength, unordered_set<unsigned long long>* ajacencyHash, clock_t t0);

#endif /* _GRASP_H_ */