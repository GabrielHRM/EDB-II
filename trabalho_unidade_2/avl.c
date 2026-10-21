#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

// Função para obter a altura de um nó
int altura(No *N) {
    if (N == NULL)
        return 0;
    return N->altura;
}

// Função auxiliar para obter o maior de dois números
int maior(int a, int b) {
    return (a > b) ? a : b;
}

// Calcula o fator de balanceamento (diferença entre sub-árvore esquerda e direita)
int fatorDeBalanceamento(No *N) {
    if (N == NULL)
        return 0;
    return altura(N->esquerdo) - altura(N->direito);
}

// Rotação simples à direita
No *rotacaoDireita(No *y) {
    No *x = y->esquerdo;
    No *T2 = x->direito;

    // Realiza a rotação
    x->direito = y;
    y->esquerdo = T2;

    // Atualiza as alturas
    y->altura = maior(altura(y->esquerdo), altura(y->direito)) + 1;
    x->altura = maior(altura(x->esquerdo), altura(x->direito)) + 1;

    return x; // Retorna a nova raiz
}

// Rotação simples à esquerda
No *rotacaoEsquerda(No *x) {
    No *y = x->direito;
    No *T2 = y->esquerdo;

    // Realiza a rotação
    y->esquerdo = x;
    x->direito = T2;

    // Atualiza as alturas
    x->altura = maior(altura(x->esquerdo), altura(x->direito)) + 1;
    y->altura = maior(altura(y->esquerdo), altura(y->direito)) + 1;

    return y; // Retorna a nova raiz
}

// Função auxiliar para alocar um novo nó na memória
No *novoNo(int valor) {
    No *no = (No *)malloc(sizeof(No));
    no->valor = valor;
    no->esquerdo = NULL;
    no->direito = NULL;
    no->altura = 1; // O novo nó é inicialmente adicionado como folha
    return no;
}

// Função recursiva para inserir um valor e balancear a árvore AVL
No *inserir(No *no, int valor) {
    // 1. Inserção normal de Árvore de Busca Binária
    if (no == NULL)
        return novoNo(valor);

    if (valor < no->valor)
        no->esquerdo = inserir(no->esquerdo, valor);
    else if (valor > no->valor)
        no->direito = inserir(no->direito, valor);
    else {
        // Valores repetidos não são permitidos
        printf("Aviso: O valor %d ja existe na arvore e nao sera inserido.\n", valor);
        return no; 
    }

    // 2. Atualiza a altura do nó ancestral atual
    no->altura = 1 + maior(altura(no->esquerdo), altura(no->direito));

    // 3. Calcula o fator de balanceamento deste nó ancestral
    int balanceamento = fatorDeBalanceamento(no);

    // 4. Analisa os 4 casos de desbalanceamento e aplica as rotações

    // Caso Esquerda-Esquerda
    if (balanceamento > 1 && valor < no->esquerdo->valor)
        return rotacaoDireita(no);

    // Caso Direita-Direita
    if (balanceamento < -1 && valor > no->direito->valor)
        return rotacaoEsquerda(no);

    // Caso Esquerda-Direita
    if (balanceamento > 1 && valor > no->esquerdo->valor) {
        no->esquerdo = rotacaoEsquerda(no->esquerdo);
        return rotacaoDireita(no);
    }

    // Caso Direita-Esquerda
    if (balanceamento < -1 && valor < no->direito->valor) {
        no->direito = rotacaoDireita(no->direito);
        return rotacaoEsquerda(no);
    }

    // Retorna o ponteiro do nó (inalterado se não houve rotação)
    return no;
}