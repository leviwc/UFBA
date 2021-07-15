#include <math.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#define int long long
using namespace std;
int n;
bool ganhou(vector<vector<int> > &mat, bool eu) {
    int qt = 0;
    for (int i = 0; i < n; i++) {
        bool achou1 = true, achou2 = true;
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == -1) {
                qt++;
            }
            if (mat[i][j] != eu) {
                achou1 = false;
            }
            if (mat[j][i] != eu) {
                achou2 = false;
            }
        }
        if (achou1 or achou2) {
            return true;
        }
    }

    return (qt == 0);
}
int rec(vector<vector<int> > &mat, bool eu) {
    if (ganhou(mat, 0)) return 1;
    if (ganhou(mat, 1)) return 0;
    int qt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == -1) {
                if (eu) {
                    mat[i][j] = 1;
                    qt += rec(mat, !eu);
                    mat[i][j] = -1;
                } else {
                    mat[i][j] = 0;
                    qt += rec(mat, !eu);
                    mat[i][j] = -1;
                }
            }
        }
    }
    return qt;
}
signed main() {
    cin >> n;
    vector<vector<int> > mat(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }
    int val = 1e18, ii = 0, jj = 0;
    if (ganhou(mat, 1) or ganhou(mat, 0)) {
        cout << -1 << "," << -1 << endl;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int aux = 1e18;
            if (mat[i][j] == -1) {
                mat[i][j] = 1;
                aux = rec(mat, 0);
                mat[i][j] = -1;
            }
            if (aux < val) {
                val = aux;
                ii = i, jj = j;
            }
        }
    }
    cout << ii << "," << jj << endl;
}