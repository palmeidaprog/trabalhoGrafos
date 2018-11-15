#ifndef GRAPHMLPARSER_H
#define GRAPHMLPARSER_H

#include <fstream>
#include <string>
#include <iostream>
#include <stack>
#include <cctype>
#include "grafo.h"
#include "grafotipo.h"
#include "graphmlparser.h"
#include "grafobuilder.h"

using std::string;
using std::ifstream;
using std::stack;

namespace grafos {
class GraphMLParser {
    string nomeArquivo;
    GrafoBuilder<float> *builder; // não destruir ao destruir a classe
    No<float> *no;
    Grafo<float> *grafo;
    bool finaliza, valorado;
    int count;

    enum class Procurando {
        GRAFO, PARAMETRO_GRAFO, NODE, NODE_DATA, ARESTA,
        ARESTA_DATA, FIM
    };
    Procurando procurando;

public:
    GraphMLParser(const std::string &nomeArquivo);
    GraphMLParser(Grafo<float> *grafo);
    ~GraphMLParser();

    Grafo<float> *getGrafo();

private:
    void montaAresta(const string &id, const string &source,
                     const string &target);
    void parse();
    void scanner(string &parse);
    bool comecaCom(const string &procurar, const string &palavra, long &pos,
        bool atualiza = true);
    void interpretaGrafo(const string &s, long &pos);
    void interpretaNo(const string &s, long &pos);
    void interpretaNoData(const string &s, long &pos);
    void interpretaAresta(const string &s, long &pos);
    void interpretaArestaData(const string &s, long &pos);
    void removeEspacos(const string &s, long &pos);
    string pegaValor(const string &s, long &pos, bool dentroDeData = false);
    Procurando atualizaEstado(const string &s, long &pos);
    void adicionaAresta(GrafoBuilder<float> *builder, const string &id,
            const string &source, const string &target);
};
}

#endif // GRAPHMLPARSER_H
