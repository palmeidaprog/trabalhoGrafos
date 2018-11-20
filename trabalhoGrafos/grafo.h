#ifndef GRAFO_H
#define GRAFO_H

#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <map>
#include "no.h"
#include "gmlparser.h"
#include "grafotipo.h"
#include "iteradorgrafo.h"
#include "kmeansmodo.h"
#include "centroid.h"

using std::stringstream;
using std::string;
using std::vector;
using grafos::kmeans::Centroid;
using grafos::kmeans::KmeansModo;

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
          const string &id = "") : tamanho(vertices.size()),
        listaAdj(listaAdjacente), vertices(vertices), tipo(tipo), id(id),
        arestas(arestas) { }

    ~Grafo() {
        for(int i = 0; i < vertices.size(); i++) {
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

        for(int i = 0; i < vertices.size(); i++) {
            s << "[" << i << "]";
            No<T> *lido = listaAdj[i];
            while(lido != nullptr) {
                s << " ->" << lido->getVertice() << "(" <<
                    lido->getCluster() << ")";
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

    IteradorGrafo<T> *getIterador() {
        return new IteradorGrafo<T>(listaAdj, tamanho);
    }

    void gerarPesosAleatorios(int max) {
        max *= 10;
        for(int i = 0; i < tamanho; i++) {
            No<T> *no = listaAdj[i];
            while(no != nullptr) {
                double num = (rand() % max) / 10.0;
                no->setValorAresta(num);
                no = no->getProx();
            }
        }
    }

    vector<Centroid<T>*> getCentroid(int numeroDeCentroids,
            KmeansModo modo) {
        vector<Centroid<T>*> centroids;
        for(int i = 0; i < numeroDeCentroids; i++) {
            int indice;
            if(i == 0) {
                indice = 0;
            } else if(i == 1) {
                indice = tamanho - 1;
            } else {
                indice = (tamanho - 1) / i + ((i & 1) ? (tamanho-1)/2 : 0);
            }
            while(listaAdj[indice] == nullptr) {
                if(++indice >= tamanho) {
                    indice = rand() % tamanho;
                }
            }
            if(modo == KmeansModo::PESO_ARESTAS) {
                centroids.push_back(new Centroid<T>(
                        listaAdj[indice]->getValorAresta()));
            } else if(modo == KmeansModo::DISTANCIA_EUCLIDIANA) {
                centroids.push_back(new Centroid<T>(
                        listaAdj[indice]->getValorAresta(),
                        listaAdj[indice]->getX(),
                        listaAdj[indice]->getY()));
            }
        }
        return centroids;
    }

    vector<Centroid<T>*> getCentroidDistancia(int numeroDeCentroids,
            KmeansModo modo) {
        vector<Centroid<T>*> centroids;

        float menorX = INT_MAX, maiorX = INT_MIN, menorY = INT_MAX,
                maiorY = INT_MIN;
        for(int i = 0; i < vertices.size(); i++) {
            No<T> *no = listaAdj[i];
            while(no != nullptr) {
                menorX = std::min(menorX, no->getX());
                menorY = std::min(menorY, no->getY());
                maiorX = std::max(maiorX, no->getX());
                maiorY = std::max(maiorY, no->getY());
                no = no->getProx();
            }
        }

        double diffX = (maiorX - menorX) / (numeroDeCentroids + 1);
        double diffY = (maiorY - menorY) / (numeroDeCentroids + 1);
        for(int i = 0; i < numeroDeCentroids; i++) {
            centroids.push_back(new Centroid<T>(
                                    0,
                                    diffX * (i+1),
                                    diffY * (i+1)));
        }

        return centroids;
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
