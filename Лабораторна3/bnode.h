#pragma once

const int MAXN = 1000;

struct BNode {
    int key;
    bool red;
    BNode* l;
    BNode* r;
};

BNode* newB(int k, bool red);
int heightB(BNode* p);
void freeB(BNode* p);
BNode* copyB(BNode* p);
void toArrayB(BNode* p, int a[], int& n);
void printB(BNode* root, bool color);
