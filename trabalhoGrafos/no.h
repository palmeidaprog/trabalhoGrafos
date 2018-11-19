#ifndef NOLISTA_H
#define NOLISTA_H

#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::stringstream;
using std::vector;

namespace grafos {
template <typename T = float>
class No {
    No<T> *origem;
    int vertice;
    string verticeId, verticeLabel;
    string arestaId, arestaLabel;
    int r, g, b; // cores (gephi)
    float x, y, size; // posicao (gephi)
    T valorAresta; // peso da aresta (pode ser qualquer tipo)
    No *prox;
    int cluster;

    struct Data {
        string key;
        string value;

        Data(const string &key, const string &value) : key(key), value(value)
        { }
        ~Data() { }
    };
    vector<Data> data, arestaData;

public:

    // copia
    No(const No<T> *copia) : prox(nullptr) {
        origem = copia->origem;
        vertice = copia->vertice;
        verticeId = copia->verticeId;
        verticeLabel = copia->verticeLabel;
        arestaId = copia->arestaId;
        arestaLabel = copia->arestaLabel;
        r = copia->r;
        g = copia->g;
        b = copia->b;
        x = copia->x;
        y = copia->y;
        size = copia->size;
        valorAresta = copia->valorAresta;
        cluster = copia->cluster;
    }

    No(int vertice, No<T> *prox = nullptr) : vertice(vertice), prox(prox) {
        stringstream s;
        s << vertice;
        verticeId = s.str();
    }


    No(const string &id) : verticeId(id), prox(nullptr) { }

    No(int vertice, const string &verticeId, No<T> *origem, No *prox = nullptr) :
            vertice(vertice), verticeId(verticeId), origem(origem), prox(prox) { }
    ~No() { }

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

    float getSize() const {
        return size;
    }

    void setSize(float size) {
        No::size = size;
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

    No<T> *getOrigem() const {
        return origem;
    }

    void setOrigem(No<T> *origem) {
        No::origem = origem;
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

    int getCluster() const {
        return cluster;
    }

    void setCluster(int cluster) {
        No::cluster = cluster;
    }

    T getValorAresta() const {
        return valorAresta;
    }

    void setValorAresta(const T &valorAresta) {
        No::valorAresta = valorAresta;
    }

    void adicionaData(const string &key, const string &valor) {
        data.emplace_back(key, valor);
    }

    void adicionaArestaData(const string &key, const string &valor) {
        arestaData.emplace_back(key, valor);
    }

};
}

#endif // NOLISTA_H
