#include <math.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#define int long long
using namespace std;
int h[12][12] = {
    {0, 270, 475, 675, 749, 828, 1017, 980, 1318, 1093, 1664, 1924},
    {-1, 0, 225, 394, 484, 612, 837, 938, 1236, 1238, 1646, 2128},
    {-1, -1, 0, 205, 290, 426, 712, 933, 1230, 1376, 1683, 2343},
    {-1, -1, -1, 0, 99, 247, 623, 933, 1190, 1508, 1673, 2457},
    {-1, -1, -1, -1, 0, 152, 551, 902, 1158, 1524, 1632, 2508},
    {-1, -1, -1, -1, -1, 0, 430, 846, 1078, 1545, 1553, 2533},
    {-1, -1, -1, -1, -1, -1, 0, 493, 657, 1298, 1227, 2334},
    {-1, -1, -1, -1, -1, -1, -1, 0, 325, 845, 746, 1860},
    {-1, -1, -1, -1, -1, -1, -1, -1, 0, 957, 488, 1938},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 965, 1032},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 1787},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
};
int s, t, val;
double p[12];
vector<pair<int, int> > adj[12];
void put(int a, int b, int val) {
    a--;
    b--;
    adj[a].push_back({b, val});
    adj[b].push_back({a, val});
}
int dist[12], pai[12];
void start() {
    for (int i = 0; i < 12; i++) {
        dist[i] = 1e9;
        pai[i] = i;
        for (int j = 0; j < 12; j++) {
            if (h[i][j] == -1) {
                h[i][j] = h[j][i];
            }
        }
    }
    put(1, 2, 270);
    put(1, 3, 475);
    put(1, 4, 675);
    put(1, 8, 980);
    put(1, 10, 1093);
    put(2, 3, 225);
    put(3, 4, 205);
    put(4, 5, 99);
    put(4, 7, 623);
    put(4, 8, 933);
    put(5, 6, 152);
    put(5, 7, 551);
    put(6, 7, 430);
    put(7, 8, 493);
    put(8, 9, 325);
    put(8, 10, 845);
    put(9, 10, 957);
    put(9, 11, 488);
    put(10, 11, 965);
    put(10, 12, 1032);
    put(11, 12, 1787);
}
string ans = "";
int aStar() {
    priority_queue<pair<int, int>, vector<pair<int, int> >,
                   greater<pair<int, int> > >
        q;
    q.push({0, s});
    dist[s] = 0;
    while (!q.empty()) {
        int b;
        b = q.top().second;
        q.pop();
        if (b == t) {
            break;
        }
        for (pair<int, int> v : adj[b]) {
            int score = v.second + dist[b];
            if (score < dist[v.first]) {
                pai[v.first] = b;
                dist[v.first] = score;
                q.push({(h[v.first][t]), v.first});
            }
        }
    }
    int sum = val;
    int at = t;
    while (pai[at] != at) {
        sum -= floor(val * (0.2 * (1.0 - p[at])));
        string aux = to_string(at + 1);
        if (at + 1 >= 10) {
            reverse(aux.begin(), aux.end());
        }
        ans += aux;
        at = pai[at];
        ans += '-';
    }
    sum -= floor(val * (0.2 * (1.0 - p[s])));
    string aux = to_string(s + 1);
    if (s + 1 >= 10) {
        reverse(aux.begin(), aux.end());
    }
    ans += aux;
    reverse(ans.begin(), ans.end());
    return sum;
}
signed main() {
    start();
    cin >> s >> t >> val, s--, t--;
    for (int i = 0; i < 12; i++) {
        int a;
        double b;
        cin >> a >> b;
        a--;
        p[a] = b;
    }
    int val = aStar();
    cout << ans << endl << val << endl;
}