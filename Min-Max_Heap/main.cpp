#include <stdexcept>
#include <vector>

constexpr int TOTAL_MILHARES = 10000;

std::vector<unsigned long long> apostas(TOTAL_MILHARES, 0);

void registrarAposta(int numero) {
    if (numero < 0 || numero >= TOTAL_MILHARES) {
        throw std::out_of_range("milhar inválido");
    }

    ++apostas[numero];
}


int MenorAposta(const std::vector<int>& apostas){
    int menor = apostas[0];

    for (size_t i = 1; i < v.size(); i++){
        if(apostas[i] < menor){
            menor = v[i];
        }
    }
    return mneor;
}

int MaiorAposta(const std::vector<int>& apostas){
    int maior = apostas[0];

    for (size_t i = 1; i < v.size(); i++){
        if(apostas[i] > maior){
            maior = v[i];
        }
    }
    return maior;
}