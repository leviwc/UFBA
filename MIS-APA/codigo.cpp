#include <bits/stdc++.h>

#include <chrono>

using namespace std;

#define int long long
const int INF = 2e18;

// melhorar performance no output
#define endl "\n"
// fast input
#define fastio      \
    cin.tie(NULL);  \
    cout.tie(NULL); \
    ios_base::sync_with_stdio(false)

const int N = 101;
int n;
int adj[N][N];
bitset<100> aux;
bool rec(int k) {
    vector<int> perm(n, 0);
    for (int i = n - 1; i >= n - k; i--) {
        perm[i] = 1;
    }
    do {
        bool impossible = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (perm[i] and perm[j] and adj[i + 1][j + 1]) {
                    impossible = true;
                    break;
                }
            }
            if (impossible) {
                break;
            }
        }
        if (impossible) continue;
        return true;
    } while (next_permutation(perm.begin(), perm.end()));
    return false;
}

// TETA(n*n * 2 ^n)
int brute() {
    int mai = 0;
    for (int i = 0; i < 1ll << n; i++) {
        int quantidadeDeBitsAtivos = 0;
        bool impossivel = false;
        for (int j = 0; j < n; j++) {
            quantidadeDeBitsAtivos += ((i >> j) & 1);
            for (int k = j + 1; k < n; k++) {
                if (((i >> j) & 1) and ((i >> k) & 1) and
                    adj[j + 1]
                       [k + 1]) {  // testando se ambos estão na possibilidade
                                   // atual e se tem ligação
                    impossivel = true;
                    break;
                }
            }
            if (impossivel) break;
        }
        if (impossivel) continue;
        // se for um independent set possivel guardar a quantidade de bits
        // ativos.
        mai = max(mai, quantidadeDeBitsAtivos);
    }
    return mai;
}
// O(combinatoria(n, n/2))*n;
int backTracking(bitset<100> &b, int pos) {
    if (pos > n) return 0;
    bool achou = false;
    for (int i = 1; i < pos; i++) {
        if (b[i] == 0) continue;
        if (adj[i][pos]) {
            achou = true;
        }
    }
    int ans = 0;
    if (!achou) {
        b[pos] = 1;
        ans = 1 + backTracking(b, pos + 1);
        b[pos] = 0;
    }
    return max(ans, backTracking(b, pos + 1));
}

int binarySearchOtimizada() {
    int qtdArestas = 0, threshold = ceil(n * log(n) / 2.0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            qtdArestas += adj[i][j];
        }
    }
    qtdArestas /= 2;

    int l = 1, r = n, div = (qtdArestas < threshold ? 2 : 10), resposta = 1;
    while (l <= r) {
        int med = l + (r - l) / div;
        if (div > 2) div--;
        if (rec(med)) {
            resposta = med;
            l = med + 1;
        } else {
            r = med - 1;
        }
    }
    return resposta;
}
int binarySearch() {
    int l = 1, r = n, resposta = 1;
    while (l <= r) {
        int med = (l + r) / 2;
        if (rec(med)) {
            resposta = med;
            l = med + 1;
        } else {
            r = med - 1;
        }
    }
    return resposta;
}
// revise as variaveis e a ordem nas funções
signed main() {
    fastio;
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a][b] = 1;
        adj[b][a] = 1;
    }

    // testando cada função:

    cout << fixed << setprecision(6);
    auto t1 = std::chrono::high_resolution_clock::now();
    cout << "Resultado com busca binaria: " << binarySearch() << endl;
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() /
        1000.0;
    cout << duration << " s" << endl;
    //
    //
    //
    //
    t1 = std::chrono::high_resolution_clock::now();
    cout << "Resultado com backtracking apenas: " << backTracking(aux, 1)
         << endl;
    t2 = std::chrono::high_resolution_clock::now();
    duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() /
        1000.0;
    cout << duration << " s" << endl;
    //
    //
    //
    //
    t1 = std::chrono::high_resolution_clock::now();

    cout << "Resultado testando todas as possibilidades: " << brute() << endl;
    t2 = std::chrono::high_resolution_clock::now();
    duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() /
        1000.0;
    cout << duration << " s" << endl;
    //
    //
    //
    //
    t1 = std::chrono::high_resolution_clock::now();

    cout << "Resultado com busca binaria otimizada: " << binarySearchOtimizada()
         << endl;
    t2 = std::chrono::high_resolution_clock::now();
    duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() /
        1000.0;
    cout << duration << " s" << endl;
}
