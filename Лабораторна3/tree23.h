#pragma once
#include "bnode.h"

struct Node23 {
    int n;
    int key[3];
    Node23* ch[4];
};

Node23* new23(int k);
bool isLeaf(Node23* p);
void insert23(Node23*& root, int k);
bool search23(Node23* p, int k);
void remove23(Node23*& root, int k);
int height23(Node23* p);
void free23(Node23* p);
Node23* copy23(Node23* p);
void toArray23(Node23* p, int a[], int& n);
void print23(Node23* root);
BNode* convert(Node23* p);
