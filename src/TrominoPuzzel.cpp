#include "TrominoPuzzel.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>
#include <vector>

using namespace std;

TrominoPuzzel::TrominoPuzzel(int n, int x, int y) {
    xMiss= x;
    yMiss= y;
    board[xMiss][yMiss] = -1;

    tileCount = 0;
    size = pow(2, n);
}

void TrominoPuzzel::solveTromino(int size, int missingX, int missingY, int topX, int topY) {
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
        solveTromino(half, newMissingX[i], newMissingY[i], quadX[i], quadY[i]);
    }
}

void TrominoPuzzel::assignColors() {
    if (colored) return; // Only color once
    colored = true;

    // Use a temporary board to keep original tile IDs while coloring
    int tempBoard[128][128];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            tempBoard[i][j] = board[i][j]; // Copy original IDs
        }
    }

    // Map to store the assigned color for each original tromino ID
    // Max tile ID is tileCount - 1. Size depends on size of board.
    // A map is flexible, or an array sized based on max possible tileCount
    // Max tiles = (size*size - 1) / 3. For size 128, this is ~5461.
    // Let's use an array for performance, assuming tile IDs are contiguous from 0.
    int trominoColors[128*128/3 + 5]; // Array to hold colors for tile IDs 0 to tileCount-1
    for(int i = 0; i < (128*128/3 + 5); ++i) {
        trominoColors[i] = 0; // 0 means uncolored
    }


    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // Iterate through the board to find each uncolored tromino tile by its ID
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int currentTrominoID = tempBoard[i][j];

            // Skip the missing tile or already colored trominoes
            if (currentTrominoID == -1 || trominoColors[currentTrominoID] != 0) {
                continue;
            }

            // This is the first cell we've encountered for this uncolored tromino ID.
            // Find colors used by adjacent trominoes.
            bool usedColors[5] = {false}; // Indices 1, 2, 4 will be used

            // Iterate through the board to find all cells belonging to the current tromino ID
            // and check their neighbors.
            for (int x = 0; x < size; ++x) {
                for (int y = 0; y < size; ++y) {
                    if (tempBoard[x][y] == currentTrominoID) { // Found a cell of the current tromino
                        // Check its neighbors
                        for (int d = 0; d < 4; ++d) {
                            int nx = x + dx[d];
                            int ny = y + dy[d];

                            // Check bounds
                            if (nx >= 0 && ny >= 0 && nx < size && ny < size) {
                                int neighborTrominoID = tempBoard[nx][ny];

                                // If the neighbor is part of a DIFFERENT tromino tile (and not the missing square)
                                if (neighborTrominoID != currentTrominoID && neighborTrominoID != -1) {
                                    // Check if the neighbor tromino has already been colored
                                    if (trominoColors[neighborTrominoID] != 0) {
                                        int neighborColor = trominoColors[neighborTrominoID];
                                        if (neighborColor == 1 || neighborColor == 2 || neighborColor == 4) {
                                            usedColors[neighborColor] = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Choose a color for the current tromino ID that hasn't been used by its neighbors
            int chosenColor = 0;
            if (!usedColors[1]) {
                chosenColor = 1; // Try color 1 (BLUE)
            } else if (!usedColors[2]) {
                chosenColor = 2; // Try color 2 (GREEN)
            } else {
                chosenColor = 4; // Default to color 4 (RED) - there should always be an available color among these 3
            }

            // Store the chosen color for this tromino ID
            trominoColors[currentTrominoID] = chosenColor;

            // Now, apply this chosen color to all cells on the main board belonging to this tromino ID
            for (int x = 0; x < size; ++x) {
                for (int y = 0; y < size; ++y) {
                    if (tempBoard[x][y] == currentTrominoID) {
                        board[x][y] = chosenColor;
                    }
                }
            }
        }
    }
    // The missing tile (-1) remains -1 in the board.
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
                if(board[i][j] < 10) {
                    cout << "  "  <<" ";
                } else {
                    cout << "  "  <<" ";
                }
            }
        }
        cout << endl;
    }
    SetColor(BLACK, BRIGHT_WHITE);
}