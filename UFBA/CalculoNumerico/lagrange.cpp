#include <bits/stdc++.h>
using namespace std;
double tabela[100][100];
double lagrange(int m, int li, double x) {
    double cima, baixo;
    cima = baixo = 1;
    for (int i = 0; i < m; i++) {
        if (i == li) continue;
        cima *= (x - tabela[0][i]);
        baixo *= (tabela[0][li] - tabela[0][i]);
    }
    return cima / baixo;
}
int32_t main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> tabela[i][j];
        }
    }
    double x;
    cin >> x;
    double sum = 0;
    for (int i = 0; i < m; i++) {
        sum += lagrange(m, i, x) * tabela[1][i];
    }
    cout << sum << endl;
}
