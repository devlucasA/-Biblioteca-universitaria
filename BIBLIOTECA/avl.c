#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

// Função para inicializar a árvore AVL
AVLTree* createAVLTree() {
    AVLTree* tree = (AVLTree*)malloc(sizeof(AVLTree));
    tree->root = NULL;
    return tree;
}

// Função para criar um novo nó
Node* createNode(int key, void * data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->data = data; //Armazena o livro
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

// Função para obter a altura de um nó
int height(Node* node) {
    return node ? node->height : 0;
}

// Função para obter o fator de balanceamento de um nó
int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Função de rotação à direita
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

// Função de rotação à esquerda
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

// Função para inserir um nó na árvore AVL
Node* insertNode(Node* node, int key, void* data) {
    if (node == NULL) 
        return createNode(key, data);

    if (key < node->key)
        node->left = insertNode(node->left, key, data);
    else if (key > node->key)
        node->right = insertNode(node->right, key, data);
    else
        return node;

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}


// Função para buscar um nó na árvore AVL
Node* searchNode(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return searchNode(root->left, key);
    return searchNode(root->right, key);
}

// Função para exibir a árvore em pré-ordem
void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Função para exibir a árvore em in-ordem
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

// Função para exibir a árvore em pós-ordem
void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}

// Função para liberar a memória alocada pela árvore AVL
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}


Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    // Realiza a busca do nó a ser removido
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Nó encontrado
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // Se a árvore tinha apenas um nó, retorne
    if (root == NULL)
        return root;

    // Atualiza a altura do nó atual
    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    // Verifica e corrige o balanceamento
    int balance = getBalance(root);

    // Caso de Rotação à Direita
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    // Caso de Rotação Esquerda-Direita
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Caso de Rotação à Esquerda
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    // Caso de Rotação Direita-Esquerda
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}


