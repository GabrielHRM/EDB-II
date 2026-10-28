#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int rotacoesAVL = 0;

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
    rotacoesAVL++;
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
    rotacoesAVL++;
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
        printf("-> Valor %d inserido.", valor);
    else if (valor > no->valor)
        no->direito = inserir(no->direito, valor);
        printf("-> Valor %d inserido.", valor);
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

// Função auxiliar para encontrar o nó com o menor valor (necessária para remoção de nó com dois filhos)
No *noMinimo(No *no) {
    No *atual = no;
    while (atual->esquerdo != NULL)
        atual = atual->esquerdo;
    return atual;
}

// Função recursiva para remover um valor e manter a árvore AVL balanceada
No *remover(No *raiz, int valor) {
    // 1. Remoção padrão de Árvore de Busca Binária
    if (raiz == NULL) {
        printf("Aviso: O valor %d nao foi encontrado para remocao.\n", valor);
        return raiz;
    }

    if (valor < raiz->valor)
        raiz->esquerdo = remover(raiz->esquerdo, valor);
        printf("-> Remocao do valor %d concluida.", valor);
    else if (valor > raiz->valor)
        raiz->direito = remover(raiz->direito, valor);
        printf("-> Remocao do valor %d concluida.", valor);
    else {
        // Nó encontrado
        // Caso 1 e 2: Nó com um filho ou nenhum filho
        if ((raiz->esquerdo == NULL) || (raiz->direito == NULL)) {
            No *temp = raiz->esquerdo ? raiz->esquerdo : raiz->direito;

            // Sem filhos
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else // Um filho
                *raiz = *temp; // Copia o conteúdo do filho não vazio
            
            free(temp);
        } else {
            // Caso 3: Nó com dois filhos
            // Obtém o sucessor em ordem (o menor valor da sub-árvore direita)
            No *temp = noMinimo(raiz->direito);
            
            // Copia o valor do sucessor para este nó
            raiz->valor = temp->valor;
            
            // Remove o sucessor
            raiz->direito = remover(raiz->direito, temp->valor);
        }
    }

    // Se a árvore tinha apenas um nó, retorna
    if (raiz == NULL)
        return raiz;

    // 2. Atualiza a altura do nó atual
    raiz->altura = 1 + maior(altura(raiz->esquerdo), altura(raiz->direito));

    // 3. Calcula o fator de balanceamento deste nó
    int balanceamento = fatorDeBalanceamento(raiz);

    // 4. Analisa os casos de desbalanceamento e aplica as rotações

    // Caso Esquerda-Esquerda
    if (balanceamento > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0)
        return rotacaoDireita(raiz);

    // Caso Esquerda-Direita
    if (balanceamento > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0) {
        raiz->esquerdo = rotacaoEsquerda(raiz->esquerdo);
        return rotacaoDireita(raiz);
    }

    // Caso Direita-Direita
    if (balanceamento < -1 && fatorDeBalanceamento(raiz->direito) <= 0)
        return rotacaoEsquerda(raiz);

    // Caso Direita-Esquerda
    if (balanceamento < -1 && fatorDeBalanceamento(raiz->direito) > 0) {
        raiz->direito = rotacaoDireita(raiz->direito);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// Função para buscar um elemento na árvore
No *buscar(No *raiz, int valor) {
    if (raiz == NULL) {
        printf("Busca: O valor %d nao existe na arvore.\n", valor);
        return NULL;
    }
    
    if (valor == raiz->valor) {
        printf("Busca: O valor %d foi encontrado na arvore.\n", valor);
        return raiz;
    }
    
    if (valor < raiz->valor)
        return buscar(raiz->esquerdo, valor);
        
    return buscar(raiz->direito, valor);
}

// Função para percorrer a árvore em ordem (imprime os elementos em ordem crescente)
void emOrdem(No *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerdo);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direito);
    }
}

// Função para imprimir e visualizar a estrutura da árvore no terminal
// O parâmetro 'espaco' controla o espaçamento para simular a hierarquia
void visualizarArvore(No *raiz, int espaco) {
    // Caso base
    if (raiz == NULL)
        return;

    // Aumenta a distância entre os níveis da árvore
    int espacamento_nivel = 5;
    espaco += espacamento_nivel;

    // Processa primeiro o filho direito (aparece na parte superior do terminal)
    visualizarArvore(raiz->direito, espaco);

    // Imprime o nó atual após os espaços corretos
    printf("\n");
    for (int i = espacamento_nivel; i < espaco; i++)
        printf(" ");
    printf("%d\n", raiz->valor);

    // Processa o filho esquerdo (aparece na parte inferior do terminal)
    visualizarArvore(raiz->esquerdo, espaco);
}