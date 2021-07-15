#include <iomanip>
#include <iostream>
using namespace std;
int main() {
    double A = 1;
    double s = 2;

    while (s > 1) {
        A = A / 2;
        s = 1 + A;
    }
    cout << fixed << setprecision(30);
    cout << 2 * A << endl;
}