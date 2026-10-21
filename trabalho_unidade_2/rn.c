#include <stdio.h>
#include <stdlib.h>
#include "rn.h"

// Função auxiliar para criar um novo nó (sempre inserido como VERMELHO por regra)
NoRN *criarNoRN(int valor) {
    NoRN *novoNo = (NoRN *)malloc(sizeof(NoRN));
    novoNo->valor = valor;
    novoNo->cor = VERMELHO; // Propriedade: Novos nós são sempre vermelhos
    novoNo->esquerdo = NULL;
    novoNo->direito = NULL;
    novoNo->pai = NULL;
    return novoNo;
}

// Rotação simples à esquerda (Rubro-Negra)
void rotacaoEsquerdaRN(NoRN **raiz, NoRN *x) {
    NoRN *y = x->direito;
    x->direito = y->esquerdo;

    if (y->esquerdo != NULL)
        y->esquerdo->pai = x;

    y->pai = x->pai;

    if (x->pai == NULL)
        *raiz = y; // x era a raiz
    else if (x == x->pai->esquerdo)
        x->pai->esquerdo = y;
    else
        x->pai->direito = y;

    y->esquerdo = x;
    x->pai = y;
}

// Rotação simples à direita (Rubro-Negra)
void rotacaoDireitaRN(NoRN **raiz, NoRN *y) {
    NoRN *x = y->esquerdo;
    y->esquerdo = x->direito;

    if (x->direito != NULL)
        x->direito->pai = y;

    x->pai = y->pai;

    if (y->pai == NULL)
        *raiz = x; // y era a raiz
    else if (y == y->pai->direito)
        y->pai->direito = x;
    else
        y->pai->esquerdo = x;

    x->direito = y;
    y->pai = x;
}

// Função auxiliar para restaurar as propriedades da árvore após a inserção
void consertarInsercaoRN(NoRN **raiz, NoRN *z) {
    while (z->pai != NULL && z->pai->cor == VERMELHO) {
        if (z->pai == z->pai->pai->esquerdo) {
            NoRN *y = z->pai->pai->direito; // O tio (filho direito do avô)

            // Caso 1: O tio é vermelho
            if (y != NULL && y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai; // Move a análise para o avô
            } else {
                // Caso 2: O tio é preto e o nó é filho direito (necessita de rotação dupla)
                if (z == z->pai->direito) {
                    z = z->pai;
                    rotacaoEsquerdaRN(raiz, z);
                }
                // Caso 3: O tio é preto e o nó é filho esquerdo
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoDireitaRN(raiz, z->pai->pai);
            }
        } else {
            // Cenário simétrico: o pai de z é o filho direito do avô
            NoRN *y = z->pai->pai->esquerdo; // O tio (filho esquerdo do avô)

            // Caso 1: O tio é vermelho
            if (y != NULL && y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                // Caso 2: O tio é preto e o nó é filho esquerdo
                if (z == z->pai->esquerdo) {
                    z = z->pai;
                    rotacaoDireitaRN(raiz, z);
                }
                // Caso 3: O tio é preto e o nó é filho direito
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoEsquerdaRN(raiz, z->pai->pai);
            }
        }
    }
    // A raiz deve ser sempre preta
    (*raiz)->cor = PRETO;
}

// Função principal de inserção
void inserirRN(NoRN **raiz, int valor) {
    NoRN *z = criarNoRN(valor);
    NoRN *y = NULL;
    NoRN *x = *raiz;

    // 1. Inserção normal de Árvore de Busca Binária
    while (x != NULL) {
        y = x;
        if (z->valor < x->valor)
            x = x->esquerdo;
        else if (z->valor > x->valor)
            x = x->direito;
        else {
            // Valor repetido encontrado
            printf("Aviso: O valor %d ja existe na arvore e nao sera inserido.\n", valor);
            free(z);
            return;
        }
    }

    z->pai = y;

    if (y == NULL)
        *raiz = z; // A árvore estava vazia
    else if (z->valor < y->valor)
        y->esquerdo = z;
    else
        y->direito = z;

    // 2. Corrige as violações das propriedades Rubro-Negras
    consertarInsercaoRN(raiz, z);
}

// Função para buscar um elemento na árvore Rubro-Negra
NoRN *buscarRN(NoRN *raiz, int valor) {
    if (raiz == NULL) {
        printf("Busca: O valor %d nao existe na arvore.\n", valor);
        return NULL;
    }
    
    if (valor == raiz->valor) {
        printf("Busca: O valor %d foi encontrado na arvore.\n", valor);
        return raiz;
    }
    
    if (valor < raiz->valor)
        return buscarRN(raiz->esquerdo, valor);
        
    return buscarRN(raiz->direito, valor);
}

// Função para percorrer a árvore em ordem (imprime em ordem crescente)
void emOrdemRN(NoRN *raiz) {
    if (raiz != NULL) {
        emOrdemRN(raiz->esquerdo);
        printf("%d ", raiz->valor);
        emOrdemRN(raiz->direito);
    }
}

