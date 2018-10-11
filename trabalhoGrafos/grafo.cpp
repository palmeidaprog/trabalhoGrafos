#include "grafo.h"

Grafos::Grafo::Grafo(const FILE *arquivo) : arquivo(arquivo), tamanho(0) { }

Grafos::Grafo::~Grafo() {
    fclose(arquivo);
}

std::string Grafos::Grafo::getLista() {
    stringstream s;

    for(int i = 0; i < tamanho; i++) {
        s << "[" << i << "]";
        No *lido = listaAdj[i];
        while(lido != nullptr) {

        }
    }

}


