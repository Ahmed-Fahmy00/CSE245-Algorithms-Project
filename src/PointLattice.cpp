#include "PointLattice.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <functional>
#include <tuple>
#include <set>
#include <unordered_map>
#include <functional>
#include <bitset>
#include <cstdint>

using namespace std;

PointLattice::PointLattice(int size) {
    n= size;
    grid.resize(n + 2, vector<int>(n + 2, 0));
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

void PointLattice::solveGreedy() {
    if (n <= 2) {
        cout << "Greedy solution is only implemented for 3x3 (n=2) grid.\n";
        return;
    }

    int X = n%2 == 0 ? ( n / 2 ) - 1: round(n / 2) ;
    int Y = round(n / 2) ;

    move(X, Y, X + 2, Y + 2);
    move(X, Y, X    , Y - 3);
    move(X, Y, X - 3, Y + 3);
    move(X, Y, X + 4, Y    );

    if(moves == minmoves() ) return ;
    move(X, Y, X , Y -3);

    int count = -4;
    bool flag = true;
    while (moves < minmoves() ) {
        if (flag)
            move(X, Y, X + count, Y );
        else
            move(X, Y, X + abs(count), Y );

        if (moves == minmoves() ) return ;

        if (flag)
            move(X, Y, X , Y + abs(count));
        else
            move(X, Y, X , Y + count);

        if (flag)
            flag= false;
        else
            flag = true;

        count --;
    }

}

void PointLattice::solveDP() {

}

