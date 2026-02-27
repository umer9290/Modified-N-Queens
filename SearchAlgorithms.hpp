#ifndef SearchAlgorithms_h
#define SearchAlgorithms_h

#include "ModifiedNQueens.hpp"
#include <vector>
#include <string>

struct SearchResult {
    vector<pair<int,int>> solution;
    int nodesExpanded;
    int frontierSize;
    bool success;
};

class SearchAlgorithms {
public:
    static SearchResult BFS(ModifiedNQueens& problem);
    static SearchResult UCS(ModifiedNQueens& problem);
    static SearchResult AStar(ModifiedNQueens& problem);
};

#endif