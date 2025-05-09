#include <iostream>
#include "PointLattice.cpp"
using namespace std;

int main() {

    while (true) {
        cout <<"Enter the value of n for the n x n grid ( n > 2 ): ";
        int n;
        cin >> n;
        if (n <= 2) {
            cout << "Invalid input. Please enter a value greater than 2." << endl;
        }else {
            PointLattice lattice(n);
            lattice.solveGreedy();
            //lattice.solveDP();
            cout << "Minimum moves required: " << lattice.moves << endl;
        }
    }

}
