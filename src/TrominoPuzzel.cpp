#include "TrominoPuzzel.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>
#include <set>
#include <windows.h>

using namespace std;

TrominoPuzzel::TrominoPuzzel(int n, int x, int y) {
    xMiss= x;
    yMiss= y;
    board[xMiss][yMiss] = -1;

    tileCount = 1;
    size = pow(2, n);
}

void TrominoPuzzel::solveTrominoDAC(int size, int missingX, int missingY, int topX, int topY) {
    if (size == 2) {
        int trominoID = tileCount++;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (topX + i != missingX || topY + j != missingY) {
                    board[topX + i][topY + j] = trominoID;
                }
            }
        }
        return;
    }

    int half = size / 2;
    int midX = topX + half;
    int midY = topY + half;
    int trominoID = tileCount++;

    int quadX[4] = {topX, topX, midX, midX};
    int quadY[4] = {topY, midY, topY, midY};
    int newMissingX[4] = {midX - 1, midX - 1, midX, midX};
    int newMissingY[4] = {midY - 1, midY, midY - 1, midY};

    int quadrant = (missingX >= midX) * 2 + (missingY >= midY);
    newMissingX[quadrant] = missingX;
    newMissingY[quadrant] = missingY;

    for (int i = 0; i < 4; i++) {
        if (i != quadrant)
            board[newMissingX[i]][newMissingY[i]] = trominoID;
    }

    for (int i = 0; i < 4; i++) {
        solveTrominoDAC(half, newMissingX[i], newMissingY[i], quadX[i], quadY[i]);
    }
}

bool TrominoPuzzel::solveTrominoBT() {
    int r = -1, c = -1;
    bool flag = false;

    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            if (board[i][j] == 0) {
                r = i;
                c = j;
                flag = true;
                break;
            }
        }
        if (flag) break;
    }

    if (r == -1) return true;

    int relativeCoords[8][2][2] = {
        {{+1, 0}, {0, +1}},
        {{-1, 0}, {0, +1}},
        {{+1, 0}, {0, -1}},
        {{-1, 0}, {0, -1}},
        {{-1, 0}, {-1, +1}},
        {{-1, 0}, {-1, -1}},
        {{+1, 0}, {+1, +1}},
        {{+1, 0}, {+1, -1}}
    };

    for (int i = 0; i < 8; ++i) {
        int r1 = r + relativeCoords[i][0][0];
        int c1 = c + relativeCoords[i][0][1];
        int r2 = r + relativeCoords[i][1][0];
        int c2 = c + relativeCoords[i][1][1];

        if (r1 >= 0 && r1 < size && c1 >= 0 && c1 < size &&
            r2 >= 0 && r2 < size && c2 >= 0 && c2 < size &&
            board[r1][c1] == 0 && board[r2][c2] == 0) {

            int currentTileID = ++tileCount;
            board[r][c] = currentTileID;
            board[r1][c1] = currentTileID;
            board[r2][c2] = currentTileID;

            if (solveTrominoBT()) return true;

            board[r][c] = 0;
            board[r1][c1] = 0;
            board[r2][c2] = 0;
            tileCount--;
        }
    }
    return false;
}

void TrominoPuzzel::assignColors() {
    if (colored) return;
    colored = true;

    int tempBoard[128][128];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            tempBoard[i][j] = board[i][j];
        }
    }

    int trominoColors[128*128/3 + 5];
    for(int i = 0; i < (128*128/3 + 5); ++i) {
        trominoColors[i] = 0;
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int currentTrominoID = tempBoard[i][j];

            if (currentTrominoID == -1 || trominoColors[currentTrominoID] != 0) {
                continue;
            }

            bool usedColors[5] = {false};
            for (int x = 0; x < size; ++x) {
                for (int y = 0; y < size; ++y) {
                    if (tempBoard[x][y] == currentTrominoID) {
                        for (int d = 0; d < 4; ++d) {
                            int nx = x + dx[d];
                            int ny = y + dy[d];

                            if (nx >= 0 && ny >= 0 && nx < size && ny < size) {
                                int neighborTrominoID = tempBoard[nx][ny];
                                if (neighborTrominoID != currentTrominoID && neighborTrominoID != -1) {
                                    if (trominoColors[neighborTrominoID] != 0) {
                                        int neighborColor = trominoColors[neighborTrominoID];
                                        if (neighborColor == 1 || neighborColor == 2 || neighborColor == 4)
                                            usedColors[neighborColor] = true;

                                    }
                                }
                            }
                        }
                    }
                }
            }

            int chosenColor = 0;
            if (!usedColors[1]) {
                chosenColor = 1; // Try color 1 (BLUE)
            } else if (!usedColors[2]) {
                chosenColor = 2; // Try color 2 (GREEN)
            } else {
                chosenColor = 4; // Default to color 4 (RED)
            }

            trominoColors[currentTrominoID] = chosenColor;
            for (int x = 0; x < size; ++x) {
                for (int y = 0; y < size; ++y) {
                    if (tempBoard[x][y] == currentTrominoID) {
                        board[x][y] = chosenColor;
                    }
                }
            }
        }
    }
}

enum Colors {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    RED = 4,
    BRIGHT_WHITE = 15
};

void SetColor(Colors bgColor, Colors textColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void TrominoPuzzel::printBoard() {
    assignColors();
    cout << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == -1) { // Missing tile
                SetColor(BLACK, BRIGHT_WHITE);
                cout << " X ";
            } else {
                SetColor(static_cast<Colors>(board[i][j]), BLACK);
                cout << "  " <<" ";
            }
        }
        cout << endl;
    }
    SetColor(BLACK, BRIGHT_WHITE);
}