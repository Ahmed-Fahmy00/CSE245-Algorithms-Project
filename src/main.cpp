#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
#include <algorithm>
using namespace std;

const int WIDTH = 4;
const int HEIGHT = 3;

vector<pair<int, int>> white_start = { {3, 0}, {3, 1}, {3, 2} };
vector<pair<int, int>> black_start = { {0, 0}, {0, 1}, {0, 2} };

vector<pair<int, int>> knight_directions = { {2, 1}, {1, 2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, -2}, {2, -1} };

bool in_bounds(pair<int, int> cell) {
    return cell.first >= 0 && cell.first < WIDTH && cell.second >= 0 && cell.second < HEIGHT;
}

vector<pair<int, int>> possible_knight_moves(pair<int, int> from) {
    vector<pair<int, int>> options;
    for (const auto& move : knight_directions) {
        pair<int, int> target = { from.first + move.first, from.second + move.second };
        if (in_bounds(target)) { options.push_back(target); }
    }
    return options;
}

bool is_target_state(const vector<pair<int, int>>& white, const vector<pair<int, int>>& black) {
    set<pair<int, int>> white_goal = { {0, 0}, {0, 1}, {0, 2} };
    set<pair<int, int>> black_goal = { {3, 0}, {3, 1}, {3, 2} };
    return set<pair<int, int>>(white.begin(), white.end()) == white_goal && set<pair<int, int>>(black.begin(), black.end()) == black_goal;
}

struct BoardState {
    vector<pair<int, int>> white;
    vector<pair<int, int>> black;
    int step_count;
    vector<tuple<char, pair<int, int>, pair<int, int>>> move_sequence;
};

pair<int, vector<tuple<char, pair<int, int>, pair<int, int>>>> solve_knight_puzzle(
    const vector<pair<int, int>>& white_init,
    const vector<pair<int, int>>& black_init
) {
    queue<BoardState> q;
    set<pair<vector<pair<int, int>>, vector<pair<int, int>>>> visited;

    q.push({ white_init, black_init, 0, {}});

    while (!q.empty()) {
        BoardState current = q.front();
        q.pop();

        if (is_target_state(current.white, current.black)) {
            return { current.step_count, current.move_sequence };
        }
        vector<pair<int, int>> players[2] = { current.white, current.black };
        char ids[2] = { 'W', 'B' };

        for (int p = 0; p < 2; ++p) {
            for (size_t i = 0; i < players[p].size(); ++i) {
                auto options = possible_knight_moves(players[p][i]);
                for (const auto& dest : options) {
                    if (find(players[0].begin(), players[0].end(), dest) == players[0].end() &&
                        find(players[1].begin(), players[1].end(), dest) == players[1].end()) {

                        auto updated_positions = players[p];
                        updated_positions[i] = dest;

                        pair<vector<pair<int, int>>, vector<pair<int, int>>> new_key =
                            p == 0 ? make_pair(updated_positions, current.black) : make_pair(current.white, updated_positions);

                        if (!visited.count(new_key)) {
                            visited.insert(new_key);
                            auto new_path = current.move_sequence;
                            new_path.emplace_back(ids[p], players[p][i], dest);

                            q.push({
                                new_key.first,
                                new_key.second,
                                current.step_count + 1,
                                new_path });
                        }
                    }
                }
            }
        }
    } return { -1, {} };
}

int main() {
    auto result = solve_knight_puzzle(white_start, black_start);
    int total_moves = result.first;
    auto steps = result.second;

    cout << "Minimum moves needed: " << total_moves << endl;
    if (total_moves != -1) {
        cout << "Move list:" << endl;
        for (const auto& step : steps) {
            cout << "Move " << get<0>(step) << " knight from ("
                 << get<1>(step).first << "," << get<1>(step).second << ") to ("
                 << get<2>(step).first << "," << get<2>(step).second << ")" << endl;
        }
    }

    return 0;
}
