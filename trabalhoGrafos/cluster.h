#ifndef CLUSTER_H
#define CLUSTER_H

#include <string>
#include <vector>
#include "centroid.h"
#include "no.h"


using std::string;
using std::vector;

namespace grafos { namespace kmeans {
template <typename T>
class Cluster {
    int clusterNumero;
    string clusterLabel;
    Centroid<T> *centroid;
    vector<No<T>*> set;

    void atualizaCentroid() {
        T soma = 0;
        for(size_t i = 0; i < set.size(); i++) {
            soma += set[i]->getValorAresta();
        }
        soma /= set.size();
        centroid->setData(soma);
    }

public:
    Cluster(int clusterNumero, Centroid<T> *centroid,
            const string &label = "") : clusterNumero(clusterNumero),
            centroid(centroid), clusterLabel(label) { }

    ~Cluster() {
        delete centroid;
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
};
}}


#endif // CLUSTER_H
