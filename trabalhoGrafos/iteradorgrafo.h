#ifndef ITERADORGRAFO_H
#define ITERADORGRAFO_H

#include <stdexcept>

namespace grafos {
template <typename T>
class IteradorGrafo {
    No<T> **listaAdj, *atual;
    int tamanho, pos = 0;

public:
    IteradorGrafo(No<T> **listaAdj, int tamanho) : listaAdj(listaAdj),
        tamanho(tamanho) { }
    ~IteradorGrafo() { }

    bool hasNext() {
        return atual != nullptr;
    }

    No<T> *next() {
        if(hasNext()) {
            No<T> *retorno = atual;
            atual = atual->getProx();
            while(atual == nullptr && ++pos < tamanho) {
                atual = listaAdj[pos];
            }
            return retorno;
        } else {
            throw std::out_of_range("Não existe elementos na lista");
        }
    }
};

}

#endif // ITERADORGRAFO_H
