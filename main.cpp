#include "ModifiedNQueens.hpp"
#include "SearchAlgorithms.hpp"
#include <iostream>

using namespace std;

int main() {

    int N;
    int choice;

    cout << "Enter value of N: " << endl;
    cin >> N;

    ModifiedNQueens problem(N);

    cout << "Choose Search Algorithm: " << endl;
    cout << "1. BFS\n";
    cout << "2. UCS\n";
    cout << "3. A*\n";
    cout << "Enter your choice (1-3): " << endl;
    cin >> choice;

    SearchResult result;

    // ALGORITHM SELECTION 
    if (choice == 1) {
        cout << "Running BFS...\n";
        result = SearchAlgorithms::BFS(problem);
    }
    else if (choice == 2) {
        cout << "\nRunning UCS...\n";
        result = SearchAlgorithms::UCS(problem);
    }
    else if (choice == 3) {
        cout << "\nRunning A*...\n";
        result = SearchAlgorithms::AStar(problem);
    }
    else {
        cout << "Invalid choice. Please restart program." << endl;
        return 0;
    }

    // PRINT RESULT 
    if (result.success) {
        cout << "\nSolution Found!\n\n";
        problem.printState(result.solution);

        cout << "\nNodes Expanded: " << result.nodesExpanded << endl;
        cout << "Frontier Remaining: " << result.frontierSize << endl;
    }
    else {
        cout << "\nNo solution found.\n";
    }

    return 0;
}