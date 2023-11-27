/* Comenzando con un AVL vacío, muestre todo el procedimiento de ingresar los siguientes
datos 1,2,3,4,5,6,11,13,12,10,9,8,7.
a. Luego, muestre todo el procedimiento de borrar los siguientes datos 10,9,7,8.
b. Luego, muestre todo el procedimiento de borrar el 13.
c. Luego, muestre todo el procedimiento de borrar los siguientes datos 1,5. */

// Comenzando con un AVL vacío, muestre todo el procedimiento de ingresar los siguientes
// datos 1,2,3,4,5,6,7,8.

#include <iostream>

using namespace std;

// Definición de la estructura de un nodo AVL
struct AVLNode
{
    int data;
    int height;
    AVLNode *left;
    AVLNode *right;

    AVLNode(int value) : data(value), height(1), left(nullptr), right(nullptr) {}
};

// Función para obtener la altura de un nodo
int getHeight(AVLNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

// Función para obtener el factor de equilibrio de un nodo
int getBalanceFactor(AVLNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Función para realizar una rotación a la derecha
AVLNode *rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    // Realizar la rotación
    x->right = y;
    y->left = T2;

    // Actualizar alturas
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Función para realizar una rotación a la izquierda
AVLNode *leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    // Realizar la rotación
    y->left = x;
    x->right = T2;

    // Actualizar alturas
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Función para insertar un nodo en el árbol AVL
AVLNode *insertNode(AVLNode *root, int value)
{
    // Paso 1: Realizar la inserción estándar de un BST
    if (root == nullptr)
    {
        return new AVLNode(value);
    }

    if (value < root->data)
    {
        root->left = insertNode(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insertNode(root->right, value);
    }
    else
    {
        // Los nodos duplicados no están permitidos en un AVL
        return root;
    }

    // Paso 2: Actualizar la altura del nodo actual
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Paso 3: Obtener el factor de equilibrio del nodo actual
    int balance = getBalanceFactor(root);

    // Paso 4: Realizar las rotaciones si es necesario
    // Rotación a la izquierda-izquierda (LL)
    if (balance > 1 && value < root->left->data)
    {
        return rightRotate(root);
    }
    // Rotación a la derecha-derecha (RR)
    if (balance < -1 && value > root->right->data)
    {
        return leftRotate(root);
    }
    // Rotación a la izquierda-derecha (LR)
    if (balance > 1 && value > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Rotación a la derecha-izquierda (RL)
    if (balance < -1 && value < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Devolver el nodo no modificado
    return root;
}

// Función para imprimir el árbol AVL en orden
void inOrderTraversal(AVLNode *root)
{
    if (root != nullptr)
    {
        inOrderTraversal(root->left);
        cout << root->data << " ";
        inOrderTraversal(root->right);
    }
}

// Función para eliminar un nodo en el árbol AVL
AVLNode *deleteNode(AVLNode *root, int value)
{
    // Paso 1: Realizar la eliminación estándar de un BST
    if (root == nullptr)
    {
        return nullptr; // Return null in this case
    }

    if (value < root->data)
    {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = deleteNode(root->right, value);
    }
    else
    {
        // Paso 2: Eliminar el nodo actual
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            return nullptr; // Return null after deleting the node
        }
        else if (root->left == nullptr)
        {
            AVLNode *temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr)
        {
            AVLNode *temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            AVLNode *temp = root->right;
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // Si el árbol AVL tenía un solo nodo, entonces regresar
    if (root == nullptr)
    {
        return nullptr;
    }

    // Paso 3: Actualizar la altura del nodo actual
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Paso 4: Obtener el factor de equilibrio del nodo actual
    int balance = getBalanceFactor(root);

    // Paso 5: Realizar las rotaciones si es necesario
    // Rotación a la izquierda-izquierda (LL)
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
    {
        return rightRotate(root);
    }
    // Rotación a la derecha-derecha (RR)
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
    {
        return leftRotate(root);
    }
    // Rotación a la izquierda-derecha (LR)
    if (balance > 1 && getBalanceFactor(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Rotación a la derecha-izquierda (RL)
    if (balance < -1 && getBalanceFactor(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Devolver el nodo no modificado
    return root;
}

int main()
{
    AVLNode *root = nullptr;

    // Insertar los datos 1,2,3,4,5,6,11,13,12,10,9,8,7 en el AVL
    int values[] = {1, 2, 3, 4, 5, 6, 11, 13, 12, 10, 9, 8, 7};
    int numValues = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < numValues; ++i)
    {
        root = insertNode(root, values[i]);
    }

    // Imprimir el árbol AVL en orden
    cout << "Árbol AVL después de la inserción: ";
    inOrderTraversal(root);

    // a. Luego, muestre todo el procedimiento de borrar los siguientes datos 10,9,7,8.
    cout << "\n\nBorrando el 10: ";
    root = deleteNode(root, 10);
    inOrderTraversal(root);

    cout << "\n\nBorrando el 9: ";
    root = deleteNode(root, 9);
    inOrderTraversal(root);

    cout << "\n\nBorrando el 7: ";
    root = deleteNode(root, 7);
    inOrderTraversal(root);

    cout << "\n\nBorrando el 8: ";
    root = deleteNode(root, 8);
    inOrderTraversal(root);

    // b. Luego, muestre todo el procedimiento de borrar el 13.
    cout << "\n\nBorrando el 13: ";
    root = deleteNode(root, 13);
    inOrderTraversal(root);

    // c. Luego, muestre todo el procedimiento de borrar los siguientes datos 1,5.
    cout << "\n\nBorrando el 1: ";
    root = deleteNode(root, 1);
    inOrderTraversal(root);

    cout << "\n\nBorrando el 5: ";
    root = deleteNode(root, 5);
    inOrderTraversal(root);

    return 0;
}
