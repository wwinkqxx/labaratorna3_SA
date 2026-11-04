#include <iostream>
#include <windows.h>
#include "bnode.h"
#include "splay.h"
#include "tree23.h"
using namespace std;

void printAll(BNode* s1, BNode* s2, Node23* t1, Node23* t2) {
    cout << "\nSplay-дерево T1:\n"; printB(s1, false);
    cout << "\nSplay-дерево T2:\n"; printB(s2, false);
    cout << "\n2-3 дерево T1:\n";   print23(t1);
    cout << "\n2-3 дерево T2:\n";   print23(t2);
}

void printList(int a[], int n) {
    if (n == 0) cout << "немає";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
}

int main() {
    SetConsoleOutputCP(65001);

    BNode* s1 = nullptr;   BNode* s2 = nullptr;
    Node23* t1 = nullptr;  Node23* t2 = nullptr;
    int n, k;

    cout << "Кількість ключів першого набору: ";
    cin >> n;
    cout << "Ключі: ";
    for (int i = 0; i < n; i++) { cin >> k; insertS(s1, k); insert23(t1, k); }

    cout << "Кількість ключів другого набору: ";
    cin >> n;
    cout << "Ключі: ";
    for (int i = 0; i < n; i++) { cin >> k; insertS(s2, k); insert23(t2, k); }

    cout << "\n~~~~~ Початкові дерева ~~~~~";
    printAll(s1, s2, t1, t2);

    int a[MAXN], cnt;

    cout << "\n~~~~~ Завдання А: другий найменший ключ дерева T ~~~~~\n";
    cnt = 0; toArrayB(s1, a, cnt);
    cout << "splay-дерево: ";
    if (cnt >= 2) cout << a[1] << "\n"; else cout << "немає\n";
    cnt = 0; toArray23(t1, a, cnt);
    cout << "2-3 дерево: ";
    if (cnt >= 2) cout << a[1] << "\n"; else cout << "немає\n";
    printAll(s1, s2, t1, t2);

    cout << "\n~~~~~ Завдання Б: видалити з T найменший ключ ~~~~~\n";
    cnt = 0; toArrayB(s1, a, cnt);
    cout << "splay-дерево, видалено: ";
    if (cnt > 0) { cout << a[0] << "\n"; removeS(s1, a[0]); } else cout << "немає\n";
    cnt = 0; toArray23(t1, a, cnt);
    cout << "2-3 дерево, видалено: ";
    if (cnt > 0) { cout << a[0] << "\n"; remove23(t1, a[0]); } else cout << "немає\n";
    printAll(s1, s2, t1, t2);

    cout << "\n~~~~~ Завдання В: об'єднати T1 і T2 ~~~~~\n";
    BNode* sCopy = copyB(s1);
    Node23* tCopy = copy23(t1);
    cnt = 0; toArrayB(s2, a, cnt);
    for (int i = 0; i < cnt; i++) insertS(s1, a[i]);
    cnt = 0; toArray23(t2, a, cnt);
    for (int i = 0; i < cnt; i++) insert23(t1, a[i]);

    cnt = 0; toArrayB(s1, a, cnt);
    cout << "splay-дерево, ключі об'єднаного дерева: "; printList(a, cnt);
    cnt = 0; toArray23(t1, a, cnt);
    cout << "2-3 дерево, ключі об'єднаного дерева: "; printList(a, cnt);
    printAll(s1, s2, t1, t2);
    cout << "\nКопія splay-дерева T1 (до об'єднання):\n"; printB(sCopy, false);
    cout << "\nКопія 2-3 дерева T1 (до об'єднання):\n";   print23(tCopy);

    cout << "\n~~~~~ Завдання Г: 2-3 дерево T -> ліве червоно-чорне ~~~~~\n";
    BNode* rb = convert(t1);
    cnt = 0; toArrayB(rb, a, cnt);
    cout << "ключі отриманого дерева: "; printList(a, cnt);
    printAll(s1, s2, t1, t2);
    cout << "\n2-3 дерево T до перетворення:\n"; print23(t1);
    cout << "\nЛіве червоно-чорне дерево після перетворення:\n"; printB(rb, true);

    freeB(s1); freeB(s2); freeB(sCopy); freeB(rb);
    free23(t1); free23(t2); free23(tCopy);
    return 0;
}
