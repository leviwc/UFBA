#include <bits/stdc++.h>
using namespace std;
double f(double x) { return pow(x, 3.0) - (x)-1; }
signed main() {
    double x0 = 0, x1 = 0.5, er = 0.000001, xLine;
    int k = 0;
    if (abs(f(x0)) < er) {
        xLine = x0;
    } else if (abs(f(x1)) < er or abs(x1 - x0) < er) {
        xLine = x1;
    } else {
        while (true) {
            k++;
            double x2 = x1 - (f(x1) / (f(x1) - f(x0))) * (x1 - x0);
            printf("chute: %f , função: %f  \\\\ \n", x2, f(x2));
            if (abs(f(x2)) < er or abs(x2 - x1) < er) {
                xLine = x2;
                break;
            }
            x0 = x1;
            x1 = x2;
        }
    }
    cout << fixed << setprecision(7) << abs((f(x1) - f(xLine)) / f(xLine))
         << endl;
    cout << fixed << setprecision(9) << "raiz aproximada final :" << xLine
         << " " << f(xLine) << " " << k << endl;
}