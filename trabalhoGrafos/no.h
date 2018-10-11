#ifndef NOLISTA_H
#define NOLISTA_H

namespace grafos {
class No {
public:
    int vertice;
    No *prox;

    No(int vertice, No *prox = nullptr) : vertice(vertice), prox(prox) {}
    ~No() { }

public:
    inline bool operator>=(const No &b) {
        return this->vertice >= b.vertice;
    }

    inline bool operator<=(const No &b) {
        return this->vertice <= b.vertice;
    }

    inline bool operator<(const No &b) {
        return this->vertice < b.vertice;
    }
    inline bool operator>(const No &b) {
        return this->vertice > b.vertice;
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
};
}

#endif // NOLISTA_H
