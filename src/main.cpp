#include <iostream>
#include <conio.h>
#include "Task3.cpp"

using namespace std;

int main() {
    cout << "\t Hello, this is task 3 \n";
    cout << "\t Choose 1 option: \n";
    cout << "\t 1- Solve the given problem (8 disks, 4 peg) \n";
    cout << "\t 2- Solve for custom number of disks \n";
    cout << "\t 3- Exit \n";

    char choice;
    while (true) {
        choice = _getch(); // Get user input without pressing Enter

        switch (choice) {
            case '1': {
                cout << "Solving for 8 disks...\n";
                Task3 task(8);
                task.displayBoard();
                task.solveHanoi(8, 1, 4, 2, 3);
                break;
            }
            case '2': {
                int n;
                cout << "Enter the number of disks: ";
                cin >> n;
                if (n <= 0) {
                    cout << "Invalid number of disks. Please enter a positive integer.\n";
                    break;
                }
                Task3 task(n);
                task.displayBoard();
                task.solveHanoi(n, 1, 4, 2, 3);
                break;
            }
            case '3':
                cout << "Exiting program...\n";
            return 0;
            default:
                break;
        }
    }
}
