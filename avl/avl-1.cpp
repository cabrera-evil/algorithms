// ¿Cuál es la altura máxima de un AVL con 7 nodos? Asuma que la altura de un AVL con 1
// sólo nodo es 0.

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int nodos = 7;
    int altura_maxima = floor(log2(nodos + 1)) - 1;

    cout << "Altura máxima del AVL con " << nodos << " nodos: " << altura_maxima << std::endl;

    return 0;
}

