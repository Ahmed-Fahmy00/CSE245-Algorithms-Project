#include <iostream>
#include <thread>
#include <stack>
#include <queue>
#include <cmath>
#include "TowerOfHanoi.h"
using namespace std;

TowerOfHanoi::TowerOfHanoi(int n) {
    system("cls");

    numDisks = n;
    moves = 0;
    minMoves = calcMinMoves(n);

    pegs.resize(4);
    for (int i = n; i >= 1; --i) {
        pegs[0].push(i);
    }
}

void TowerOfHanoi::solveDAC(int n, int from, int to, int tempPeg1, int tempPeg2) {
    if (n == 0) return;
    if (n == 1) {
        moveDisk(from, to);
        return;
    }
    if (n == 2) {
        moveDisk(from, tempPeg1);
        moveDisk(from, to);
        moveDisk(tempPeg1, to);
        return;
    }

    solveDAC(n - 2, from, tempPeg1, tempPeg2, to);
    moveDisk(from, tempPeg2);
    moveDisk(from, to);
    moveDisk(tempPeg2, to);
    solveDAC(n - 2, tempPeg1, to, from, tempPeg2);
}

void TowerOfHanoi::solveDP(int n, int from, int to, int tempPeg1, int tempPeg2) {
    if (n == 0) return;
    if (n == 1) {
        moveDisk(from, to);
        return;
    }
    if (n == 2) {
        moveDisk(from, tempPeg1);
        moveDisk(from, to);
        moveDisk(tempPeg1, to);
        return;
    }

    int optimal = optimalK(n);

    solveDP(optimal, from, tempPeg1, tempPeg2, to);
    solve3Peg(n - optimal, from, to, tempPeg2);
    solveDP(optimal, tempPeg1, to, from, tempPeg2);
}

int TowerOfHanoi::optimalK(int n) {
    if (kMemo[n] != 0) return kMemo[n];

    int bestK = 1;
    int minMoves = INT_MAX;

    for (int k = 1; k < n; ++k) {
        int moves = 2 * calcMinMoves(k) + pow(2, n - k) - 1;
        if (moves < minMoves) {
            minMoves = moves;
            bestK = k;
        }
    }

    kMemo[n] = bestK;
    return bestK;
}

int TowerOfHanoi::calcMinMoves(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (movesMemo[n] != 0) return movesMemo[n];

    int result = INT_MAX;
    for (int i = 1; i < n; i++) {
        int moves = 2 * calcMinMoves(i) + pow(2, n - i) - 1;
        result = min(result, moves);
    }

    movesMemo[n] = result;
    return result;
}

void TowerOfHanoi::solve3Peg(int n, int from, int to, int aux) {
    if (n == 0) return;
    if (n == 1) {
        moveDisk(from, to);
        return;
    }
    solve3Peg(n - 1, from, aux, to);
    moveDisk(from, to);
    solve3Peg(n - 1, aux, to, from);
}

void TowerOfHanoi::moveDisk(int from, int to) {
    if (pegs[from].empty()) return;

    pegs[to].push(pegs[from].top());
    pegs[from].pop();
    moves++;

    cout << moves <<": Move disk " << pegs[to].top() << " from peg " << from << " to peg " << to << endl;
    //displayBoard();
}

void TowerOfHanoi::displayBoard() {
    system("cls");
    cout << "\tNumber Of Moves: " << moves << endl;
    cout << "\tCurrent Pegs State:\n\n";

    vector<queue<int>> pegQueues(4);
    int maxHeight = numDisks;

    for (int i = 0; i < 4; ++i) {
        stack<int> temp = pegs[i];
        stack<int> reversed;

        while (!temp.empty()) {
            reversed.push(temp.top());
            temp.pop();
        }
        while (!reversed.empty()) {
            pegQueues[i].push(reversed.top());
            reversed.pop();
        }
    }

    cout << "\t";
    for (int i = 1; i < 5; ++i)
        cout << "Peg " << i << "\t";
    cout << endl;

    for (int row = maxHeight - 1; row >= 0; --row) {
        cout << "\t";
        for (int i = 0; i < 4; ++i) {
            queue<int> copy = pegQueues[i];
            if (row < copy.size()) {
                for (int j = 0; j < row; ++j)
                    copy.pop();
                cout << copy.front() << "\t";
            } else
                cout << "-\t";
        }
        cout << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(500));
}
