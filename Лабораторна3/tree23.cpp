#include <iostream>
#include "tree23.h"
using namespace std;

Node23* new23(int k) {
    Node23* p = new Node23;
    p->n = 1;
    p->key[0] = k;
    for (int i = 0; i < 4; i++) p->ch[i] = nullptr;
    return p;
}

bool isLeaf(Node23* p) { return p->ch[0] == nullptr; }

void putAt(Node23* p, int i, int k, Node23* r) {
    for (int j = p->n; j > i; j--) {
        p->key[j] = p->key[j - 1];
        p->ch[j + 1] = p->ch[j];
    }
    p->key[i] = k;
    p->ch[i + 1] = r;
    p->n++;
}

void takeAt(Node23* p, int i) {
    for (int j = i; j < p->n - 1; j++) {
        p->key[j] = p->key[j + 1];
        p->ch[j + 1] = p->ch[j + 2];
    }
    p->ch[p->n] = nullptr;
    p->n--;
}

void split(Node23* p, int i) {
    Node23* c = p->ch[i];
    Node23* r = new23(c->key[2]);
    r->ch[0] = c->ch[2];
    r->ch[1] = c->ch[3];
    c->ch[2] = c->ch[3] = nullptr;
    c->n = 1;
    putAt(p, i, c->key[1], r);
}

void ins23(Node23* p, int k) {
    int i = 0;
    while (i < p->n && k > p->key[i]) i++;
    if (i < p->n && p->key[i] == k) return;
    if (isLeaf(p)) putAt(p, i, k, nullptr);
    else {
        ins23(p->ch[i], k);
        if (p->ch[i]->n == 3) split(p, i);
    }
}

void insert23(Node23*& root, int k) {
    if (!root) { root = new23(k); return; }
    ins23(root, k);
    if (root->n == 3) {
        Node23* t = new23(0);
        t->n = 0;
        t->ch[0] = root;
        root = t;
        split(root, 0);
    }
}

bool search23(Node23* p, int k) {
    while (p) {
        int i = 0;
        while (i < p->n && k > p->key[i]) i++;
        if (i < p->n && p->key[i] == k) return true;
        p = p->ch[i];
    }
    return false;
}

int min23(Node23* p) {
    while (!isLeaf(p)) p = p->ch[0];
    return p->key[0];
}

void fix(Node23* p, int i) {
    Node23* c = p->ch[i];
    if (i > 0 && p->ch[i - 1]->n == 2) {
        Node23* l = p->ch[i - 1];
        c->ch[1] = c->ch[0];
        c->ch[0] = l->ch[2];
        c->key[0] = p->key[i - 1];
        c->n = 1;
        p->key[i - 1] = l->key[1];
        l->ch[2] = nullptr;
        l->n = 1;
    } else if (i < p->n && p->ch[i + 1]->n == 2) {
        Node23* r = p->ch[i + 1];
        c->key[0] = p->key[i];
        c->ch[1] = r->ch[0];
        c->n = 1;
        p->key[i] = r->key[0];
        r->key[0] = r->key[1];
        r->ch[0] = r->ch[1];
        r->ch[1] = r->ch[2];
        r->ch[2] = nullptr;
        r->n = 1;
    } else if (i > 0) {
        Node23* l = p->ch[i - 1];
        l->key[1] = p->key[i - 1];
        l->ch[2] = c->ch[0];
        l->n = 2;
        delete c;
        takeAt(p, i - 1);
    } else {
        Node23* r = p->ch[1];
        c->key[0] = p->key[0];
        c->key[1] = r->key[0];
        c->ch[1] = r->ch[0];
        c->ch[2] = r->ch[1];
        c->n = 2;
        delete r;
        takeAt(p, 0);
    }
}

void del23(Node23* p, int k) {
    int i = 0;
    while (i < p->n && k > p->key[i]) i++;
    if (isLeaf(p)) {
        if (i < p->n && p->key[i] == k) takeAt(p, i);
        return;
    }
    if (i < p->n && p->key[i] == k) {
        p->key[i] = min23(p->ch[i + 1]);
        k = p->key[i];
        i++;
    }
    del23(p->ch[i], k);
    if (p->ch[i]->n == 0) fix(p, i);
}

void remove23(Node23*& root, int k) {
    if (!root) return;
    del23(root, k);
    if (root->n == 0) {
        Node23* t = root;
        root = root->ch[0];
        delete t;
    }
}

int height23(Node23* p) {
    int h = 0;
    while (p) { h++; p = p->ch[0]; }
    return h;
}

void free23(Node23* p) {
    if (!p) return;
    for (int i = 0; i <= p->n; i++) free23(p->ch[i]);
    delete p;
}

Node23* copy23(Node23* p) {
    if (!p) return nullptr;
    Node23* c = new23(0);
    c->n = p->n;
    for (int i = 0; i < p->n; i++) c->key[i] = p->key[i];
    for (int i = 0; i <= p->n; i++) c->ch[i] = copy23(p->ch[i]);
    return c;
}

void toArray23(Node23* p, int a[], int& n) {
    if (!p) return;
    for (int i = 0; i < p->n; i++) {
        toArray23(p->ch[i], a, n);
        a[n++] = p->key[i];
    }
    toArray23(p->ch[p->n], a, n);
}

void print23(Node23* root) {
    cout << "вузол\tрівень\tбатько\tнащадок\tключі\n";
    Node23* q[MAXN];
    int lev[MAXN], par[MAXN], num[MAXN];
    int head = 0, tail = 0;
    if (root) { q[0] = root; lev[0] = 1; par[0] = 0; tail = 1; }

    while (head < tail) {
        Node23* p = q[head];
        cout << head + 1 << "\t" << lev[head] << "\t";
        if (par[head] == 0) cout << "-\t-\t";
        else cout << par[head] << "\t" << num[head] << "\t";
        cout << p->key[0];
        if (p->n == 2) cout << " " << p->key[1];
        cout << "\n";

        if (!isLeaf(p))
            for (int i = 0; i <= p->n; i++) {
                q[tail] = p->ch[i];
                lev[tail] = lev[head] + 1;
                par[tail] = head + 1;
                num[tail] = i + 1;
                tail++;
            }
        head++;
    }
    cout << "висота: " << height23(root) << "\n";
}

BNode* convert(Node23* p) {
    if (!p) return nullptr;
    if (p->n == 1) {
        BNode* x = newB(p->key[0], false);
        x->l = convert(p->ch[0]);
        x->r = convert(p->ch[1]);
        return x;
    }
    BNode* x = newB(p->key[1], false);
    BNode* y = newB(p->key[0], true);
    y->l = convert(p->ch[0]);
    y->r = convert(p->ch[1]);
    x->l = y;
    x->r = convert(p->ch[2]);
    return x;
}
