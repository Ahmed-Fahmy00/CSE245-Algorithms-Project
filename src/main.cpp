#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <tuple>
#include <iomanip>

using namespace std;

const int MAXN = 10;

int n;
int targetLines;
set<pair<int, int>> visited;
vector<pair<int, int>> path;
map<tuple<int, int, int, int>, bool> memo;

int dx[4] = {0, 1, 0, -1}; // right, down, left, up
int dy[4] = {1, 0, -1, 0};

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

// DP + Backtracking
bool dfs(int x, int y, int dir, int linesUsed) {
    if (visited.size() == n * n && linesUsed == targetLines) {
        return true;
    }

    auto key = make_tuple(x, y, dir, linesUsed);
    if (memo.count(key)) return false;
    memo[key] = true;

    for (int newDir = 0; newDir < 4; ++newDir) {
        int nx = x + dx[newDir];
        int ny = y + dy[newDir];

        if (!isValid(nx, ny)) continue;

        bool isNewLine = (newDir != dir);
        int newLinesUsed = linesUsed + isNewLine;

        if (newLinesUsed > targetLines) continue;

        if (visited.count({nx, ny}) == 0) {
            visited.insert({nx, ny});
            path.push_back({nx, ny});

            if (dfs(nx, ny, newDir, newLinesUsed)) {
                return true;
            }

            path.pop_back();
            visited.erase({nx, ny});
        }
    }

    return false;
}

void printMatrixPath() {
    vector<vector<int>> grid(n, vector<int>(n, 0));
    for (int i = 0; i < path.size(); ++i) {
        int x = path[i].first;
        int y = path[i].second;
        grid[x][y] = i + 1;
    }

    cout << "\nPath Matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(3) << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    cout << "Enter grid size n (n > 2): ";
    cin >> n;

    if (n <= 2 || n > MAXN) {
        cout << "n must be between 3 and " << MAXN << ".\n";
        return 1;
    }

    targetLines = 2 * n - 2;
    bool found = false;

    for (int startDir = 0; startDir < 2; ++startDir) { // try right and down
        path.clear();
        visited.clear();
        memo.clear();

        visited.insert({0, 0});
        path.push_back({0, 0});

        if (dfs(0, 0, startDir, 0)) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "\nPath found:\n";
        for (auto& p : path) {
            cout << "(" << p.first << ", " << p.second << ") -> ";
        }
        cout << "END\n";
        cout << "\nTotal Points: " << path.size() << ", Total Lines Used: " << targetLines << endl;
        printMatrixPath();
    } else {
        cout << "No path found with exactly " << targetLines << " lines.\n";
    }

    return 0;
}
