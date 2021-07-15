#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
vector<string> fatos;
vector<string> ids;
pair<string, int> pega(string aux, int pos) {
    string ans = "";
    int abre = 0, posf = pos;
    for (int i = pos; i < (int)aux.size(); i++) {
        abre += (aux[i] == '(');
        abre -= (aux[i] == ')');
        if (abre < 0) {
            break;
        }
        if (abre == 0 and aux[i] == ',') {
            break;
        }
        ans += aux[i];
        posf = i;
    }
    return {ans, posf};
}
bool isFunc(string aux) { return aux[(int)aux.size() - 1] == ')'; }
bool isVar(string aux) { return (aux[0] >= 'A' and aux[0] <= 'Z'); }
map<string, string> m;
string aux;
vector<string> vars;
vector<string> anse;
void rec(int pos) {
    if (pos == (int)vars.size()) {
        string ans = "";
        for (int i = 0; i < (int)aux.size(); i++) {
            auto a = pega(aux, i);
            if (isVar(a.first)) {
                ans += m[a.first];
                i = a.second;
            } else {
                ans += aux[i];
            }
        }
        if (binary_search(fatos.begin(), fatos.end(), ans)) {
            for (auto x : m) {
                string ee = x.first + "/" + x.second;
                bool achou = false;
                for (int i = 0; i < (int)anse.size(); i++) {
                    if (ee == anse[i]) achou = true;
                }
                if (!achou) anse.push_back(ee);
            }
        }
    } else {
        for (int i = 0; i < (int)ids.size(); i++) {
            m[vars[pos]] = ids[i];
            rec(pos + 1);
        }
    }
}
int32_t main() {
    while (true) {
        string a;
        cin >> a;
        if (a == "END") {
            break;
        }
        fatos.push_back(a);
        string id = "";
        for (int j = 0; j < (int)a.size(); j++) {
            if (a[j] == '(' or a[j] == ')' or a[j] == ',') {
                if (id != "") ids.push_back(id);
                id = "";
            } else {
                id += a[j];
            }
        }
        if (id != "") ids.push_back(id);
    }
    sort(fatos.begin(), fatos.end());

    m.clear();
    vars.clear();
    anse.clear();
    cin >> aux;
    for (int i = 0; i < (int)aux.size(); i++) {
        if (aux[i] >= 'A' and aux[i] <= 'Z') {
            vars.push_back(pega(aux, i).first);
        }
    }
    if (vars.size() == 0) {
        cout << (!binary_search(fatos.begin(), fatos.end(), aux) ? "FALSE"
                                                                 : "TRUE")
             << endl;
    } else {
        rec(0);
        int e = 0;
        for (int i = 0; i < (int)anse.size(); i++) {
            cout << anse[i] << (e != (int)anse.size() - 1 ? "," : "");
            e++;
        }
        cout << endl;
    }
}

// origin(origin(a,R),R)