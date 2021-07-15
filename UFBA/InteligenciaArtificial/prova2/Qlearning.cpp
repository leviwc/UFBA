#include <iostream>

using namespace std;
struct acoes {
    double left, right, up, down;
    int action() {
        if (left >= right and left >= up and left >= down) {
            return 0;
        } else if (right >= left and right >= up and right >= down) {
            return 1;
        } else if (up >= left and up >= right and up >= down) {
            return 2;
        } else {
            return 3;
        }
    }
    double side(int num) {
        if (num == 0) {
            return left;
        } else if (num == 1) {
            return right;
        } else if (num == 2) {
            return up;
        } else {
            return down;
        }
    }
    double mai() { return max(max(left, right), max(up, down)); }
    void add(int num, double newval) {
        if (num == 0) {
            left = newval;
        } else if (num == 1) {
            right = newval;
        } else if (num == 2) {
            up = newval;
        } else {
            down = newval;
        }
    }
};
double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
pair<int, int> next(pair<int, int> state, int action) {
    if (action == 0) {
        state.second--;
    } else if (action == 1) {
        state.second++;
    } else if (action == 2) {
        state.first--;
    } else {
        state.first++;
    }
    return state;
}
int32_t main() {
    int n;
    cin >> n;
    double e, fd, tx;
    cin >> e >> fd >> tx;
    double alpha = tx, gamma = fd;
    int mat[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }
    pair<int, int> item;
    cin >> item.first >> item.second;
    acoes qtable[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            qtable[i][j].left = 0;
            qtable[i][j].right = 0;
            qtable[i][j].up = 0;
            qtable[i][j].down = 0;
        }
    }
    for (int i = 0; i < 1000; i++) {
        pair<int, int> estado = item;
        int epochs, penalties, reward;
        epochs = penalties = reward = 0;
        while (true) {
            int action;
            if (fRand(0, 1) < e) {
                action = rand() % 4;
            } else {
                action = qtable[estado.first][estado.second].action();
            }
            pair<int, int> next_state = next(estado, action);
            if (next_state.first < 0 or next_state.first >= n or
                next_state.second < 0 or next_state.second >= n) {
                continue;
            }
            reward = mat[next_state.first][next_state.second];
            double old_value = qtable[estado.first][estado.second].side(action);
            double nextMax = qtable[next_state.first][next_state.second].mai();
            double new_value =
                (1.0 - alpha) * old_value + alpha * (reward + gamma * nextMax);
            qtable[estado.first][estado.second].add(action, new_value);
            if (reward == -100) {
                penalties += 1;
            }
            estado = next_state;
            epochs += 1;
            if (mat[estado.first][estado.second] == 100) break;
        }
    }
    while (mat[item.first][item.second] != 100) {
        cout << item.first << " " << item.second << endl;
        int action = qtable[item.first][item.second].action();
        item = next(item, action);
    }
    cout << item.first << " " << item.second << endl;
}