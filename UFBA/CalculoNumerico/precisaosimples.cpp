#include <iomanip>
#include <iostream>
using namespace std;
int main() {
    float A = 1;
    float s = 2;

    while (s > 1) {
        A = A / 2;
        s = 1 + A;
    }
    cout << fixed << setprecision(30);
    cout << 2 * A << endl;
}