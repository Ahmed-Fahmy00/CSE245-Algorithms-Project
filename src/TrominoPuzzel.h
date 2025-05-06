#ifndef TROMINOPUZZEL_H
#define TROMINOPUZZEL_H

using namespace std;

class TrominoPuzzel {
private:
    int board[64][64]= {0};
    int tileCount;
    void assignColors();

    bool colored = false;
public:
    int size;
    int xMiss;
    int yMiss;

    TrominoPuzzel(int n, int x, int y);
    void solveTrominoDAC(int size, int missingX, int missingY, int topX, int topY);
    bool solveTrominoBT();
    void printBoard();
};
#endif //TROMINOPUZZEL_H