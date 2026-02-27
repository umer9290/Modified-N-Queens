# Modified-N-Queens

Project Description

This project implements a modified version of the N-Queens problem using multiple search algorithms:

Breadth-First Search (BFS)

Uniform Cost Search (UCS)

A* Search with a conflict-count heuristic

In this modified version, all queens are initially placed in the top row. The goal is to move the queens into a configuration where no two queens attack each other.

The project demonstrates different search strategies and heuristic techniques to compare performance and efficiency, particularly for larger board sizes where BFS and UCS become computationally expensive.

# How to Compile and Run

To compile the project, build all source files (main.cpp, ModifiedNQueens.cpp, SearchAlgorithms.cpp) to generate the executable:

g++ main.cpp ModifiedNQueens.cpp SearchAlgorithms.cpp -o main.exe

To run the program:

Open Command Prompt (cmd) or terminal

Navigate to the project folder

Run:

main.exe

Follow the prompts to select board size and algorithm

# Project Structure

main.cpp – Entry point of the program

ModifiedNQueens.hpp / .cpp – Board state, initial state, actions, result function, goal test, heuristic, and printing functions

SearchAlgorithms.hpp / .cpp – Implements BFS, UCS, and A* search

Utilities – Helper functions for state tracking and comparison

# Team Members

Umer Bin Affan (30497)

Raheel Shaikh (31554)
