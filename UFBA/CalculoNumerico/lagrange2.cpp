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
    for (int i = 0; i < m; i++) {
        double c = 1, d = 1;
        for (int j = 0; j < m; j++) {
            if (i != j) {
                c = c * (z - x[j]);
                d = d * (x[i] - x[j]);
            }
        }
        r = r + y[i] * (c / d);
    }
    cout << r << endl;
}