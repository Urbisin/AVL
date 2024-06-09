#include <iostream>
#include "AVL.cpp"
using namespace std;

int main() {

    AVL arbol;

    arbol.insertar(10);
    arbol.insertar(20);
    arbol.insertar(30);
    arbol.insertar(40);
    arbol.insertar(50);
    arbol.insertar(25);

    arbol.inOrder();
    arbol.postOrder();
    arbol.preOrder();

    arbol.eliminar(10);
    arbol.inOrder();

    arbol.buscar(20) ? cout << "Encontrado" << endl : cout << "No encontrado" << endl;
    arbol.buscar(1) ? cout << "Encontrado" << endl : cout << "No encontrado" << endl;

    return 0;

}