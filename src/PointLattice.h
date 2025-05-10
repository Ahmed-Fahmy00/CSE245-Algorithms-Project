#ifndef POINTLATTICE_H
#define POINTLATTICE_H

#include <vector>
using namespace std;

class PointLattice {
private:
    int n; // Size of the grid
    vector<vector<int>> grid; // 2D array to represent the grid
    vector<int[4]> eachmove; // Optional: Could store move history
    int minmoves(); // Minimum number of moves (2n - 2)
    void move(int &startX, int &startY, int endX, int endY); // Log a move and update position

public:
    int moves; // Track number of moves taken
    PointLattice(int size); // Constructor

    void solveGreedy(); // Existing greedy algorithm
    void solveDP();     // Dynamic programming solution
};

#endif // POINTLATTICE_H
