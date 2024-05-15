#include <iostream>
using namespace std;

class Nodo {
public:
    int dato;
    Nodo* izq;
    Nodo* der;
    int altura;
};

class AVL {
public:
    Nodo* raiz;

    int altura(Nodo* N) {
        if (N == NULL)
            return 0;
        return N->altura;
    }

    int max(int a, int b) {
        return (a > b)? a : b;
    }

    Nodo* nuevoNodo(int dato) {
        Nodo* nodo = new Nodo();
        nodo->dato = dato;
        nodo->izq = NULL;
        nodo->der = NULL;
        nodo->altura = 1;
        return(nodo);
    }

    Nodo* rotarDerecha(Nodo* y) {
        Nodo* x = y->izq;
        Nodo* T2 = x->der;
        x->der = y;
        y->izq = T2;
        y->altura = max(altura(y->izq), altura(y->der)) + 1;
        x->altura = max(altura(x->izq), altura(x->der)) + 1;
        return x;
    }

    Nodo* rotarIzquierda(Nodo* x) {
        Nodo* y = x->der;
        Nodo* T2 = y->izq;
        y->izq = x;
        x->der = T2;
        x->altura = max(altura(x->izq), altura(x->der)) + 1;
        y->altura = max(altura(y->izq), altura(y->der)) + 1;
        return y;
    }

    int getBalance(Nodo* N) {
        if (N == NULL)
            return 0;
        return altura(N->izq) - altura(N->der);
    }

    Nodo* insertar(Nodo* nodo, int dato) {
        if (nodo == NULL)
            return(nuevoNodo(dato));
        if (dato < nodo->dato)
            nodo->izq = insertar(nodo->izq, dato);
        else if (dato > nodo->dato)
            nodo->der = insertar(nodo->der, dato);
        else
            return nodo;

        nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));

        int balance = getBalance(nodo);

        if (balance > 1 && dato < nodo->izq->dato)
            return rotarDerecha(nodo);

        if (balance < -1 && dato > nodo->der->dato)
            return rotarIzquierda(nodo);

        if (balance > 1 && dato > nodo->izq->dato) {
            nodo->izq = rotarIzquierda(nodo->izq);
            return rotarDerecha(nodo);
        }

        if (balance < -1 && dato < nodo->der->dato) {
            nodo->der = rotarDerecha(nodo->der);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    bool buscar(Nodo* raiz, int dato) {
        while (raiz != NULL) {
            if (dato < raiz->dato)
                raiz = raiz->izq;
            else if (dato > raiz->dato)
                raiz = raiz->der;
            else
                return true;
        }
        return false;
    }
};