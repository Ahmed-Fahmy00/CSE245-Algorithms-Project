#include <iostream>
#include <conio.h>
#include "TowerOfHanoi.cpp"

using namespace std;

int main() {
    cout << "\t Hello, this is task 3 \n";
    cout << "\t Choose 1 option: \n";
    cout << "\t 1- Solve the given problem using Divide and Conquer (8 disks, 4 peg) \n";
    cout << "\t 2- Solve the given problem using Dynamic Programming (8 disks, 4 peg) \n";
    cout << "\t 3- Solve for custom number of disks \n";
    cout << "\t 4- Exit \n";

    while (true) {
        char choice = _getch(); // Get user input without pressing Enter

        switch (choice) {
            case '1': {
                cout << "Solving for 8 disks using Divide and Conquer...\n";
                TowerOfHanoi Problem1(8);
                Problem1.displayBoard();
                //cout << Problem1.calcMinMoves(8);
                Problem1.solveDAC(8, 0, 3, 1, 2);
                break;
            }
            case '2': {
                cout << "Solving for 8 disks using Dynamic Programming...\n";
                TowerOfHanoi Problem2(8);
                Problem2.displayBoard();
                Problem2.solveDP(8, 0, 3, 1, 2);
                break;
            }
            case '3': {
                int n;
                cout << "Enter the number of disks (1-20): ";
                cin >> n;
                if (n <= 0 || n > 20) {
                    cout << "Invalid number of disks. Please enter a positive integer.\n";
                    break;
                }
                TowerOfHanoi Problem3(n);
                Problem3.displayBoard();
                Problem3.solveDP(n, 0, 3, 1, 2);
                break;
            }
            case '4':
                cout << "Exiting program...\n";
                return 0;
            default:
                break;
        }
    }
}