#include <bits/stdc++.h>

using namespace std;
struct Gauss {
    vector<vector<double>> a;
    void add_eq(vector<double> &v) { a.push_back(v); }
    const double EPS = 1e-9;
    const int INF =
        2;  // it doesn't actually have to be infinity or a big number
    int gauss(vector<double> &ans) {
        int n = (int)a.size();
        int m = (int)a[0].size() - 1;
        vector<int> where(m, -1);
        for (int col = 0, row = 0; col < m && row < n; ++col) {
            int sel = row;
            for (int i = row; i < n; ++i)
                if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
            if (abs(a[sel][col]) < EPS) continue;
            for (int i = col; i <= m; ++i) swap(a[sel][i], a[row][i]);
            where[col] = row;

            for (int i = 0; i < n; ++i)
                if (i != row) {
                    double c = a[i][col] / a[row][col];
                    for (int j = col; j <= m; ++j) a[i][j] -= a[row][j] * c;
                }
            ++row;
        }
        ans.assign(m, 0);
        for (int i = 0; i < m; ++i)
            if (where[i] != -1) {
                ans[i] = a[where[i]][m] / a[where[i]][i];
            }
        for (int i = 0; i < n; ++i) {
            double sum = 0;
            for (int j = 0; j < m; ++j) sum += ans[j] * a[i][j];
            if (abs(sum - a[i][m]) > EPS) return 0;
        }

        for (int i = 0; i < m; ++i)
            if (where[i] == -1) return INF;
        return 1;
    }
};
int32_t main() {
    int n, m;
    cin >> n >> m;
    Gauss gaus;
    for (int i = 0; i < n; i++) {
        vector<double> a(m + 1);
        for (int j = 0; j <= m; j++) {
            cin >> a[j];
        }
        gaus.add_eq(a);
    }
    vector<double> ans;
    if (gaus.gauss(ans) != 0) {
        double sum = 0;
        for (int i = 0; i < ans.size(); i++) {
            sum += ans[i] * pow(5, i);
        }
        cout << sum << endl;
    } else {
        cout << "you are dumb" << endl;
    }
}