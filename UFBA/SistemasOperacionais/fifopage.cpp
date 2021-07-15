#include <bits/stdc++.h>
using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> v(n);
    int mat[8][n];
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = -1;
        }
    }
    mat[0][0] = v[0];
    int at = 1;
    int qt = 0;
    int vet[8] = {0};
    for (int i = 1; i < 8; i++) {
        vet[i] = 10000000;
    }
    for (int i = 1; i < n; i++) {
        bool achou = false;
        for (int j = 0; j < 8; j++) {
            mat[j][i] = mat[j][i - 1];
        }
        for (int j = 0; j < 8; j++) {
            if (v[i] == mat[j][i - 1]) {
                vet[j] = i;
                achou = true;
                break;
            }
            if (mat[j][i - 1] == -1) {
                mat[j][i] = v[i];
                vet[j] = i;
                achou = true;
                break;
            }
        }
        if (achou) continue;
        int men = 100000;
        for (int j = 0; j < 8; j++) {
            men = min(men, vet[j]);
        }
        for (int j = 0; j < 8; j++) {
            if (vet[j] == men) {
                qt++;
                mat[j][i] = v[i];
                vet[j] = i;
                break;
            }
        }
    }

    for (int i = 7; i >= 0; i--) {
        cout << i << '&';
        for (int j = 0; j < n; j++) {
            cout << mat[i][j] << (j == n - 1 ? "" : "&");
        }
        cout << "\\\\" << endl;
        cout << "\\hline" << endl;
    }
    cout << "\\hline" << endl;
    cout << qt << endl;
}