#ifndef CLUSTER_H
#define CLUSTER_H

#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <cstdlib>
#include "centroid.h"
#include "no.h"
#include "kmeansmodo.h"


using std::string;
using std::vector;
using std::stringstream;
using std::endl;

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
        for (size_t i = 0; i < set.size(); i++) {
            soma += set[i]->getValorAresta();
        }
        soma /= set.size();
        centroid->setData(soma);
    }

    void atualizaDistancia() {
        float somaX = 0, somaY = 0;
        for (size_t i = 0; i < set.size(); i++) {
            somaX += set[i]->getX();
            somaY += set[i]->getY();
        }
        somaX /= set.size();
        somaY /= set.size();
        centroid->setX(somaX);
        centroid->setY(somaY);
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
        if(modo == KmeansModo::PESO_ARESTAS) {
            atualizaCentroid();
        } else {
            atualizaDistancia();
        }
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

    float distancia(No<T> *no) const {
        return sqrt(pow(centroid->getY() - no->getY(), 2) +
        pow(centroid->getX() - no->getX(), 2));
    }

    string toString() {
        stringstream s;
        s << "Cluster " << clusterNumero << " (" << clusterLabel << ") = { "
          << "Centroid(" << centroid->getData() << ", " << centroid->getX()
          << ", " << centroid->getY() << ")" << endl;
        for(size_t i = 0; i < set.size(); i++) {
            No<T> *no = set[i];
            if(modo == KmeansModo::PESO_ARESTAS) {
                s << "\t (" << no->getOrigem()->getVerticeId() << ") --(" <<
                  no->getValorAresta() << ")--> (" << no->getVerticeId() << ")" <<
                  endl;
            } else {
                s << "\t (" << no->getVerticeId() << " : " <<
                    no->getVerticeId() << ")" << endl;
            }
        }
        s << "}" << endl;
        return s.str();
    }

    void colorir() {
        for(auto no : set) {
            if(modo == KmeansModo::PESO_ARESTAS) {
                no->getOrigem()->setR(cor.r);
                no->getOrigem()->setG(cor.g);
                no->getOrigem()->setB(cor.b);
            } else {
                no->setR(cor.r);
                no->setG(cor.g);
                no->setB(cor.b);
            }

        }
    }
};
}}


#endif // CLUSTER_H
