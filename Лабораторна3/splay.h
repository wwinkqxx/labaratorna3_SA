#pragma once
#include "bnode.h"

BNode* rotRight(BNode* h);
BNode* rotLeft(BNode* h);
BNode* splay(BNode* h, int k);
void insertS(BNode*& root, int k);
bool searchS(BNode*& root, int k);
void removeS(BNode*& root, int k);
