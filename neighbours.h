#ifndef _NEIGHBOURS_H_
#define _NEIGHBOURS_H_

//returns the max color value of one neighbour
int getColorChangesValue(int* coloration, int firstNodeNewColor, int secondNodeNewColor, int firstNode, int secondNode, int* totalColorWeights, int maxColorValue, int* weights, int colorCount, int* maxColor);

//changes the values of coloration and totalColorWeights to the values of the best neighbour for the current graph. returns the best maxColorValue of all neighbours
int getBestNeighbour(int nodeCount, int colorCount, int** nodeAjacencyList, int* totalColorWeights, int* coloration, int maxColorValue, int* weights, int** avaliableColors);

#endif /* _NEIGHBOURS_H_ */