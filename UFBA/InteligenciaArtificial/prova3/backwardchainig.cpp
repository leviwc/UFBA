#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
vector<string> expr;
set<string> fatos;
int qt;
bool isFato(string aux) {
    if (fatos.count(aux)) {
        return true;
    }
    qt++;
    if (qt > 1000) {
        return false;
    }
    for (auto x : expr) {
        string esquerda = "";
        for (int i = (int)x.size() - 1; x[i] != ' '; i--) {
            esquerda += x[i];
        }
        if (esquerda != aux) {
            continue;
        }
        string ee = "";
        bool ans = isFato(ee + x[0]);
        for (int i = 2; i < (int)x.size(); i++) {
            ee = "";
            if (x[i] == '=') {
                break;
            }
            if (x[i] == '|') {
                if (ans) break;
                ans = isFato(ee + x[i + 2]);
                i += 3;
            } else if (x[i] == '^') {
                ans &= isFato(ee + x[i + 2]);
                i += 3;
            }
        }
        if (ans) return true;
    }
    return false;
}
int32_t main() {
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        string e;
        getline(cin, e);
        expr.push_back(e);
    }

    string fato;
    cin >> fato;
    string fa = "";
    for (int i = 0; i < (int)fato.size(); i++) {
        if (fato[i] == ',') {
            fatos.insert(fa);
            fa = "";
            continue;
        }
        fa += fato[i];
    }
    fatos.insert(fa);
    string pergunta;
    cin >> pergunta;
    if (isFato(pergunta)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
}