#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define int long long
using namespace std;
vector<string> parse(string s) {
    vector<string> ans;
    string aux = "";
    bool achou = false;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            if (achou) ans.push_back(aux);
            achou = true;
            aux = "";
            continue;
        }
        aux += s[i];
    }
    if (aux != "") {
        ans.push_back(aux);
    }
    return ans;
}
signed main() {
    string s;
    cout << "{ " << endl;
    while (getline(cin, s)) {
        vector<string> parsed = parse(s);
        cout << "{ ";
        for (int i = 0; i < parsed.size(); i++) {
            if (parsed[i] == "-") {
                cout << -1;
            } else {
                cout << parsed[i];
            }
            if (i != parsed.size() - 1) cout << ", ";
        }
        cout << "}, " << endl;
    }
    cout << " }" << endl;
}