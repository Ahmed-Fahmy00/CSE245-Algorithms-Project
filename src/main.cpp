#include <iostream>
#include "PointLattice.cpp"
using namespace std;

int main() {
    int choice = 1;
    while (choice == 1) {
        cout <<"Enter the value of n for the n x n grid ( n > 2 ): ";
        int n;
        cin >> n;
        if (n <= 2) {
            cout << "Invalid input. Please enter a value greater than 2." << endl;
        } else {
            PointLattice lattice(n);
            cout << "Enter 1 to solve using Greedy, 2 to solve using Dynamic Programming: ";
            int method;
            cin >> method;
            if (method == 1) {
                lattice.solveGreedy();
            } else {
                lattice.solveDP();
            }
            cout << "Minimum moves required: " << lattice.moves << endl;
        }
        cout << "Enter 1 to solve the problem, 0 to exit: ";
        cin >> choice;
    }

}
