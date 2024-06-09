#include <iostream>
using namespace std;

class Nodo {
public:
    int dato;
    Nodo* izq;
    Nodo* der;
    int altura;

    Nodo(int val) : dato(val), izq(NULL), der(NULL), altura(1) {}
};

class AVL {
private:
    Nodo* raiz;

    int altura(Nodo* N) {
        return (N == NULL) ? 0 : N->altura;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Nodo* nuevoNodo(int dato) {
        return new Nodo(dato);
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
        return (N == NULL) ? 0 : altura(N->izq) - altura(N->der);
    }

    Nodo* insertar(Nodo* nodo, int dato) {
        if (nodo == NULL)
            return nuevoNodo(dato);

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

    Nodo* minValueNode(Nodo* nodo) {
        Nodo* actual = nodo;
        while (actual->izq != NULL)
            actual = actual->izq;
        return actual;
    }

    Nodo* eliminar(Nodo* raiz, int dato) {
        if (raiz == NULL)
            return raiz;

        if (dato < raiz->dato)
            raiz->izq = eliminar(raiz->izq, dato);
        else if (dato > raiz->dato)
            raiz->der = eliminar(raiz->der, dato);
        else {
            if ((raiz->izq == NULL) || (raiz->der == NULL)) {
                Nodo* temp = raiz->izq ? raiz->izq : raiz->der;
                if (temp == NULL) {
                    temp = raiz;
                    raiz = NULL;
                } else
                    *raiz = *temp;
                delete temp;
            } else {
                Nodo* temp = minValueNode(raiz->der);
                raiz->dato = temp->dato;
                raiz->der = eliminar(raiz->der, temp->dato);
            }
        }

        if (raiz == NULL)
            return raiz;

        raiz->altura = 1 + max(altura(raiz->izq), altura(raiz->der));
        int balance = getBalance(raiz);

        if (balance > 1 && getBalance(raiz->izq) >= 0)
            return rotarDerecha(raiz);

        if (balance > 1 && getBalance(raiz->izq) < 0) {
            raiz->izq = rotarIzquierda(raiz->izq);
            return rotarDerecha(raiz);
        }

        if (balance < -1 && getBalance(raiz->der) <= 0)
            return rotarIzquierda(raiz);

        if (balance < -1 && getBalance(raiz->der) > 0) {
            raiz->der = rotarDerecha(raiz->der);
            return rotarIzquierda(raiz);
        }

        return raiz;
    }

    bool buscar(Nodo* nodo, int dato) {
        while (nodo != NULL) {
            if (dato < nodo->dato)
                nodo = nodo->izq;
            else if (dato > nodo->dato)
                nodo = nodo->der;
            else
                return true;
        }
        return false;
    }

    void inOrder(Nodo* raiz) {
        if (raiz != NULL) {
            inOrder(raiz->izq);
            cout << raiz->dato << " ";
            inOrder(raiz->der);
        }
    }

    void preOrder(Nodo* raiz) {
        if (raiz != NULL) {
            cout << raiz->dato << " ";
            preOrder(raiz->izq);
            preOrder(raiz->der);
        }
    }

    void postOrder(Nodo* raiz) {
        if (raiz != NULL) {
            postOrder(raiz->izq);
            postOrder(raiz->der);
            cout << raiz->dato << " ";
        }
    }

public:
    AVL() : raiz(NULL) {}

    void insertar(int dato) {
        raiz = insertar(raiz, dato);
    }

    void eliminar(int dato) {
        raiz = eliminar(raiz, dato);
    }

    bool buscar(int dato) {
        return buscar(raiz, dato);
    }

    void inOrder() {
        inOrder(raiz);
        cout << endl;
    }

    void preOrder() {
        preOrder(raiz);
        cout << endl;
    }

    void postOrder() {
        postOrder(raiz);
        cout << endl;
    }
};
