#include <bits/stdc++.h>
using namespace std;
double f(double x) { return pow(x, 3.0) - (x)-1; }
signed main() {
    double l = 1, r = 2, e = 0.000001,
           med = (l * f(r) - r * f(l)) / (f(r) - f(l));
    int qt = 0;
    double ant = med;
    while (true) {
        med = (l * f(r) - r * f(l)) / (f(r) - f(l));
        qt++;
        printf(
            "intervalo [%f,%f], raiz aproximada %f, resultado da função %f "
            "\\\\ "
            "\n ",
            l, r, med, f(med));
        if (abs(f(med)) < e) {
            break;
        }
        if (f(med) > 0) {
            r = med;
        } else {
            l = med;
        }
        ant = med;
    }
    cout << abs((f(ant) - f(med)) / f(med)) << endl;

    cout << fixed << setprecision(6) << "raiz aproximada final :" << med << " "
         << f(med) << " " << qt << endl;
}