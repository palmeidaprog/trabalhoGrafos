#ifndef CLUSTER_H
#define CLUSTER_H

#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "centroid.h"
#include "no.h"
#include "kmeansmodo.h"


using std::string;
using std::vector;

namespace grafos { namespace kmeans {
template <typename T>
class Cluster {
    int clusterNumero;
    string clusterLabel;
    Centroid<T> *centroid;
    vector<No<T>*> set;
    KmeansModo modo;
    struct Cor {
        int r, g, b;
        Cor() {
            r = rand() % 256;
            g = rand() % 256;
            b = rand() % 256;
        }
        ~Cor() { }
    };
    Cor cor;

    void atualizaCentroid() {
        T soma = 0;
        for(size_t i = 0; i < set.size(); i++) {
            soma += set[i]->getValorAresta();
        }
        soma /= set.size();
        centroid->setData(soma);
    }

public:
    Cluster(int clusterNumero, Centroid<T> *centroid, KmeansModo modo =
            KmeansModo::PESO_ARESTAS, const string &label = "") :
            clusterNumero(clusterNumero), centroid(centroid),
            modo(modo), clusterLabel(label) { }

    ~Cluster() {
        delete centroid;
    }

    const vector<No<T>*> &getClusterData() {
        return set;
    }

    void adiciona(No<T> *no) {
        set.push_back(no);
        no->setCluster(clusterNumero);
        atualizaCentroid();
    }

    void remove(No<T> *no) {
        for(size_t i = 0; i < set.size(); i++) {
            if(set[i] == no) {
                set.erase(set.begin() + i);
            }
        }
    }

    const T &getCentroid() {
        return centroid->getData();
    }

    T compara(const T &data) const {
        return std::abs(data - this->centroid->getData());
    }

    void colorir() {
        for(auto no : set) {
            no->getOrigem()->setR(cor.r);
            no->getOrigem()->setG(cor.g);
            no->getOrigem()->setB(cor.b);
        }
    }
};
}}


#endif // CLUSTER_H
