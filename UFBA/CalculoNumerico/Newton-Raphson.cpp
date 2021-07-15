#include <bits/stdc++.h>
using namespace std;
double f(double x) { return pow(x, 3.0) - (x)-1; }
double fLine(double x) { return 3 * pow(x, 2) - 1; }
signed main() {
    double x0 = 0, er = 0.000001, xLine;
    int k = 0;
    if (abs(f(x0)) < er) {
        xLine = x0;
    } else {
        while (true) {
            double x1 = x0 - f(x0) / fLine(x0);
            k++;
            printf("chute: %f , função: %f  \\\\ \n", x1, f(x1));
            if (abs(f(x1)) < er or abs(x1 - x0) < er) {
                xLine = x1;
                break;
            }
            x0 = x1;
        }
    }
    cout << fixed << setprecision(7) << abs((f(x0) - f(xLine)) / f(xLine))
         << endl;
    cout << fixed << setprecision(7) << "raiz aproximada final :" << xLine
         << " " << f(xLine) << " " << k << endl;
}