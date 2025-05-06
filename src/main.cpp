#include <iostream>
#include "TrominoPuzzel.cpp"

using namespace std ;

int main()
{
    cout << "Enter board Size 2^n (from 1 to 6): ";
    int n, xMiss, yMiss;
    cin >> n;
    if (n < 1 || n > 6) {
        cout << "Invalid input! Board size must be between 2^1 and 2^6." << endl;
        return 0;
    }

    cout << "Enter the position of the missing square (0-based index): ";
    cin >> xMiss >> yMiss;

    int size = pow(2, n);
    if (xMiss < 0 || xMiss >= size || yMiss < 0 || yMiss >= size) {
        cout << "Invalid missing square position!" << endl;
        return 0;
    }

    TrominoPuzzel trominoPuzzle(n, xMiss, yMiss);
    trominoPuzzle.solveTrominoDAC(trominoPuzzle.size, xMiss, yMiss, 0, 0);
    //trominoPuzzle.solveTrominoBT();
    trominoPuzzle.printBoard();

    cin >> n ;
    return 0;
}