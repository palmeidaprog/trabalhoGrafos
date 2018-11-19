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
        for(size_t i = 0; i < numeroDeClusters; i++) {
            clusters.emplace_back();
        }
    }

    bool adicionaDados() {
        IteradorGrafo<T> iterador = grafo->getIterador();
        bool modificou = false;

        // adiciona os Nos aos clusters
        while(iterador.hasNext()) {
            No<T> *no = iterador.next();
            T minimo = clusters[0]->compara(no);
            int cluster = 0;

            for(size_t i = 0; i < clusters.size(); i++) {
                if(clusters[i]->compara(no) < minimo) {
                    minimo = clusters[i]->compara(no);
                    cluster = i;
                }
            }
            if(no->getCluster() == -1) {
                clusters[cluster]->adiciona(no);
            } else if(no->getCluster() != cluster) {
                clusters[no->getCluster()]->remove(no);
                clusters[cluster]->adiciona(no);
            }

        }

        return modificou;
    }



public:
    Kmeans(int numeroDeClusters, Grafo<T> *grafo, bool colorir = true,
            KmeansModo modo = KmeansModo::PESO_ARESTAS,
            int maximoIteracoes = INT_MAX) :
            numeroDeClusters(numeroDeClusters), maxIteracoes(maxIteracoes),
            grafo(grafo), modificou(true), colorir(colorir), modo(modo) {
        inicializaClusters();
        executa();
    }
    ~Kmeans() {  }

    void executa() {
        adicionaDados();

        //
        int iter = 1;
        bool modificou = true;
        while(modificou && iter++ <= maxIteracoes) {

        }
    }
};
}}

#endif // KMEANS_H
