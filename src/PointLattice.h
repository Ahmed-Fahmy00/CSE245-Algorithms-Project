#ifndef POINTLATTICE_H
#define POINTLATTICE_H


#include <vector>

using namespace std;

class PointLattice {
private:
    int n; // Size of the grid
    vector<vector<int>> grid; // 2D array to represent the grid
    vector<int[4]> eachmove; // 2D array for dynamic programming

    void move(int &startX, int &startY, int endX, int endY);
public:
    int moves;
    PointLattice(int size);

    int minmoves();
    void solveDP();
    void solveGreedy();
};

#endif //POINTLATTICE_H