#include <math.h>

#include <iostream>
#include <vector>
using namespace std;
struct node {
    int id;
    int l = -1;
    int r = -1;
    int classe = -1;
    int atributo = -1;
    node(){};
};
double entropia(vector<vector<int> > exemplos) {
    if (exemplos.size() == 0) return 0;
    int m = exemplos[0].size();
    double positivo, negativo;
    positivo = negativo = 0;
    for (int i = 0; i < (int)exemplos.size(); i++) {
        if (exemplos[i][m - 1] == 0) negativo++;
        if (exemplos[i][m - 1] == 1) positivo++;
    }
    if (negativo == 0 or positivo == 0) {
        return 0;
    }
    if (negativo == positivo) return 1;
    positivo /= exemplos.size();
    negativo /= exemplos.size();
    return -positivo * log2(positivo) - negativo * log2(negativo);
}
void imprime(node no) {
    cout << "esse sera um no  \\\\\\\\\\\\\\\\\\\\\\\\" << endl;
    cout << "id " << no.id << endl;
    cout << "ligacoes " << no.l << "  " << no.r << endl;
    cout << "classes " << no.classe << endl;
    cout << "atributos " << no.atributo << endl;
    cout << "esse foi um no \\\\\\\\\\\\\\\\\\\\\\\\\\\\ " << endl;
}
vector<node> tree;
int cria(vector<vector<int> > exemplos, vector<int> atributos) {
    int m = exemplos[0].size();
    tree.push_back(node());
    node &no = tree[tree.size() - 1];
    no.id = tree.size() - 1;
    int positivo = 0, negativo = 0;
    for (int i = 0; i < (int)exemplos.size(); i++) {
        if (exemplos[i][m - 1] == 0) negativo++;
        if (exemplos[i][m - 1] == 1) positivo++;
    }
    if (negativo == 0) {
        no.classe = 1;
    } else if (positivo == 0) {
        no.classe = 0;
    } else {
        if ((int)atributos.size() == 0) {
            no.classe = (positivo > negativo ? 1 : 0);
        } else {
            double ganho = -1e9;
            int atributo = -1;
            for (int i = 0; i < (int)atributos.size(); i++) {
                vector<vector<int> > v1, v0;
                double ganhox = entropia(exemplos);
                for (int j = 0; j < (int)exemplos.size(); j++) {
                    if (exemplos[j][atributos[i]] == 0) {
                        v0.push_back(exemplos[j]);
                    } else {
                        v1.push_back(exemplos[j]);
                    }
                }
                ganhox -= (v0.size() / (int)exemplos.size()) * entropia(v0);
                ganhox -= (v1.size() / (int)exemplos.size()) * entropia(v1);
                if (ganhox > ganho) {
                    ganho = ganhox;
                    atributo = atributos[i];
                }
            }
            vector<vector<int> > v1, v0;
            for (int j = 0; j < (int)exemplos.size(); j++) {
                if (exemplos[j][atributos[atributo]] == 0) {
                    v0.push_back(exemplos[j]);
                } else {
                    v1.push_back(exemplos[j]);
                }
            }

            no.atributo = atributo;
            vector<int> novosatributos;
            for (int i : atributos) {
                if (i != atributo) novosatributos.push_back(i);
            }
            if (v0.size() == 0) {
                tree.push_back(node());
                no.l = tree.size() - 1;
                tree[tree.size() - 1].id = tree.size() - 1;
                tree[tree.size() - 1].classe = 0;
            } else {
                cout << no.l << endl;
                no.l = cria(v0, novosatributos);
            }
            if (v1.size() == 0) {
                tree.push_back(node());
                no.r = tree.size() - 1;
                tree[tree.size() - 1].id = tree.size() - 1;
                tree[tree.size() - 1].classe = 1;
            } else {
                no.r = cria(v1, novosatributos);
            }
        }
    }
    return no.id;
}
int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > exemplos(n, vector<int>(m));
    vector<int> atributos;
    for (int i = 0; i < m - 1; i++) atributos.push_back(i);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> exemplos[i][j];
        }
    }
    cout << 0 << endl;
    return 0;
    cria(exemplos, atributos);
    vector<int> teste(m - 1);
    for (int i = 0; i < (int)tree.size(); i++) {
        imprime(tree[i]);
    }
    for (int &i : teste) cin >> i;
    int at = 0;
    while (tree[at].classe == -1) {
        if (teste[tree[at].atributo] == 0) {
            at = tree[at].l;
        } else {
            at = tree[at].r;
        }
    }
    cout << tree[at].classe << endl;
    return 0;
}