#include <bits/stdc++.h>

using namespace std;
bool colunaCriterio(vector<vector<double> >& mat) {
    int n = mat.size();
    for (int i = 0; i < n; i++) {
        double diag = abs(mat[i][i]);
        double sum = 0;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            sum += abs(mat[j][i]);
        }
        if (sum >= diag) return false;
    }
    return true;
}
bool linhaCriterio(vector<vector<double> >& mat) {
    int n = mat.size();
    for (int i = 0; i < n; i++) {
        double diag = abs(mat[i][i]);
        double sum = 0;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            sum += abs(mat[i][j]);
        }
        if (sum >= diag) return false;
    }
    return true;
}
bool funcErro(double x0, double x1, double e) {
    return (abs(x1 - x0) / abs(x1)) < e;
}
bool checkErro(vector<double>& x, vector<double>& novox, double e) {
    int n = x.size();
    for (int i = 0; i < n; i++) {
        if (!funcErro(x[i], novox[i], e)) {
            return false;
        }
    }
    return true;
}
void print(vector<double> x) {
    for (auto a : x) {
        cout << a << " ";
    }
    cout << endl;
}
bool sassenfieldCriterio(vector<vector<double> >& mat) {
    int n = mat.size();
    vector<double> beta(n);
    double mai = -1e9;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            beta[i] += (j < i ? beta[j] : 1.0) * mat[i][j];
        }
        beta[i] /= mat[i][i];
        mai = max(mai, beta[i]);
    }
    return mai < 1;
}
void troca(vector<vector<double> >& mat, vector<double>& b, int l1, int l2,
           int c1, int c2) {
    int n = mat.size();
    vector<vector<double> > res(n, vector<double>(n));
    vector<double> resb(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int l = i, c = j;
            if (l == l1) {
                l = l2;
            } else if (l == l2) {
                l = l1;
            }
            if (c == c1) {
                c = c2;
            } else if (c == c2) {
                c = c1;
            }
            resb[i] = b[l];
            res[i][j] = mat[l][c];
        }
    }
    mat = res;
    b = resb;
}
void testPermutacao(vector<vector<double> >& mat, vector<double>& b) {
    int n = mat.size();
    for (int l1 = 0; l1 < n; l1++) {
        for (int l2 = l1; l2 < n; l2++) {
            for (int c1 = 0; c1 < n; c1++) {
                for (int c2 = c1; c2 < n; c2++) {
                    troca(mat, b, l1, l2, c1, c2);
                    if (colunaCriterio(mat) or linhaCriterio(mat)) {
                        return;
                    }
                }
            }
        }
    }
}
int main() {
    int n;     // numero de variaveis
    double e;  // precisao
    cin >> n >> e;
    vector<double> x(n, 0), b(n);
    vector<vector<double> > mat(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];  // recebendo a matriz
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];  // recebendo o b_i
    }
    for (int i = 0; i < n; i++) {
        x[i] = b[i] / mat[i][i];
    }
    testPermutacao(mat, b);
    if (!colunaCriterio(mat) and !linhaCriterio(mat)) {
        cout << "não passou em criterio linha ou coluna" << endl;
        return 0;
    }
    if (!sassenfieldCriterio(mat)) {
        cout << "não passou no criterio sassenfield" << endl;
        return 0;
    }
    print(x);
    // iteração
    while (true) {
        vector<double> novox(n, 0);
        for (int i = 0; i < n; i++) {
            novox[i] += b[i];
            for (int j = 0; j < n; j++) {
                if (j == i) continue;
                novox[i] -= mat[i][j] * (j < i ? novox[j] : x[j]);
            }
            novox[i] /= mat[i][i];
        }
        if (checkErro(x, novox, e)) {
            x = novox;
            break;
        }
        x = novox;
        print(x);
    }
    print(x);
}