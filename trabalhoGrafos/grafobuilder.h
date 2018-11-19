#ifndef GRAFOBUILDER_H
#define GRAFOBUILDER_H

#include <map>
#include <string>
#include <vector>
#include "no.h"
#include "grafo.h"
#include "grafotipo.h"

using std::map;
using std::string;
using std::vector;

namespace grafos {

template <typename T = float>
class GrafoBuilder {
    map<const string, No<T>*> vertices;
    vector<No<T>*> verticePos;
    GrafoTipo tipo;
    int arestas = 0;
    string id;
    No<T> **listaAdj;
    bool listaCriada;

    void criarListaAdj() {
        if(listaCriada) {
            return;
        }

        listaAdj = new No<T>*[vertices.size()];
        for(int i = 0; i < vertices.size(); i++) {
            listaAdj[i] = nullptr;
        }
        listaCriada = true;
    }

    void insereVertice(No<T> **no, No<T> *novo) {
        if(*no == nullptr) {
            *no = novo;
            return;
        }

        if(novo->getVertice() <= (*no)->getVertice()) {
            novo->setProx(*no);
            no = &novo;
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

public:
    GrafoBuilder(GrafoTipo tipo = GrafoTipo::VALORADO_ORIENTADO,
            const string &id = "") : tipo(tipo), listaAdj(nullptr), id(id),
    listaCriada(false) { }

    ~GrafoBuilder() {
        //vertices.clear();
    }

    GrafoBuilder *adicionaVertice(No<T> *no) {
        no->setVertice(static_cast<int>(vertices.size()));
        vertices[no->getVerticeId()] = no;
        verticePos.push_back(no);
        return this;
    }

    No<T> *getNo(const string &id) {
        return vertices.at(id);
    }


    void setTipo(GrafoTipo tipo) {
        GrafoBuilder::tipo = tipo;
    }

    void enableValorado() {
        if(tipo == GrafoTipo::NORMAL) {
            tipo = GrafoTipo::VALORADO;
        } else if(tipo == GrafoTipo::ORIENTADO) {
            tipo = GrafoTipo::VALORADO_ORIENTADO;
        }
    }

    GrafoBuilder *adicionaAresta(const string &id, const string &source,
                                 No<T> *target) {
        criarListaAdj();
        target->setArestaId(id);
        target->setOrigem(getNo(source));
        insereVertice(&listaAdj[getNo(source)->getVertice()], target);
        ++arestas;
        return this;
    }

    Grafo<T> *build() {
        return new Grafo<T>(listaAdj, verticePos, tipo, arestas, id);
    }

};
}

#endif // GRAFOBUILDER_H
