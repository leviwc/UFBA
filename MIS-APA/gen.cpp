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

int32_t main() { int n = randint(1, 20); }
