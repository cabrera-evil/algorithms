// Comenzando con un AVL vacío, muestre todo el procedimiento de ingresar los siguientes
// datos 1,2,3,4,5,6,7,8.

#include <iostream>

using namespace std;

// Definición de la estructura de un nodo AVL
struct AVLNode {
    int data;
    int height;
    AVLNode* left;
    AVLNode* right;
    
    AVLNode(int value) : data(value), height(1), left(nullptr), right(nullptr) {}
};

// Función para obtener la altura de un nodo
int getHeight(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// Función para obtener el factor de equilibrio de un nodo
int getBalanceFactor(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Función para realizar una rotación a la derecha
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Realizar la rotación
    x->right = y;
    y->left = T2;

    // Actualizar alturas
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Función para realizar una rotación a la izquierda
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Realizar la rotación
    y->left = x;
    x->right = T2;

    // Actualizar alturas
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Función para insertar un nodo en el árbol AVL
AVLNode* insertNode(AVLNode* root, int value) {
    // Paso 1: Realizar la inserción estándar de un BST
    if (root == nullptr) {
        return new AVLNode(value);
    }

    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    } else {
        // Los nodos duplicados no están permitidos en un AVL
        return root;
    }

    // Paso 2: Actualizar la altura del nodo actual
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Paso 3: Obtener el factor de equilibrio del nodo actual
    int balance = getBalanceFactor(root);

    // Paso 4: Realizar las rotaciones si es necesario
    // Rotación a la izquierda-izquierda (LL)
    if (balance > 1 && value < root->left->data) {
        return rightRotate(root);
    }
    // Rotación a la derecha-derecha (RR)
    if (balance < -1 && value > root->right->data) {
        return leftRotate(root);
    }
    // Rotación a la izquierda-derecha (LR)
    if (balance > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Rotación a la derecha-izquierda (RL)
    if (balance < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Devolver el nodo no modificado
    return root;
}

// Función para imprimir el árbol AVL en orden
void inOrderTraversal(AVLNode* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        cout << root->data << " ";
        inOrderTraversal(root->right);
    }
}

int main() {
    AVLNode* root = nullptr;

    // Insertar los datos 1, 2, 3, 4, 5, 6, 7, 8 en el AVL
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int numValues = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < numValues; ++i) {
        root = insertNode(root, values[i]);
    }

    // Imprimir el árbol AVL en orden
    cout << "Árbol AVL después de la inserción: ";
    inOrderTraversal(root);

    return 0;
}
