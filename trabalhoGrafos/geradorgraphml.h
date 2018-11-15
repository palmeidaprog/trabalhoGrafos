#ifndef GERADORGRAPHML_H
#define GERADORGRAPHML_H

#include <fstream>
#include "grafo.h"
#include "no.h"

using std::vector;
using std::string;
using std::ofstream;
using std::endl;


namespace grafos {
class GeradorGraphML {
    string nomeArquivo;
    No<float> **lista;
    int tamanho;
    vector<No<float>*> vertices;
    GrafoTipo tipo;
    void salva();

public:
    GeradorGraphML(const string &nomeArquivo, No<float> **lista, int tamanho,
        const vector<No<float>*> vertices, GrafoTipo tipo);
    GeradorGraphML(const string &nomeArquivo, Grafo<float> *grafo);


};
}

#endif // GERADORGRAPHML_H
