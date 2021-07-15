#include <bits/stdc++.h>

using namespace std;
double f(double x) { return 3.3833 * log(x) + 2.8119; }
int32_t main() {
    int n;
    cin >> n;
    double ymed = 0;
    vector<pair<double, double> > pontos;
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        pontos.push_back({x, y});
        ymed += y;
    }
    ymed /= n;
    double rquadrado = 0, sqreg = 0, sqtot = 0;
    for (int i = 0; i < n; i++) {
        sqreg += pow(f(pontos[i].first) - ymed, 2);
        sqtot += pow(f(pontos[i].first) - pontos[i].second, 2);
    }
    sqtot += sqreg;
    rquadrado = sqreg / sqtot;
    cout << rquadrado << endl;
}