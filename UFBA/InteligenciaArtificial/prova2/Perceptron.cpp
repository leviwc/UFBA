#include <iomanip>
#include <iostream>
using namespace std;

int32_t main() {
    cout << fixed << setprecision(1);
    int n, m;
    cin >> n >> m;
    double bias, taxaAp;
    cin >> bias >> taxaAp;
    double pesos[m - 1];
    for (int i = 0; i < m - 1; i++) {
        cin >> pesos[i];
    }
    int tabela[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> tabela[i][j];
        }
    }
    for (int i = 0; i < 100; i++) {
        int qt = 0;
        for (int j = 0; j < n; j++) {
            double u = bias;
            for (int e = 0; e < m - 1; e++) {
                u += pesos[e] * tabela[j][e];
            }
            int ans = (u < 0 ? -1 : 1);
            if (ans != tabela[j][m - 1]) {
                for (int e = 0; e < m - 1; e++) {
                    pesos[e] = pesos[e] +
                               taxaAp * (tabela[j][m - 1] - ans) * tabela[j][e];
                }
                bias = bias + taxaAp * (tabela[j][m - 1] - ans);
                qt++;
            }
        }
        if (qt == 0) break;
    }
    for (int i = 0; i < m - 1; i++) {
        cout << pesos[i] << " ";
    }
    cout << bias << " ";
    cout << endl;
    int testes;
    cin >> testes;
    for (int i = 0; i < testes; i++) {
        double u = bias;
        for (int j = 0; j < m - 1; j++) {
            int a;
            cin >> a;
            u += pesos[j] * a;
        }
        cout << (u < 0 ? -1 : 1) << endl;
    }
}