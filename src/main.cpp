#include "PointLattice.cpp"
#include <iostream>
#include <conio.h>

using namespace std;

int main() {

    while (true) {
        cout << "\n Welcome to the Point Lattice Solver!" << endl;
        cout << "\t Choose 1 option: \n";
        cout << "\t 1- Solve the given problem using Dynamic Programming \n";
        cout << "\t 2- Solve the given problem using Greedy \n";
        cout << "\t 3- Exit \n";

        char choice = _getch();
        switch (choice) {
            case '1': {
                system("cls");
                cout << "Enter the value of n for the n x n grid ( n > 2 ): ";

                int n;
                cin >> n;
                if (n <= 2) {
                    cout << "Invalid input. Please enter a value greater than 2." << endl;
                } else {
                    PointLattice lattice1(n);
                    lattice1.solveDP();
                    cout << "Minimum moves required: " << lattice1.moves << endl;
                }
                break;
            } case '2': {
                system("cls");
                cout << "Enter the value of n for the n x n grid ( n > 2 ): ";

                int n;
                cin >> n;
                if (n <= 2) {
                    cout << "Invalid input. Please enter a value greater than 2." << endl;
                } else {
                    PointLattice lattice2(n);
                    lattice2.solveGreedy();
                    cout << "Moves Made: " << lattice2.moves << endl;
                }
                break;
            } case '3': {
                cout << "Exiting program...\n";
                return 0;
            } default:
                break;

        }

    }

}
