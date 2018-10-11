#ifndef GRAFO_H
#define GRAFO_H

#include <cstdio>
#include <string>
#include <sstream>

using std::stringstream;

namespace Grafos {
template<typename T>
class Grafo {
    int tamanho;

    struct No {
        int vertice;
        No *prox;

        No(int vertice, No *prox = nullptr) : vertice(vertice), prox(prox) {}
        ~No() { }

        bool operator>=(const No &b) {
            return this->vertice >= b.vertice;
        }

        bool operator<=(const No &b) {
            return this->vertice <= b.vertice;
        }

        bool operator<(const No &b) {
            return this->vertice < b.vertice;
        }
        bool operator>(const No &b) {
            return this->vertice > b.vertice;
        }
    };

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
                lido = apaga->prox;
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
                s << "->" << lido->vertice;
                lido = lido->prox;
            }
            s << "\n";
        }
        return s.str();
    }


private:

    void insereVertice(No **no, int vertice) {
        No *novo = new No(vertice);
        if(*no == nullptr) {
            *no = novo;
            return;
        }

        No *lido = *no;
        while(lido->prox != nullptr && novo < lido->prox) {
            lido = lido->prox;
        }

        novo->prox = lido->prox;
        lido->prox = novo;
    }




};
}

#endif // GRAFO_H
