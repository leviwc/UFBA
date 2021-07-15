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
    if (r < l) return l;
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
    int n = randint(20, 30);
    int adj[n + 1][n + 1] = {{0}};
    int m = randint(n, n * (n - 1) / 2);
    cout << n << " " << m << endl;
    for (int i = 0; i < m; i++) {
        int a, b;
        a = randint(1, n), b = randint(1, n);
        while (adj[a][b] == 1) a = randint(1, n), b = randint(1, n);
        adj[a][b] = 1;
        adj[b][a] = 1;
        cout << a << " " << b << endl;
    }
}
