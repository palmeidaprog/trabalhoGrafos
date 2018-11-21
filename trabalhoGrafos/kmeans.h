#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include <climits>
#include <sstream>
#include "grafo.h"
#include "kmeansmodo.h"
#include "cluster.h"

using std::vector;
using std::stringstream;

namespace grafos { namespace kmeans {
template <typename T>
class Kmeans {
    int numeroDeClusters, maxIteracoes, iter;
    Grafo<T> *grafo;
    bool modificou, colorir;
    KmeansModo modo;
    vector<Cluster<T>*> clusters;

    void inicializaClusters() {
        vector<Centroid<T>*> c;
        if(modo == KmeansModo::PESO_ARESTAS) {
            c = grafo->getCentroid(numeroDeClusters, modo);
        } else {
            c = grafo->getCentroid(numeroDeClusters, modo);
        }
        for(size_t i = 0; i < numeroDeClusters; i++) {
            clusters[i] = new Cluster<T>(i, c[i], modo);
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

    /*bool iteracaoDistancia() {
        IteradorGrafo<T> *iterador = grafo->getIterador();
        bool modificou = false;

        // adiciona os Nos aos clusters
        while(iterador->hasNext()) {
            No<T> *no = iterador->next();
            float minimo = clusters[0]->distancia(no);
            int cluster = 0;

            for(size_t i = 0; i < clusters.size(); i++) {
                if(clusters[i]->distancia(no) < minimo) {
                    minimo = clusters[i]->distancia(no);
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
    }*/

    bool iteracaoDistancia() {
        IteradorGrafo<T> *iterador = grafo->getIterador();
        bool modificou = false;
        vector<No<T>*> vertices = grafo->getVertices();

        // adiciona os Nos aos clusters
        for(size_t i = 0; i < vertices.size(); i++) {
            No<T> *no = vertices[i];
            float minimo = clusters[0]->distancia(no);
            int cluster = 0;

            for(size_t i = 0; i < clusters.size(); i++) {
                if(clusters[i]->distancia(no) < minimo) {
                    minimo = clusters[i]->distancia(no);
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
        return modificou;
    }



public:
    Kmeans(int numeroDeClusters, Grafo<T> *grafo, int maximoIteracoes =
            INT_MAX, bool colorir = true,  KmeansModo modo =
                    KmeansModo::PESO_ARESTAS) :
            numeroDeClusters(numeroDeClusters), maxIteracoes(maximoIteracoes),
            grafo(grafo), modificou(true), colorir(colorir), modo(modo) {
        clusters.resize(numeroDeClusters);
        clusters.shrink_to_fit();
        inicializaClusters();
        executa();
    }
    ~Kmeans() {
        if(clusters.size() > 0) {
            for(auto c : clusters) {
                delete c;
            }
        }
    }

    void executa() {
        iter = 0;
        bool modificou = true;
        while(modificou && iter++ < maxIteracoes) {
            if(modo == KmeansModo::PESO_ARESTAS) {
                modificou = iteracao();
            } else {
                modificou = iteracaoDistancia();
            }
        }
        if(colorir) {
            for(auto i : clusters) {
                i->colorir();
            }
        }
    }

    string toString() {
        stringstream s;
        s << "Clusters " << numeroDeClusters <<
                          " - Iteracoes feitas:" << iter << endl << endl;
        for(auto a : clusters) {
            s << a->toString();
        }
        return s.str();
    }

    const vector<Cluster<T>*> &getClusters() {
        return clusters;
    }
};
}}

#endif // KMEANS_H
