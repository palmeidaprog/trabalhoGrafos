#ifndef GRAFO_H
#define GRAFO_H

#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "no.h"
#include "gmlparser.h"
#include "grafotipo.h"

using std::stringstream;
using std::string;
using std::vector;

namespace grafos {
template <typename T = float>
class Grafo {
    int tamanho;
    //friend GraphMLParser;
    GrafoTipo tipo;
    string id;
    vector<No<T>*> vertices;
    No<T> **listaAdj;
    int arestas;

public:

    Grafo(FILE *arquivo, GrafoTipo tipo = GrafoTipo::NORMAL) : tamanho(0) {
        criaListaAdj(arquivo);
    }
    Grafo(GrafoTipo tipo = GrafoTipo::NORMAL, const string &id = "") :
        tipo(tipo), id(id), tamanho(0), listaAdj(nullptr){
    }

    Grafo(No<T> **listaAdjacente, const vector<No<T>*> &vertices,
          GrafoTipo tipo = GrafoTipo::VALORADO_ORIENTADO, int arestas = 0,
          const string &id = "") : listaAdj(listaAdjacente),
        vertices(vertices), tipo(tipo), id(id), arestas(arestas)
    { }

    ~Grafo() {
        for(int i = 0; i < tamanho; i++) {
            No<T> *lido = listaAdj[i];
            while(lido != nullptr) {
                No<T> *apaga = lido;
                lido = apaga->getProx();
                delete apaga;
            }
        }
        delete[] listaAdj;
    }

    int getVerticesNum() const {
        return vertices.size();
    }

    int getArestasNum() const {
        return arestas;
    }

    GrafoTipo getTipo() const {
        return tipo;
    }


    std::string getLista() {
        stringstream s;

        for(int i = 0; i < tamanho; i++) {
            s << "[" << i << "]";
            No<T> *lido = listaAdj[i];
            while(lido != nullptr) {
                s << " ->" << lido->getVertice();
                lido = lido->getProx();
            }
            s << "\n";
        }
        return s.str();
    }

    std::string pegaGML(const string &arquivo) {
        GMLParser<T> gml(listaAdj, tamanho, arquivo);
        return std::move(gml.gerarGML());
    }

    const string &getId() const {
        return id;
    }

    void setId(const string &id) {
        Grafo::id = id;
    }

    No<T> **getListaAdjacente() {
        return listaAdj;
    }

    vector<No<T>*> getVertices() {
        return vertices;
    }


private:
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
        listaAdj = new No<T>*[tamanho];
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






private:

    void insereVertice(No<T> **no, int vertice) {
        No<T> *novo = new No<T>(vertice);
        if(*no == nullptr) {
            *no = novo;
            return;
        }

        if(novo->getVertice() <= (*no)->getVertice()) {
            novo->setProx(*no);
            *no = novo;
            return;
        }

        No<T> *lido = *no, *ant = NULL;
        while(lido != nullptr && novo->getVertice() >
              lido->getVertice()) {
            ant = lido;
            lido = lido->getProx();
        }

        ant->setProx(novo);
        novo->setProx(lido);

    }
};
}

#endif // GRAFO_H
