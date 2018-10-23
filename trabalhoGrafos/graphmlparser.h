#ifndef GRAPHMLPARSER_H
#define GRAPHMLPARSER_H

#include <fstream>
#include <string>
#include <iostream>
#include <stack>

using std::string;
using std::ifstream;
using std::stack;

namespace grafos {
class GraphMLParser {
    string nomeArquivo, json;

public:
    GraphMLParser(const std::string &nomeArquivo);

private:
    void parse();
    void tratarString(string &parse, stack<string> &pilha);
};
}

#endif // GRAPHMLPARSER_H
