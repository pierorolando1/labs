#include<iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

// Función para crear un nuevo nodo
Node* CreateNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Memory error\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Función para insertar en un ABB
Node* InsertNode(Node* root, int data) {
    // Si el árbol está vacío, asignar nuevo nodo dirección
    if (root == NULL) {
        root = CreateNode(data);
        return root;
    }

    // Else, hacer un recorrido en profundidad
    if (data < root->data) {
        root->left = InsertNode(root->left, data);
    }
    else {
        root->right = InsertNode(root->right, data);
    }

    return root;
}

// Función para hacer recorrido inorden
void inorder(Node* temp) {
    if (temp == NULL)
        return;

    inorder(temp->left);
    cout << temp->data << ' ';
    inorder(temp->right);
}

// Función para hacer recorrido preorden
void preorder(Node* temp) {
    if (temp == NULL)
        return;

    cout << temp->data << ' ';
    preorder(temp->left);
    preorder(temp->right);
}

// Función para hacer recorrido postorden
void postorder(Node* temp) {
    if (temp == NULL)
        return;

    postorder(temp->left);
    postorder(temp->right);
    cout << temp->data << ' ';
}

// Función para buscar un nodo dado en un ABB
Node* search(Node* root, int key) {
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->data == key)
       return root;
    
    // Key is greater than root's key
    if (root->data < key)
       return search(root->right, key);
  
    // Key is smaller than root's key
    return search(root->left, key);
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// 1. Eliminación de un nodo dado (su valor)
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// 2. Recorrido en amplitud (o por niveles).
void levelOrder(Node* root) {
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        cout << node->data << " ";
        q.pop();
        if (node->left != NULL) q.push(node->left);
        if (node->right != NULL) q.push(node->right);
    }
}

// 3. Visualizar ABB de manera jerárquica vertical, imprime cada nivel del arbol en una linea nueva
void printTree(Node* root, int space) {
    if (root == NULL) return;
    space += 5;
    printTree(root->right, space);
    cout << endl;
    for (int i = 5; i < space; i++) {
        cout << " ";
    }
    cout << root->data << "\n";
    printTree(root->left, space);
}

// 4. Contar las hojas de un ABB.
int countLeaves(Node* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

// 5. Dado un ABB, reportar cuál es su altura.
int height(Node* root) {
    if (root == NULL) return 0;
    return 1 + max(height(root->left), height(root->right));
}

// 6. Contar el número de nodos y el número de niveles de un ABB.
int countNodes(Node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// 7. Eliminar todos los nodos del árbol
void deleteTree(Node* &root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = NULL;
}


/*
1 es el jefe, tiene 2 subjefes, el 2 y el 3, 2 tiene a cargo a 4 y 5, 3 tiene a cargo a 6 y 7
*/
int main() {
    Node* root = NULL;
    root = InsertNode(root, 1);
    InsertNode(root, -1);
    InsertNode(root, 3);
    InsertNode(root, 2);
    InsertNode(root, 4);
    InsertNode(root, 5);
    InsertNode(root, 6);
    InsertNode(root, 7);

    cout << "Inorder: ";
    inorder(root);
    cout << endl;

    cout << "Preorder: ";
    preorder(root);
    cout << endl;

    cout << "Postorder: ";
    postorder(root);
    cout << endl;

    Node* result = search(root, 5);
    if (result) {
        cout << "Elemento encontrado: " << result->data << endl;
    }
    else {
        cout << "Elemento no encontrado\n";
    }

    cout << "Eliminando el nodo 5\n";
    root = deleteNode(root, 5);

    levelOrder(root);

    printTree(root, 0);

    return 0;
}