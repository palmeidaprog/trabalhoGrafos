#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include <climits>
#include "grafo.h"
#include "kmeansmodo.h"
#include "cluster.h"

using std::vector;

namespace grafos { namespace kmeans {
template <typename T>
class Kmeans {
    int numeroDeClusters, maxIteracoes;
    Grafo<T> *grafo;
    bool modificou, colorir;
    KmeansModo modo;
    vector<Cluster<T>*> clusters;

    void inicializaClusters() {
        vector<Centroid<T>*> c = grafo->getCentroid(numeroDeClusters);
        for(size_t i = 0; i < numeroDeClusters; i++) {
            clusters.emplace_back(new Cluster<T>(i, c[i]));
        }
    }

    bool iteracao() {
        IteradorGrafo<T> *iterador = grafo->getIterador();
        bool modificou = false;

        // adiciona os Nos aos clusters
        while(iterador->hasNext()) {
            No<T> *no = iterador->next();
            T minimo = clusters[0]->compara(no->getValorAresta());
            int cluster = 0;

            for(size_t i = 0; i < clusters.size(); i++) {
                if(clusters[i]->compara(no->getValorAresta()) < minimo) {
                    minimo = clusters[i]->compara(no->getValorAresta());
                    cluster = i;
                }
            }
            if(no->getCluster() != cluster) {
                if(no->getCluster() != -1) {
                    clusters[no->getCluster()]->remove(no);
                }
                clusters[cluster]->adiciona(no);
                modificou = true;
            }

        }
        delete iterador;
        return modificou;
    }



public:
    Kmeans(int numeroDeClusters, Grafo<T> *grafo, int maximoIteracoes =
            INT_MAX, bool colorir = true,  KmeansModo modo =
                    KmeansModo::PESO_ARESTAS) :
            numeroDeClusters(numeroDeClusters), maxIteracoes(maxIteracoes),
            grafo(grafo), modificou(true), colorir(colorir), modo(modo) {
        inicializaClusters();
        executa();
    }
    ~Kmeans() {
        for(auto c : clusters) {
            delete c;
        }
    }

    void executa() {
        int iter = 0;
        bool modificou = true;
        while(modificou && iter++ <= maxIteracoes) {
            modificou = iteracao();
        }
        if(colorir) {
            for(auto i : clusters) {
                i->colorir();
            }
        }
    }

    const vector<Cluster<T>*> &getClusters() {
        return clusters;
    }
};
}}

#endif // KMEANS_H
