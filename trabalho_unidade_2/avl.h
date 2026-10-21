#ifndef AVL_H
#define AVL_H

// Estrutura do nó da árvore AVL
typedef struct No {
    int valor;
    struct No *esquerdo;
    struct No *direito;
    int altura;
} No;

// Protótipos das funções auxiliares e de balanceamento
int altura(No *N);
int maior(int a, int b);
int fatorDeBalanceamento(No *N);
No *rotacaoDireita(No *y);
No *rotacaoEsquerda(No *x);

No *inserir(No *no, int valor);
// No *remover(No *no, int valor);
// No *buscar(No *no, int valor);
// void emOrdem(No *no);
// void visualizarArvore(No *no, int espaco);

#endif