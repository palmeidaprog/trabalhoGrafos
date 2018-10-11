#ifndef GRAFO_H
#define GRAFO_H

#include <cstdio>
#include <string>
#include <sstream>
#include "no.h"
#include "gmlparser.h"

using std::stringstream;
using grafos::No;
using grafos::GMLParser;

namespace grafos {
template<typename T>
class Grafo {
    int tamanho;
    No **listaAdj;

    void criaListaAdj(FILE *arquivo) {
        if(arquivo == nullptr) {
            return;
        }


        fseek(arquivo, 0, SEEK_SET);
        fscanf(arquivo, "%d", &tamanho);
        if(tamanho <= 0) {
            return;
        }

        // inicializa a lista de Adjacencia
        listaAdj = new No*[tamanho];
        for(int i = 0; i < tamanho; i++) {
            listaAdj[i] = nullptr;
        }

        int vertice, i = 0;
        while(fscanf(arquivo, "%d", &vertice) == 1) {
            if(vertice == -1) {
                ++i;
            } else {
                insereVertice(&listaAdj[i], vertice);
            }
        }
        fclose(arquivo);
    }


public:
    Grafo(FILE *arquivo) : tamanho(0) {
        criaListaAdj(arquivo);
    }

    ~Grafo() {
        for(int i = 0; i < tamanho; i++) {
            No *lido = listaAdj[i];
            while(lido != nullptr) {
                No *apaga = lido;
                lido = apaga->getProx();
                delete apaga;
            }
        }
        delete[] listaAdj;
    }


    std::string getLista() {
        stringstream s;

        for(int i = 0; i < tamanho; i++) {
            s << "[" << i << "]";
            No *lido = listaAdj[i];
            while(lido != nullptr) {
                s << " ->" << lido->getVertice();
                lido = lido->getProx();
            }
            s << "\n";
        }
        return s.str();
    }

    std::string pegaGML(const string &arquivo) {
        GMLParser gml(listaAdj, tamanho, arquivo);
        return std::move(gml.gerarGML());
    }


private:

    void insereVertice(No **no, int vertice) {
        No *novo = new No(vertice);
        if(*no == nullptr) {
            *no = novo;
            return;
        }

        No *lido = *no;
        while(lido->getProx() != nullptr && novo < lido->getProx()) {
            lido = lido->getProx();
        }

        novo->setProx(lido->getProx());
        lido->setProx(novo);
    }
};
}

#endif // GRAFO_H
