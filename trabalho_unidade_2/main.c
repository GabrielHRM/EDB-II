#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "rn.h"

void menuOperacoes() {
    printf("\n--- OPERACOES ---\n");
    printf("1. Inserir elemento\n");
    printf("2. Remover elemento\n");
    printf("3. Buscar elemento\n");
    printf("4. Percurso em ordem (Crescente)\n");
    printf("5. Visualizar estrutura da arvore\n");
    printf("0. Voltar ao menu principal\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcaoPrincipal, opcaoOperacao, valor;
    
    // Raízes das árvores
    No *raizAVL = NULL;
    NoRN *raizRN = NULL;

    do {
        printf("\n=== AMAZON ENGINEERING CHALLENGE ===\n");
        printf("1. Testar Arvore AVL\n");
        printf("2. Testar Arvore Rubro-Negra\n");
        printf("0. Sair\n");
        printf("Escolha o tipo de arvore: ");
        scanf("%d", &opcaoPrincipal);

        if (opcaoPrincipal == 1) {
            // Sub-menu para Árvore AVL
            do {
                printf("\n[ ARVORE AVL ]");
                menuOperacoes();
                scanf("%d", &opcaoOperacao);

                switch (opcaoOperacao) {
                    case 1:
                        printf("Digite o valor a inserir: ");
                        scanf("%d", &valor);
                        raizAVL = inserir(raizAVL, valor);
                        printf("\n-> Total de rotacoes AVL ate agora: %d\n", rotacoesAVL);
                        break;
                    case 2:
                        printf("Digite o valor a remover: ");
                        scanf("%d", &valor);
                        raizAVL = remover(raizAVL, valor);
                        printf("\n-> Total de rotacoes AVL ate agora: %d\n", rotacoesAVL);
                        break;
                    case 3:
                        printf("Digite o valor a buscar: ");
                        scanf("%d", &valor);
                        buscar(raizAVL, valor);
                        break;
                    case 4:
                        printf("Elementos em ordem: ");
                        emOrdem(raizAVL);
                        printf("\n");
                        break;
                    case 5:
                        printf("Estrutura da Arvore AVL:\n");
                        visualizarArvore(raizAVL, 0);
                        break;
                    default:
                        printf("Opcao invalida!\n");
                }
            } while (opcaoOperacao != 0);

        } else if (opcaoPrincipal == 2) {
            // Sub-menu para Árvore Rubro-Negra
            do {
                printf("\n[ ARVORE RUBRO-NEGRA ]");
                menuOperacoes();
                scanf("%d", &opcaoOperacao);

                switch (opcaoOperacao) {
                    case 1:
                        printf("Digite o valor a inserir: ");
                        scanf("%d", &valor);
                        inserirRN(&raizRN, valor);
                        printf("\n-> Total de rotacoes RN ate agora: %d\n", rotacoesRN);
                        break;
                    case 2:
                        printf("Digite o valor a remover: ");
                        scanf("%d", &valor);
                        removerRN(&raizRN, valor);
                        printf("\n-> Total de rotacoes RN ate agora: %d\n", rotacoesRN);
                        break;
                    case 3:
                        printf("Digite o valor a buscar: ");
                        scanf("%d", &valor);
                        buscarRN(raizRN, valor);
                        break;
                    case 4:
                        printf("Elementos em ordem: ");
                        emOrdemRN(raizRN);
                        printf("\n");
                        break;
                    case 5:
                        printf("Estrutura da Arvore Rubro-Negra:\n");
                        visualizarArvoreRN(raizRN, 0);
                        break;
                    default:
                        printf("Opcao invalida!\n");
                }
            } while (opcaoOperacao != 0);
            
        } else if (opcaoPrincipal != 0) {
            printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcaoPrincipal != 0);

    return 0;
}