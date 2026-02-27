#include "ModifiedNQueens.hpp"
#include <iostream>
#include <cmath>

ModifiedNQueens::ModifiedNQueens(int n) {
// Store the board size so all functions can use it
    N = n;
}

int ModifiedNQueens::getSize() const {
    return N;
}


/*

-INITIAL STATE
    .) All queens start in the top row (row = 0).
    .) Each column has exactly one queen initially.

*/

vector<pair<int,int>> ModifiedNQueens::getInitialState() const {

    vector<pair<int,int>> state;

    // Loop through each column and place queen at (0, col)
    for (int col = 0; col < N; col++) {
        state.push_back({0, col});
    }

    return state;
}


/*

-GOAL TEST
    1. Exactly one queen per row
    2. No conflicts (row, column, diagonal)

*/

bool ModifiedNQueens::isGoal(const vector<pair<int,int>>& state) const {

    // We count how many queens appear in each row
    vector<int> rowCount(N, 0);

    for (auto q : state) {
        rowCount[q.first]++;
    }

    // If any row has 0 or more than 1 queen then it is not valid
    for (int i = 0; i < N; i++) {
        if (rowCount[i] != 1)
            return false;
    }

    // If no row violations, check conflicts using heuristic
    return heuristic(state) == 0;
}


/*

-ACTION FUNCTION
    .) Generates all valid moves from current state.
    .) A queen can move U, D, L, R if:
            - It stays inside board
            - Adjacent cell is not occupied

*/

vector<pair<int,char>> ModifiedNQueens::getActions(
    const vector<pair<int,int>>& state) const {

    vector<pair<int,char>> actions;

    // Possible movement directions
    char directions[4] = {'U','D','L','R'};

    // Try moving every queen
    for (int i = 0; i < N; i++) {

        int r = state[i].first;
        int c = state[i].second;

        // Try each direction
        for (char d : directions) {

            int nr = r;
            int nc = c;

            // Compute new position
            if (d == 'U') nr--;
            if (d == 'D') nr++;
            if (d == 'L') nc--;
            if (d == 'R') nc++;

            // Skip if move goes outside board limits
            if (nr < 0 || nr >= N || nc < 0 || nc >= N)
                continue;

            // Check whether another queen already occupies that cell
            bool occupied = false;
            for (auto q : state) {
                if (q.first == nr && q.second == nc) {
                    occupied = true;
                    break;
                }
            }

            // Only add move if destination is free
            if (!occupied)
                actions.push_back({i, d});
        }
    }

    return actions;
}


/*

-RESULT FUNCTION
    .) Applies a single action and returns the new state.
    .) If move is invalid, original state is returned.

*/

vector<pair<int,int>> ModifiedNQueens::getResult(
    const vector<pair<int,int>>& state,
    pair<int,char> action) const {

    // Make a copy so original state remains unchanged
    vector<pair<int,int>> newState = state;

    int index = action.first;   // which queen
    char d = action.second;     // direction

    int r = newState[index].first;
    int c = newState[index].second;

    int nr = r;
    int nc = c;

    // Update coordinates according to direction
    if (d == 'U') nr--;
    if (d == 'D') nr++;
    if (d == 'L') nc--;
    if (d == 'R') nc++;

    // If move goes outside board then ignore it
    if (nr < 0 || nr >= N || nc < 0 || nc >= N)
        return state;

    // If destination cell is already occupied then ignore it
    for (auto q : state) {
        if (q.first == nr && q.second == nc)
            return state;
    }

    // Otherwise update queen position
    newState[index] = {nr, nc};
    return newState;
}


/*

-HEURISTIC FUNCTION
    .) Counts total number of conflicts.
    .) If queen A conflicts with queen B, it is counted twice (once per comparison).

*/

int ModifiedNQueens::heuristic(const vector<pair<int,int>>& state) const {

    int conflicts = 0;

    // Compare every queen with every other queen
    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N; j++) {

            // Skip comparing same queen
            if (i == j) continue;

            int r1 = state[i].first;
            int c1 = state[i].second;
            int r2 = state[j].first;
            int c2 = state[j].second;

            // Same row conflict
            if (r1 == r2) conflicts++;

            // Same column conflict
            else if (c1 == c2) conflicts++;

            // Diagonal conflict
            else if (abs(r1 - r2) == abs(c1 - c2))
                conflicts++;
        }
    }

    return conflicts;
}


/*

-PRINT FUNCTION
    .) Displays board visually using '.' and 'Q'

*/

void ModifiedNQueens::printState(
    const vector<pair<int,int>>& state) const {

    vector<vector<char>> board(N, vector<char>(N, '.'));

    // Mark queen positions
    for (auto q : state) {
        board[q.first][q.second] = 'Q';
    }

    // Print board row by row
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}