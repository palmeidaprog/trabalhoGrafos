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
    string nomeArquivo, json;
    Grafo grafo;

    struct Parametro {
        string chave, valor;
        Parametro() { }
        ~Parametro() { }
    };

    enum class Procurando {
        GRAFO, PARAMETRO_GRAFO, NODE, PARAMETRO_NODE, NODE_DATA,
    };

public:
    GraphMLParser(const std::string &nomeArquivo);
    GraphMLParser(Grafo grafo);


private:
    void parse();
    void scanner(string &parse, stack<string> &pilha);
    Parametro proxParametro(string &parse, int pos);
    bool comecaCom(const string &procurar, const string &palavra, int &pos);
    void interpretaGrafo(const string &s, int &pos);
};
}

#endif // GRAPHMLPARSER_H
