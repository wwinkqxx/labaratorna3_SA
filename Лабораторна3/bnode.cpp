#include <iostream>
#include "bnode.h"
using namespace std;

BNode* newB(int k, bool red) {
    BNode* p = new BNode;
    p->key = k;
    p->red = red;
    p->l = nullptr;
    p->r = nullptr;
    return p;
}

int heightB(BNode* p) {
    if (!p) return 0;
    int a = heightB(p->l), b = heightB(p->r);
    return 1 + (a > b ? a : b);
}

void freeB(BNode* p) {
    if (!p) return;
    freeB(p->l);
    freeB(p->r);
    delete p;
}

BNode* copyB(BNode* p) {
    if (!p) return nullptr;
    BNode* c = newB(p->key, p->red);
    c->l = copyB(p->l);
    c->r = copyB(p->r);
    return c;
}

void toArrayB(BNode* p, int a[], int& n) {
    if (!p) return;
    toArrayB(p->l, a, n);
    a[n++] = p->key;
    toArrayB(p->r, a, n);
}

void printB(BNode* root, bool color) {
    cout << "вузол\tрівень\tбатько\tбік\tключ";
    if (color) cout << "\tколір";
    cout << "\n";

    BNode* q[MAXN];
    int lev[MAXN], par[MAXN];
    bool isLeft[MAXN];
    int head = 0, tail = 0;
    if (root) { q[0] = root; lev[0] = 1; par[0] = 0; tail = 1; }

    while (head < tail) {
        BNode* p = q[head];
        cout << head + 1 << "\t" << lev[head] << "\t";
        if (par[head] == 0) cout << "-\t-\t";
        else cout << par[head] << "\t" << (isLeft[head] ? "лівий" : "правий") << "\t";
        cout << p->key;
        if (color) cout << "\t" << (p->red ? "червоний" : "чорний");
        cout << "\n";

        if (p->l) { q[tail] = p->l; lev[tail] = lev[head] + 1; par[tail] = head + 1; isLeft[tail] = true;  tail++; }
        if (p->r) { q[tail] = p->r; lev[tail] = lev[head] + 1; par[tail] = head + 1; isLeft[tail] = false; tail++; }
        head++;
    }
    cout << "висота: " << heightB(root) << "\n";
}
