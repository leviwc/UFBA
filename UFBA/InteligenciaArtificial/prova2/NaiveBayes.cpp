#include <iostream>

using namespace std;

int32_t main() {
    int n, m;
    cin >> n >> m;
    int mat[n][m];
    int teste[m - 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }
    for (int i = 0; i < m - 1; i++) {
        cin >> teste[i];
    }
    int sim[m] = {0}, nao[m] = {0};
    for (int i = 0; i < n; i++) {
        bool final = mat[i][m - 1];
        for (int j = 0; j < m - 1; j++) {
            if (final and mat[i][j]) {
                sim[j]++;
            }
            if (!final and !mat[i][j]) {
                nao[j]++;
            }
        }
        if (final) {
            sim[m - 1]++;
        } else {
            nao[m - 1]++;
        }
    }
    double probsim = 1, probnao = 1;
    for (int i = 0; i < m; i++) {
        probsim *= sim[i] / (double)n;
        probnao *= nao[i] / (double)n;
    }
    if (probsim > probnao) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
}