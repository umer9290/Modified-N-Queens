#ifndef ModifiedNQueens_h
#define ModifiedNQueens_h

#include <vector>
#include <string>

using namespace std;

class ModifiedNQueens {
private:
    int N;  // board size

public:
    ModifiedNQueens(int n);

    int getSize() const;

    vector<pair<int,int>> getInitialState() const;

    bool isGoal(const vector<pair<int,int>>& state) const;

    vector<pair<int,char>> getActions(const vector<pair<int,int>>& state) const;

    vector<pair<int,int>> getResult(
        const vector<pair<int,int>>& state,
        pair<int,char> action
    ) const;

    int heuristic(const vector<pair<int,int>>& state) const;

    void printState(const vector<pair<int,int>>& state) const;
};

#endif