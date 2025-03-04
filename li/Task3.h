#ifndef TASK3_H
#define TASK3_H

#include <vector>
#include <stack>

using namespace std;

class Task3 {
private:
    vector<stack<int>> pegs;  // Vector of 4 stacks representing the pegs

public:
    Task3(int n);  // Constructor to initialize the board with n disks
    void displayBoard();  // Function to print the current board state
    void moveDisk(int disk, int from, int to);  // Function to move a disk
    void solveHanoi(int n, int src, int dest, int aux1, int aux2);  // Solving function
    void pause();  // Function to introduce a 4-second pause
};

#endif // TASK3_H

