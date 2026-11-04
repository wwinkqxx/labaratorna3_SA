#include "splay.h"

BNode* rotRight(BNode* h) {
    BNode* x = h->l;
    h->l = x->r;
    x->r = h;
    return x;
}

BNode* rotLeft(BNode* h) {
    BNode* x = h->r;
    h->r = x->l;
    x->l = h;
    return x;
}

BNode* splay(BNode* h, int k) {
    if (!h) return h;
    if (k < h->key) {
        if (!h->l) return h;
        if (k < h->l->key) {
            h->l->l = splay(h->l->l, k);
            h = rotRight(h);
        } else if (k > h->l->key) {
            h->l->r = splay(h->l->r, k);
            if (h->l->r) h->l = rotLeft(h->l);
        }
        return h->l ? rotRight(h) : h;
    }
    if (k > h->key) {
        if (!h->r) return h;
        if (k > h->r->key) {
            h->r->r = splay(h->r->r, k);
            h = rotLeft(h);
        } else if (k < h->r->key) {
            h->r->l = splay(h->r->l, k);
            if (h->r->l) h->r = rotRight(h->r);
        }
        return h->r ? rotLeft(h) : h;
    }
    return h;
}

void insertS(BNode*& root, int k) {
    if (!root) { root = newB(k, false); return; }
    root = splay(root, k);
    if (root->key == k) return;
    BNode* n = newB(k, false);
    if (k < root->key) { n->l = root->l; n->r = root; root->l = nullptr; }
    else               { n->r = root->r; n->l = root; root->r = nullptr; }
    root = n;
}

bool searchS(BNode*& root, int k) {
    root = splay(root, k);
    return root && root->key == k;
}

void removeS(BNode*& root, int k) {
    if (!searchS(root, k)) return;
    BNode* t;
    if (!root->l) t = root->r;
    else {
        t = splay(root->l, k);
        t->r = root->r;
    }
    delete root;
    root = t;
}