// Função para imprimir e visualizar a estrutura da árvore com identificação de cores
void visualizarArvoreRN(NoRN *raiz, int espaco) {
    if (raiz == NULL)
        return;

    int espacamento_nivel = 5;
    espaco += espacamento_nivel;

    // Processa o filho direito
    visualizarArvoreRN(raiz->direito, espaco);

    // Imprime o nó atual
    printf("\n");
    for (int i = espacamento_nivel; i < espaco; i++)
        printf(" ");
    
    // Identifica a cor: (V) para Vermelho, (P) para Preto
    char corIdentificador = (raiz->cor == VERMELHO) ? 'V' : 'P';
    printf("%d(%c)\n", raiz->valor, corIdentificador);

    // Processa o filho esquerdo
    visualizarArvoreRN(raiz->esquerdo, espaco);
}

// Função auxiliar para encontrar o menor nó de uma sub-árvore
NoRN *noMinimoRN(NoRN *no) {
    while (no->esquerdo != NULL)
        no = no->esquerdo;
    return no;
}

// Função auxiliar para substituir a sub-árvore 'u' pela sub-árvore 'v'
void transplantarRN(NoRN **raiz, NoRN *u, NoRN *v) {
    if (u->pai == NULL)
        *raiz = v;
    else if (u == u->pai->esquerdo)
        u->pai->esquerdo = v;
    else
        u->pai->direito = v;
    
    if (v != NULL)
        v->pai = u->pai;
}

// Função para corrigir as propriedades da árvore após remoção
void consertarRemocaoRN(NoRN **raiz, NoRN *x, NoRN *x_pai) {
    while (x != *raiz && (x == NULL || x->cor == PRETO)) {
        if (x == x_pai->esquerdo) {
            NoRN *w = x_pai->direito; // Irmão
            if (w != NULL && w->cor == VERMELHO) {
                w->cor = PRETO;
                x_pai->cor = VERMELHO;
                rotacaoEsquerdaRN(raiz, x_pai);
                w = x_pai->direito;
            }
            if (w == NULL || ((w->esquerdo == NULL || w->esquerdo->cor == PRETO) && 
                              (w->direito == NULL || w->direito->cor == PRETO))) {
                if (w != NULL) w->cor = VERMELHO;
                x = x_pai;
                x_pai = x->pai;
            } else {
                if (w->direito == NULL || w->direito->cor == PRETO) {
                    if (w->esquerdo != NULL) w->esquerdo->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacaoDireitaRN(raiz, w);
                    w = x_pai->direito;
                }
                w->cor = x_pai->cor;
                x_pai->cor = PRETO;
                if (w->direito != NULL) w->direito->cor = PRETO;
                rotacaoEsquerdaRN(raiz, x_pai);
                x = *raiz;
            }
        } else {
            // Cenário simétrico (x é filho direito)
            NoRN *w = x_pai->esquerdo;
            if (w != NULL && w->cor == VERMELHO) {
                w->cor = PRETO;
                x_pai->cor = VERMELHO;
                rotacaoDireitaRN(raiz, x_pai);
                w = x_pai->esquerdo;
            }
            if (w == NULL || ((w->direito == NULL || w->direito->cor == PRETO) && 
                              (w->esquerdo == NULL || w->esquerdo->cor == PRETO))) {
                if (w != NULL) w->cor = VERMELHO;
                x = x_pai;
                x_pai = x->pai;
            } else {
                if (w->esquerdo == NULL || w->esquerdo->cor == PRETO) {
                    if (w->direito != NULL) w->direito->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacaoEsquerdaRN(raiz, w);
                    w = x_pai->esquerdo;
                }
                w->cor = x_pai->cor;
                x_pai->cor = PRETO;
                if (w->esquerdo != NULL) w->esquerdo->cor = PRETO;
                rotacaoDireitaRN(raiz, x_pai);
                x = *raiz;
            }
        }
    }
    if (x != NULL)
        x->cor = PRETO;
}

// Função principal para remover um nó da árvore Rubro-Negra
void removerRN(NoRN **raiz, int valor) {
    NoRN *z = *raiz;
    
    // Procura o nó a remover
    while (z != NULL && z->valor != valor) {
        if (valor < z->valor) z = z->esquerdo;
        else z = z->direito;
    }

    if (z == NULL) {
        printf("Aviso: O valor %d nao foi encontrado para remocao.\n", valor);
        return;
    }

    NoRN *y = z;
    NoRN *x = NULL;
    NoRN *x_pai = NULL;
    Cor cor_original_y = y->cor;

    if (z->esquerdo == NULL) {
        x = z->direito;
        x_pai = z->pai;
        transplantarRN(raiz, z, z->direito);
    } else if (z->direito == NULL) {
        x = z->esquerdo;
        x_pai = z->pai;
        transplantarRN(raiz, z, z->esquerdo);
    } else {
        y = noMinimoRN(z->direito);
        cor_original_y = y->cor;
        x = y->direito;
        x_pai = y; // x_pai inicialmente aponta para y

        if (y->pai == z) {
            if (x != NULL) x->pai = y;
            x_pai = y;
        } else {
            x_pai = y->pai;
            transplantarRN(raiz, y, y->direito);
            y->direito = z->direito;
            y->direito->pai = y;
        }
        transplantarRN(raiz, z, y);
        y->esquerdo = z->esquerdo;
        y->esquerdo->pai = y;
        y->cor = z->cor;
    }

    free(z);

    if (cor_original_y == PRETO) {
        consertarRemocaoRN(raiz, x, x_pai);
    }
}