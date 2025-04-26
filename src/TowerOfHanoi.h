#ifndef TOWEROFHANOI_H
#define TOWEROFHANOI_H

using namespace std;

class TowerOfHanoi {
private:
    vector<stack<int>> pegs;  // Vector of 4 stacks representing the pegs
    int numDisks;  // Number of disks
    int moves;  // Number of moves made
    int minMoves;  // Minimum moves required
    int movesMemo[21]={0}; // Memoization array for moves
    int kMemo[21]={0}; // Memoization array for optimal k

    void moveDisk(int from, int to);  // Function to move a disk
    void solve3Peg(int n, int from, int to, int aux);  // Function to solve using 3 pegs
    int optimalK(int n);// Function to find the optimal k for 4 pegs
    
public:
    TowerOfHanoi(int n);  // Constructor to initialize the board with n disks
    void solveDAC(int n, int from, int to, int tempPeg1 , int tempPeg2);  // Function to solve using Divide and Conquer
    void solveDP(int n, int from, int to, int tempPeg1, int tempPeg2);  // Function to solve using Dynamic Programming
    void displayBoard();  // Function to print the current board state
    int calcMinMoves(int n); // Function to calculate minimum moves for 4 pegs

};

#endif //TOWEROFHANOI_H