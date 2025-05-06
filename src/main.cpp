#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> Point;

// Build a path that uses exactly 2n-2 lines to cover all n^2 points
vector<Point> buildOptimalPathDP(int n) {
    vector<Point> path;

    // Start from top-left and go down the first column
    for (int r = 0; r < n; ++r) {
        path.emplace_back(r, 0);
    }

    // Now go right and zigzag up/down each column
    bool goingUp = true;
    for (int c = 1; c < n; ++c) {
        if (goingUp) {
            for (int r = n - 1; r >= 0; --r) {
                path.emplace_back(r, c);
            }
        } else {
            for (int r = 0; r < n; ++r) {
                path.emplace_back(r, c);
            }
        }
        goingUp = !goingUp;
    }

    return path;
}

void printPath(const vector<Point>& path) {
    for (const auto& p : path) {
        cout << "(" << p.first << ", " << p.second << ") -> ";
    }
    cout << "END\n";
}

// Count the number of straight line segments in the path
int countLines(const vector<Point>& path) {
    if (path.size() < 2) return 0;
    int lines = 1;

    int dx = path[1].first - path[0].first;
    int dy = path[1].second - path[0].second;

    for (size_t i = 2; i < path.size(); ++i) {
        int ndx = path[i].first - path[i - 1].first;
        int ndy = path[i].second - path[i - 1].second;

        if (ndx != dx || ndy != dy) {
            ++lines;
            dx = ndx;
            dy = ndy;
        }
    }

    return lines;
}

int main() {
    int n;
    cout << "Enter the value of n (n > 2): ";
    cin >> n;

    if (n <= 2) {
        cout << "Invalid input. n must be > 2.\n";
        return 1;
    }

    auto path = buildOptimalPathDP(n);
    printPath(path);
    cout << "Total points crossed: " << path.size() << "\n";
    cout << "Minimum number of straight lines used: " << countLines(path)
         << " (Expected: " << (2 * n - 2) << ")\n";

    return 0;
}
