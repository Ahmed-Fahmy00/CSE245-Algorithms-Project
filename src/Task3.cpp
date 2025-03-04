#include <iostream>
#include <vector>
#include <stack>
#include <thread>
#include <chrono>
#include "../li/Task3.h"

using namespace std;

// Constructor: Initializes pegs and places n disks on the first peg
Task3::Task3(int n) {
    pegs.resize(5);  // Pegs 1 to 4 (index 0 is unused)
    for (int i = n; i >= 1; --i) {
        pegs[1].push(i);  // Place all disks on peg 1 initially
    }
}

// Displays the current state of the pegs
void Task3::displayBoard() {
    cout << "\nCurrent Board State:\n";
    for (int i = 1; i <= 4; ++i) {
        cout << "Peg " << i << ": ";
        stack<int> temp = pegs[i];
        vector<int> pegDisks;
        while (!temp.empty()) {
            pegDisks.push_back(temp.top());
            temp.pop();
        }
        for (int j = pegDisks.size() - 1; j >= 0; --j) {
            cout << pegDisks[j] << " ";
        }
        cout << endl;
    }
    cout << "---------------------------\n";
}

// Moves a disk from one peg to another, updates the board, and pauses
void Task3::moveDisk(int disk, int from, int to) {
    if (!pegs[from].empty() && pegs[from].top() == disk) {
        pegs[from].pop();
        pegs[to].push(disk);
        cout << "Move disk " << disk << " from peg " << from << " to peg " << to << endl;
        displayBoard();
        pause();
    }
}

// Pauses execution for 4 seconds
void Task3::pause() {
    this_thread::sleep_for(chrono::seconds(4));
}

// Frame-Stewart Algorithm to solve the 4-peg Tower of Hanoi problem optimally
void Task3::solveHanoi(int n, int src, int dest, int aux1, int aux2) {
    if (n == 0) return;
    if (n == 1) {
        moveDisk(1, src, dest);
        return;
    }

    int k = n / 2; // Optimal split (can be adjusted dynamically)

    solveHanoi(k, src, aux1, aux2, dest);  // Move k disks to auxiliary peg
    solveHanoi(n - k, src, dest, aux1, aux2);  // Move remaining disks to destination
    solveHanoi(k, aux1, dest, aux2, src);  // Move k disks from auxiliary peg to destination
}


