#include "SearchAlgorithms.hpp"
#include <queue>
#include <set>

using namespace std;


// Converts state to string so we can store it in visited set
// This prevents revisiting the same configuration again
string stateToString(const vector<pair<int,int>>& state) {

    string s = "";

    for (auto q : state) {
        s += to_string(q.first) + "," + to_string(q.second) + ";";
    }

    return s;
}


/*

-BFS - Breadth First Search
    Expands nodes level by level using FIFO queue
    Guarantees shortest path in terms of number of moves

*/

SearchResult SearchAlgorithms::BFS(ModifiedNQueens& problem) {

    queue<vector<pair<int,int>>> frontier;  // FIFO structure
    set<string> visited;                   // Tracks explored states

    SearchResult result;
    result.nodesExpanded = 0;

    auto initial = problem.getInitialState();

    // Start search with initial state
    frontier.push(initial);
    visited.insert(stateToString(initial));

    while (!frontier.empty()) {

        // Remove next state from queue
        auto state = frontier.front();
        frontier.pop();

        result.nodesExpanded++;

        // Check if this state satisfies goal conditions
        if (problem.isGoal(state)) {
            result.solution = state;
            result.frontierSize = frontier.size();
            result.success = true;
            return result;
        }

        // Generate all possible next moves
        auto actions = problem.getActions(state);

        for (auto a : actions) {

            auto newState = problem.getResult(state, a);
            string key = stateToString(newState);

            // Expand only if state was never seen before
            if (visited.find(key) == visited.end()) {
                frontier.push(newState);
                visited.insert(key);
            }
        }
    }

    result.success = false;
    return result;
}


/*
- UCS - Uniform Cost Search
    .) Expands node with lowest accumulated path cost g(n)
    .) Unlike BFS, it uses priority queue instead of FIFO queue
*/

SearchResult SearchAlgorithms::UCS(ModifiedNQueens& problem) {

    // Node stores (cost so far, state)
    using Node = pair<int, vector<pair<int,int>>>;

    // Min-heap based on total path cost
    auto cmp = [](Node a, Node b) {
        return a.first > b.first;
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> frontier(cmp);

    set<string> visited;

    SearchResult result;
    result.nodesExpanded = 0;

    auto initial = problem.getInitialState();

    // Initial state cost is 0
    frontier.push({0, initial});

    while (!frontier.empty()) {

        // Pick state with lowest path cost
        Node current = frontier.top();
        frontier.pop();

        int costSoFar = current.first;
        auto state = current.second;

        string key = stateToString(state);

        // Skip if already expanded
        if (visited.find(key) != visited.end())
            continue;

        visited.insert(key);
        result.nodesExpanded++;

        // Check if goal reached
        if (problem.isGoal(state)) {
            result.solution = state;
            result.frontierSize = frontier.size();
            result.success = true;
            return result;
        }

        // Generate possible actions
        auto actions = problem.getActions(state);

        for (auto a : actions) {

            auto newState = problem.getResult(state, a);

            // Each move has cost 1
            int newCost = costSoFar + 1;

            frontier.push({newCost, newState});
        }
    }

    result.success = false;
    return result;
}


/*

- A* Search
    .) Uses heuristic (conflict count) to guide search
    .) Expands states with lower heuristic first

*/

SearchResult SearchAlgorithms::AStar(ModifiedNQueens& problem) {

    // Node structure
    struct Node {
        int f;                      // f(n) = g(n) + h(n), total estimated cost
        int g;                      // g(n), cost to reach this state from start
        vector<pair<int,int>> state; 
    };

    // Min-heap comparator: node with smallest f(n) has highest priority
    auto cmp = [](const Node &a, const Node &b) {
        return a.f > b.f; // smaller f comes first
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> frontier(cmp); // priority queue for A*
    set<string> visited; // to avoid revisiting the same state

    SearchResult result;
    result.nodesExpanded = 0; // count of nodes expanded during search

    // Get initial board state
    auto initial = problem.getInitialState();
    int h0 = problem.heuristic(initial); // heuristic for initial state

    // Push initial state to frontier: g = 0, f = g + h
    frontier.push({h0, 0, initial});

    while (!frontier.empty()) {

        Node current = frontier.top(); // get node with lowest f(n)
        frontier.pop();

        // Convert state to string for visited tracking
        string key = stateToString(current.state);

        // Skip if this state was already visited
        if (visited.find(key) != visited.end())
            continue;

        visited.insert(key);        // mark state as visited
        result.nodesExpanded++;     // increment expanded node count

        // Check if current state is goal
        if (problem.isGoal(current.state)) {
            result.solution = current.state;
            result.frontierSize = frontier.size();
            result.success = true;
            return result; // goal found, return result
        }

        // Generate all possible actions from current state
        auto actions = problem.getActions(current.state);

        for (auto a : actions) {

            // Apply action to get new state
            auto newState = problem.getResult(current.state, a);

            string newKey = stateToString(newState);

            // Skip if new state is already visited
            if (visited.find(newKey) != visited.end())
                continue;

            int gNew = current.g + 1;               // cost to reach new state
            int hNew = problem.heuristic(newState); // heuristic estimate to goal
            int fNew = gNew + hNew;                 // f = g + h

            // Push new state into frontier with its f value
            frontier.push({fNew, gNew, newState});
        }
    }

    // No solution found
    result.success = false;
    return result;
}