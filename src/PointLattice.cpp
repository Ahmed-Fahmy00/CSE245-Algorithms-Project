#include "PointLattice.h"
#include <iostream>

#include <cmath>

using namespace std;

PointLattice::PointLattice(int size) {
    n= size;
    moves = 0;
}

int PointLattice::minmoves() {
    return (2 * n) - 2;
}

void PointLattice::move(int &startX, int &startY, int endX, int endY) {
    moves++;
    cout << "Move " << moves<<": ( " << startX << ", " << startY << ") to ( " << endX << ", " << endY << ")\n";
    startX= endX;
    startY= endY;
}

void PointLattice::solveDP() {
    if (n < 3) {
        cout << "DP solution is only implemented for n >= 3.\n";
        return;
    }

    int X = n%2 == 0 ?  n / 2  - 1: round(n / 2) ;
    int Y = round(n / 2) ;

    moves = 0;

    move(X, Y, X + 2, Y + 2);
    move(X, Y, X    , Y - 3);
    move(X, Y, X - 3, Y + 3);
    move(X, Y, X + 4, Y    );

    if (moves == minmoves()) return;
    move(X, Y, X, Y - 3);

    int step = 4;
    bool flag = true;

    while (moves < minmoves()) {
        if (flag) {
            move(X, Y, X + step, Y);  // right
        } else {
            move(X, Y, X - step, Y);  // left
        }

        if (moves == minmoves()) return;

        if (flag) {
            move(X, Y, X, Y + step);  // down
        } else {
            move(X, Y, X, Y - step);  // up
        }

        flag = !flag;
        step++;
    }
}

void PointLattice::solveGreedy() {
    if (n < 3) {
        cout << "Grid size must be at least 3x3 for this solution.\n";
        return;
    }

    int startX = 1, startY = 1;
    moves = 0;

    for (int i = 1; i <= n; ++i) {
        if (i % 2 == 1) {
            move(startX, startY, n, startY);
            startX = n;
        } else {
            move(startX, startY, 1, startY);
            startX = 1;
        }

        if (i < n) {
            move(startX, startY, startX, startY + 1);
            startY++;
        }
    }
}