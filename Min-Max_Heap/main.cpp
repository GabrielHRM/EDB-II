#include <stdexcept>
#include <vector>

constexpr int TOTAL_MILHARES = 10000;

struct Milhar {
    int numero; //numero do milhar
    unsigned long long quantidadeApostas;// qtde de apostas naquele milhar
};

class MinMaxHeap {
private:
    std::vector<Milhar> heap; // milhar guardado no heap
    std::vector<int> posicao; // posição do milhar no heap

public:
    MinMaxHeap(){
        heap.resize(TOTAL_MILHARES);
        posicao.resize(TOTAL_MILHARES);

        for (int i = 0; i < TOTAL_MILHARES; i++){
            heap[i].numero = i;
            heap[i].quantidadeApostas = 0;
            posicao[i] = i;
        }
    }
};

std::vector<unsigned long long> apostas(TOTAL_MILHARES, 0);

//apostas = quantidade de apostas e numero = posição do milhar(0 até 9999)
void registrarAposta(int numero) {
    if (numero < 0 || numero >= TOTAL_MILHARES) {
        throw std::out_of_range("milhar inválido");
    }

    ++apostas[numero];
}


int MenorAposta(const std::vector<unsigned long long>& apostas){
    int menor = 0;

    for (int i = 1; i < TOTAL_MILHARES; i++){
        if (apostas[i] < apostas[menor]){
            menor = i;
        }
    }

    return menor;
}

int MaiorAposta(const std::vector<unsigned long long>& apostas){
    int maior = 0;

    for (int i = 1; i < TOTAL_MILHARES; i++){
        if (apostas[i] > apostas[maior]){
            maior = i;
        }
    }

    return maior;
}