# Amazon Engineering Challenge: Árvores Balanceadas (AVL e Rubro-Negra)

## 👤 Identificação do Autor

- **Autor:** Gabriel Henrique Rocha Melo
- **Matrícula:** 20250059916
- **Componente Curricular:** IMD0039 - Estruturas de Dados Básicas II  
- **Instituição:** Instituto Metrópole Digital (IMD / UFRN)  

---

## 📌 Visão Geral do Projeto

Este repositório contém a solução do **Amazon Engineering Challenge**, desenvolvido no âmbito da disciplina de Estruturas de Dados Básicas II. 

Durante eventos de altíssimo tráfego de dados, como a **Black Friday**, o sistema de logística da Amazon demanda operações de inserção, busca e remoção de identificadores de encomendas com alta eficiência determinística $O(\log n)$. Como a ordem imprevisível ou sequencial de chegada dos dados pode degradar uma Árvore de Busca Binária (BST) convencional para tempo linear $O(n)$, este projeto implementa e compara duas estruturas auto-balanceadas desenvolvidas do zero em C:

1. **Árvore AVL** (balanceamento estrito por fator de altura);
2. **Árvore Rubro-Negra / Red-Black** (balanceamento por coloração e rotações).

---

## 📁 Estrutura do Repositório

O repositório está organizado para fornecer acesso direto ao código-fonte completo, documentação e à versão compilada funcional do programa:

```text
    EDB-II/
    ├── .gitattributes         # Configurações do repositório Git
    └── trabalho_unidade_2/    # Pasta do projeto
        ├── prints_testes/     # Pasta com os prints dos testes
        ├── amazon_trees.exe   # Executável do programa
        ├── avl.c              # Implementação e lógica de balanceamento da Árvore AVL
        ├── avl.h              # Definições de estruturas e protótipos da Árvore AVL
        ├── main.c             # Ponto de entrada e menu interativo do sistema
        ├── rn.c               # Implementação, rebalanceamento e coloração da Árvore Rubro-Negra
        └── rn.h               # Definições de estruturas e protótipos da Árvore Rubro-Negra
    ├── README.md          # Documentação técnica do projeto
```

---

## ⚙️ Dependências e Requisitos

### Dependências Necessárias
- **Compilador GCC:** gcc (Rev8, Built by MSYS2 project) 15.2.0.
- **Bibliotecas Padrão:** Apenas a biblioteca padrão C (`<stdio.h>`, `<stdlib.h>`).
- **Bibliotecas Externas:** **Nenhuma**. Toda a lógica de balanceamento, rotação e tratamento de cores foi desenvolvida manualmente sem bibliotecas de terceiros.

---

## 🚀 Instruções de Compilação e Execução

### 1. Compilando o Código-Fonte
Para gerar a versão compilada a partir do código-fonte, utilize o terminal na raiz do projeto:

```bash
# Compilação via gcc (powershell)
gcc main.c avl.c rn.c -o amazon_trees
```

### 2. Executando o Programa Compilado

```bash
# Execução no powershell
.\amazon_trees.exe
```

---

## 🛠️ Descrição das Funcionalidades Implementadas e Exemplos de Uso

### Funcionalidades do Sistema

1. **Escolha Dinâmica da Estrutura:** O usuário seleciona no início da execução se deseja interagir com a Árvore AVL ou com a Árvore Rubro-Negra.
2. **Inserção com Verificação de Duplicatas:** Insere novos identificadores numéricos e impede a inclusão de elementos repetidos, exibindo alertas.
3. **Remoção de Nós em Qualquer Configuração:** Trata a exclusão de nós folha, nós com um filho e nós com dois filhos, garantindo o rebalanceamento imediato.
4. **Busca Eficiente:** Verifica a existência de um elemento na árvore e informa o status ao usuário.
5. **Percurso Em-Ordem:** Exibe todos os identificadores em ordem estritamente crescente.
6. **Visualização Gráfica/Hierárquica da Estrutura:** Imprime no terminal o formato visual da árvore:
   - Na **Árvore Rubro-Negra**, cada nó indica explicitamente sua cor: `[PRETO]` ou `[VERMELHO]`.
7. **Contador Automático de Rotações:** Mantém um registro exato do número de rotações efetuadas para fins de análise comparativa.

---

---

## 💡 Comentários sobre o Funcionamento e Decisões de Implementação

### 1. Árvore AVL
- **Mecanismo:** A AVL mantém um controle estrito de altura. Para cada nó, calcula-se o **Fator de Balanceamento** $FB = \text{altura}(\text{esquerda}) - \text{altura}(\text{direita})$.
- **Condição de Violação:** Se $|FB| > 1$, a árvore aplica rotações simples (LL ou RR) ou rotações duplas (LR ou RL).
- **Uso Indicado:** Excelente para cenários em que a quantidade de buscas é predominantemente maior do que as inserções/remoções, devido à menor altura média.

### 2. Árvore Rubro-Negra (Red-Black)
- **Mecanismo:** Cada nó possui um atributo adicional de **cor** (`VERMELHO` ou `PRETO`). O balanceamento é garantido pelas 5 propriedades fundamentais:
  1. Todo nó é vermelho ou preto.
  2. A raiz é sempre preta.
  3. Todas as folhas nulas (`NIL`) são pretas.
  4. Se um nó é vermelho, seus dois filhos devem ser pretos (não há nós vermelhos consecutivos).
  5. Todos os caminhos de um nó até suas folhas descendentes contêm a mesma quantidade de nós pretos (*black-height*).
- **Ajustes:** Prioriza o **recolorimento de nós** para resolver conflitos de cor. Quando o recolorimento não basta, realiza rotações.
- **Uso Indicado:** Ideal para sistemas de altíssima frequência de escrita (inserções/remoções frequentes, como o fluxo da Black Friday), pois requer menos rotações no pior caso se comparada à AVL.

### 3. Tratamento de Casos Limite
- **Duplicatas:** Tentativas de reinserir uma chave existente são interrompidas no momento do percurso, retornando uma mensagem informativa e cancelando qualquer alteração.
- **Remoção de Inexistentes:** O algoritmo realiza a busca prévia da chave; caso não a encontre, encerra a operação sem realizar percursos de rebalanceamento desnecessários.
- **Casos Especiais de Remoção:** Ao remover um nó interno com dois filhos, substitui-se a chave pelo **sucessor em-ordem** (menor nó da subárvore direita) e rebalanceia-se a partir do ponto de remoção efetivo.

---

## 🏆 Recomendação Técnica para a Amazon

Para a infraestrutura logística do sistema de encomendas da Amazon no cenário de **Black Friday**, a recomendação técnica é a utilização da **Árvore Rubro-Negra**.

### Justificativa Técnica:
1. **Menor Custo em Operações de Escrita:** Em um ambiente de logística pesada onde pacotes são constantemente cadastrados e despachados (alta taxa de inserção/remoção), a Rubro-Negra reduz a necessidade de reestruturações pesadas via rotações, resolvendo a maioria das violações apenas alterando as cores dos nós.
2. **Garantia de Desempenho Logarítmico:** Embora a altura da Rubro-Negra possa ser ligeiramente maior do que a da AVL (no máximo $2\log(n+1)$), o tempo de busca permanece estritamente em $O(\log n)$, o que atende plenamente aos requisitos de baixa latência do sistema.
