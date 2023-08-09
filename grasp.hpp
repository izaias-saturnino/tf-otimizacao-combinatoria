#ifndef _GRASP_H_
#define _GRASP_H_

//returns the max value after one iteration of the grasp meta heuristic. changes the value of the coloration array to the local minimum values
int grasp(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration, int* adjacentNodeListLength, int** nodeAjacencyMatrix);

#endif /* _GRASP_H_ */