#ifndef RN_H
#define RN_H

// Enumeração para as cores dos nós
typedef enum { VERMELHO, PRETO } Cor;

// Estrutura do nó da árvore Rubro-Negra
typedef struct NoRN {
    int valor;
    Cor cor;
    struct NoRN *esquerdo;
    struct NoRN *direito;
    struct NoRN *pai;
} NoRN;

// Protótipos das operações principais
NoRN *criarNoRN(int valor);
void rotacaoEsquerdaRN(NoRN **raiz, NoRN *x);
void rotacaoDireitaRN(NoRN **raiz, NoRN *y);
void inserirRN(NoRN **raiz, int valor);
void removerRN(NoRN **raiz, int valor);
NoRN *buscarRN(NoRN *raiz, int valor);
void emOrdemRN(NoRN *raiz);
void visualizarArvoreRN(NoRN *raiz, int espaco);
extern int rotacoesRN;

#endif // RN_H