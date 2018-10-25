#ifndef NOLISTA_H
#define NOLISTA_H

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

namespace grafos {
template <typename T = int>
class No {
public:
    int vertice;
    string verticeId, verticeLabel;
    string arestaId, arestaLabel;
    int r, g, b; // cores (gephi)
    float x, y; // posicao (gephi)
    T valorAresta; // peso da aresta (pode ser qualquer tipo)
    No *prox;

    No(int vertice, No *prox = nullptr) : vertice(vertice), prox(prox) {
        stringstream s;
        s << vertice;
        verticeId = s.str();
    }
    No(int vertice, const string &verticeId, No *prox = nullptr) :
            vertice(vertice), verticeId(verticeId), prox(prox) { }
    ~No() { }

public:
    inline bool operator>=(const No &b) {
        return this->valorAresta >= b.valorAresta;
    }

    inline bool operator<=(const No &b) {
        return this->valorAresta <= b.valorAresta;
    }

    inline bool operator<(const No &b) {
        return this->valorAresta < b.valorAresta;
    }
    inline bool operator>(const No &b) {
        return this->valorAresta > b.valorAresta;
    }

    int getVertice() const {
        return vertice;
    }

    void setVertice(int vertice) {
        this->vertice = vertice;
    }

    No *getProx() const {
        return prox;
    }

    void setProx(No *prox) {
        this->prox = prox;
    }

    const string &getVerticeId() const {
        return verticeId;
    }

    void setVerticeId(const string &verticeId) {
        No::verticeId = verticeId;
    }

    const string &getVerticeLabel() const {
        return verticeLabel;
    }

    void setVerticeLabel(const string &verticeLabel) {
        No::verticeLabel = verticeLabel;
    }

    const string &getArestaId() const {
        return arestaId;
    }

    void setArestaId(const string &arestaId) {
        No::arestaId = arestaId;
    }

    const string &getArestaLabel() const {
        return arestaLabel;
    }

    void setArestaLabel(const string &arestaLabel) {
        No::arestaLabel = arestaLabel;
    }

    int getR() const {
        return r;
    }

    void setR(int r) {
        No::r = r;
    }

    int getG() const {
        return g;
    }

    void setG(int g) {
        No::g = g;
    }

    int getB() const {
        return b;
    }

    void setB(int b) {
        No::b = b;
    }

    float getX() const {
        return x;
    }

    void setX(float x) {
        No::x = x;
    }

    float getY() const {
        return y;
    }

    void setY(float y) {
        No::y = y;
    }

    T getValorAresta() const {
        return valorAresta;
    }

    void setValorAresta(const T &valorAresta) {
        No::valorAresta = valorAresta;
    }

};
}

#endif // NOLISTA_H
