#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    int m;
    cin >> m;
    vector<double> x(m), y(m);
    for (double &a : x) cin >> a;
    for (double &a : y) cin >> a;
    double z;
    cin >> z;
    double r = 0;
    vector<double> dely(m);
    for (int i = 0; i < m; i++) {
        dely[i] = y[i];
    }
    for (int k = 0; k < m - 1; k++) {
        for (int i = m - 1; i > k; i--) {
            dely[i] = (dely[i] - dely[i - 1]) / (x[i] - x[i - k - 1]);
        }
    }
    r = dely[m - 1];
    for (int i = m - 2; i >= 0; i--) {
        r = r * (z - x[i]) + dely[i];
    }
    cout << r << endl;
}