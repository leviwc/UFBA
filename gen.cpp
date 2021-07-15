#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> ii;
random_device ndgen;    // non-deterministic random generator.
mt19937 dgen(ndgen());  // deterministic random generator.

/**
 * Random Integer.
 *
 * Generates a random integer in the range
 * [l, r].
 *
 * Time Complexity: O(?).
 * Space Complexity: O(?).
 */
int randint(const int l, const int r) {
    uniform_int_distribution<int> distribution(l, r);
    return distribution(dgen);
}
namespace {
class Randomness {
   public:
    Randomness() {
        FILE *f = fopen("/dev/urandom", "r");
        uint32_t value;
        fread(&value, sizeof value, 1, f);
        srand(value);
    }
};
Randomness randomness;
}  // namespace

int32_t main() {
    int n = 5000;
    cout << 5000 << endl;
    int qt = randint(10000, 15000);
    cout << qt + n - 1 << endl;
    set<pair<int, int> > used;
    for (int i = 0; i < n - 1; i++) {
        cout << i + 1 << " " << i + 2 << " " << randint(1, 100000000) << endl;
    }
    while (qt--) {
        int a = randint(1, 5000), b = randint(1, 5000),
            c = randint(1, 1000000000);
        while (used.count(make_pair(a, b)) or used.count(make_pair(b, a))) {
            a = randint(1, 5000), b = randint(1, 5000),
            c = randint(1, 1000000000);
        }
        cout << a << " " << b << " " << c << endl;
        used.insert(make_pair(a, b));
    }
}
