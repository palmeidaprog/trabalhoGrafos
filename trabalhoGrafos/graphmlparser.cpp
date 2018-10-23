#include "graphmlparser.h"

grafos::GraphMLParser::GraphMLParser(const std::string &nomeArquivo) :
    nomeArquivo(nomeArquivo) {
    parse();
}

void grafos::GraphMLParser::parse() {
    ifstream in(nomeArquivo);
    stack<string> pilha;

    if(!in.is_open()) {
        return;
    }

    string s;

    while(in.good()) {
        getline(in, s);
        if(pilha.empty() && s.find("<graph")) {

        }
    }

    in.close();
}

void grafos::GraphMLParser::tratarString(string &parse, stack<string>
                                         &pilha) {
    long pos, fim;
    while((pos = parse.find("<")) != string::npos
          && parse.find(">")){
        parse = parse.substr(pos + 1);
    }
}
