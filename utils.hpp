#ifndef _UTILS_H_
#define _UTILS_H_

#define UNDEFINED -1

#include <tuple>
#include <functional>

using namespace std;

struct TupleHash {
    template <typename T, typename U>
    size_t operator()(const pair<T, U>& p) const {
        size_t h1 = hash<T>{}(p.first);
        size_t h2 = hash<U>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

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

//changes the value of coloration to an array full of UNDEFINED values
void getEmptyColoration(int nodeCount, int* coloration);

//changes the color of the node and changes the avaliableColors matrix for consistency
void updateNodeColor(int* avaliableColors, int nodeCount, int* coloration, int** nodeAjacencyList, int nodeBestColor, int node, int adjacentNodesCount, int colorCount);

#endif /* _UTILS_H_ */