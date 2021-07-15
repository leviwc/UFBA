#include <math.h>

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
#define int long long
using namespace std;
double h[14][14] = {
    {0, 10, 18.5, 24.8, 36.4, 38.8, 35.8, 25.4, 17.6, 9.1, 16.7, 27.3, 27.6,
     29.8},
    {-1, 0, 8.5, 14.8, 26.6, 29.1, 26.1, 17.3, 10, 3.5, 15.5, 20.9, 19.1, 21.8},
    {-1, -1, 0, 6.3, 18.2, 20.6, 17.6, 13.6, 9.4, 10.3, 19.5, 19.1, 12.1, 16.6},
    {-1, -1, -1, 0, 12, 14.4, 11.5, 12.4, 12.6, 16.7, 23.6, 18.6, 10.6, 15.4},
    {-1, -1, -1, -1, 0, 3, 2.4, 19.4, 23.3, 28.2, 34.2, 24.8, 14.5, 17.9},
    {-1, -1, -1, -1, -1, 0, 3.3, 22.3, 25.7, 30.3, 36.7, 27.6, 15.2, 18.2},
    {-1, -1, -1, -1, -1, -1, 0, 20, 23, 27.3, 34.2, 25.7, 12.4, 15.6},
    {-1, -1, -1, -1, -1, -1, -1, 0, 8.2, 20.3, 16.1, 6.4, 22.7, 27.6},
    {-1, -1, -1, -1, -1, -1, -1, -1, 0, 13.5, 11.2, 10.9, 21.2, 26.6},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 17.6, 24.2, 18.7, 21.2},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 14.2, 31.5, 35.5},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 28.8, 33.6},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 5.1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
};
int s, t, v, u;
vector<pair<int, pair<double, int> > > adj[14];
void put(int a, int b, double val, int cor) {
    a--;
    b--;
    adj[a].push_back({b, {val, cor}});
    adj[b].push_back({a, {val, cor}});
}
pair<int, pair<double, int> > pai[14];
double dist[14];
void start() {
    for (int i = 0; i < 14; i++) {
        dist[i] = 1e9;
        pai[i] = {i, {0, 0}};
        for (int j = 0; j < 14; j++) {
            if (h[i][j] == -1) {
                h[i][j] = h[j][i];
            }
        }
    }
    // azul 1, amarelo 2, vermelho 3, verde 4
    put(1, 2, 10, 1);
    put(2, 3, 8.5, 1);
    put(2, 9, 10, 2);
    put(2, 10, 3.5, 2);
    put(3, 4, 6.3, 1);
    put(3, 9, 9.4, 3);
    put(3, 13, 18.7, 3);
    put(4, 5, 13, 1);
    put(4, 8, 15.3, 4);
    put(4, 13, 12.8, 4);
    put(5, 6, 3, 1);
    put(5, 7, 2.4, 2);
    put(5, 8, 30, 2);
    put(8, 9, 9.6, 2);
    put(8, 12, 6.4, 4);
    put(9, 11, 12.2, 3);
    put(13, 14, 5.1, 4);
}
vector<int> expansion, path;
double ans;
void aStar() {
    priority_queue<tuple<double, int, int>, vector<tuple<double, int, int> >,
                   greater<tuple<double, int, int> > >
        q;
    q.push(make_tuple(h[s][t], s, (int)0));
    dist[s] = 0;
    while (!q.empty()) {
        double a = get<0>(q.top());
        int b = get<1>(q.top());
        int cor = get<2>(q.top());
        q.pop();
        if (b == t) {
            cout << b << " " << cor << " " << dist[b] / v * 60 << endl;
            expansion.push_back(b);
            break;
        }
        if (dist[b] + (h[b][t]) != a) {
            continue;
        }
        cout << b << " " << cor << " " << dist[b] / v * 60 << endl;
        expansion.push_back(b);
        for (pair<int, pair<double, int> > x : adj[b]) {
            int bald = 0;
            if (cor != 0 and cor != x.second.second) {
                bald = (u / 60.0) * v;
            }
            int score = dist[b] + (x.second.first) + bald;
            if (score < dist[x.first]) {
                pai[x.first] = {b, x.second};
                dist[x.first] = score;
                q.push(make_tuple(score + (h[x.first][t]), x.first,
                                  x.second.second));
            }
        }
    }
    int at = t;
    int corat = pai[at].second.second;
    while (pai[at].first != at) {
        ans += pai[at].second.first / v * 60;
        if (corat != pai[at].second.second) {
            corat = pai[at].second.second;
            ans += u;
        }
        path.push_back(at);
        at = pai[at].first;
    }
    path.push_back(at);
    reverse(path.begin(), path.end());
}
signed main() {
    start();
    cin >> s >> t >> v >> u;
    s--, t--;
    aStar();
    for (int i = 0; i < (int)expansion.size(); i++) {
        cout << expansion[i] + 1 << (i == (int)expansion.size() - 1 ? "" : "-");
    }
    cout << endl;
    for (int i = 0; i < (int)path.size(); i++) {
        cout << path[i] + 1 << (i == (int)path.size() - 1 ? "" : "-");
    }
    cout << endl;
    cout << fixed << setprecision(1) << ans << endl;
}