#ifndef GRAPHMLPARSER_H
#define GRAPHMLPARSER_H

#include <fstream>
#include <string>
#include <iostream>
#include <stack>
#include <cctype>
#include "grafo.h"
#include "grafotipo.h"

using std::string;
using std::ifstream;
using std::stack;
using grafos::Grafo;

namespace grafos {
class GraphMLParser {
    string nomeArquivo;
    Procurando procurando;
    Grafo *grafo; // não destruir ao destruir a classe

    enum class Procurando {
        GRAFO, PARAMETRO_GRAFO, NODE, NODE_DATA, ARESTA, ARESTA_DATA, FIM
    };

public:
    GraphMLParser(const std::string &nomeArquivo);
    GraphMLParser(Grafo *grafo);


private:
    void parse();
    void scanner(string &parse, stack<string> &pilha);
    bool comecaCom(const string &procurar, const string &palavra, long &pos,
        bool atualiza = true);
    void interpretaGrafo(const string &s, long &pos);
    void interpretaNo(const string &s, long &pos);
    void removeEspacos(const string &s, long &pos);
    string pegaValor(const string &s, long &pos);
    Procurando atualizaEstado(const string &s, long &pos);
};
}

#endif // GRAPHMLPARSER_H
