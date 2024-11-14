#ifndef AVL_TREE_H
#define AVL_TREE_H

// Estrutura do nó da árvore AVL
typedef struct Node {
    int key;
    int height;
    struct Node* left;
    struct Node* right;
} Node;

// Estrutura da árvore AVL
typedef struct AVLTree {
    Node* root;
} AVLTree;

// Funções para manipulação da árvore AVL

// Inicializa a árvore AVL
AVLTree* createAVLTree();

// Cria um novo nó com a chave fornecida
Node* createNode(int key);

// Função para obter a altura de um nó
int height(Node* node);

// Função para obter o fator de balanceamento de um nó
int getBalance(Node* node);

// Funções de rotação para balanceamento
Node* rotateRight(Node* y);
Node* rotateLeft(Node* x);

// Insere uma chave na árvore AVL e retorna a nova raiz
Node* insertNode(Node* node, int key);

// Remove uma chave da árvore AVL e retorna a nova raiz
Node* deleteNode(Node* root, int key);

// Função para buscar uma chave na árvore AVL
Node* searchNode(Node* root, int key);

Node* minValueNode(Node* node);

// Funções de exibição: Pré-ordem, In-ordem, e Pós-ordem
void preOrder(Node* root);
void inOrder(Node* root);
void postOrder(Node* root);

// Libera a memória alocada pela árvore AVL
void freeTree(Node* root);

#endif // AVL_TREE_H

