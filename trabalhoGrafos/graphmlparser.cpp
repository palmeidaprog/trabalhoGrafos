#include "graphmlparser.h"

grafos::GraphMLParser::GraphMLParser(const std::string &nomeArquivo) :
    nomeArquivo(nomeArquivo) {
    parse();
}

grafos::GraphMLParser::GraphMLParser(grafos::Grafo grafo) :
    grafo(std::move(grafo)) { }

void grafos::GraphMLParser::parse() {
    ifstream in(nomeArquivo);
    stack<string> pilha;

    if(!in.is_open()) {
        return;
    }

    string s;


    while(in.good()) {
        getline(in, s);
        scanner(s, pilha);

        if(pilha.empty()) {
            // <graph ... >
            if(s.find("<graph")) {
               pilha.push("graph");
               long pos = s.find(" ");
               s.erase(s.begin(), s.begin() + pos);
               while(s.length() > 0) {
                   pos = s.find("=");
                   if(pos == string::npos) {

                   }
               }

            }
            continue;
        }
    }

    in.close();
}

void grafos::GraphMLParser::scanner(string &parse, stack<string>
                                         &pilha) {
    Procurando procurando = Procurando::GRAFO;
    GrafoTipo tipo;
    long pos = 0;
    string s;
    while(pos < parse.size()) {
        switch(procurando) {
        case Procurando::GRAFO:
            if(comecaCom("<graph", s, pos)) {
                procurando = Procurando::PARAMETRO_GRAFO;
            } else {
                pos = parse.size();
            }
            break;
        case Procurando::PARAMETRO_GRAFO:

        }


        if(parse[i] == '<') {
            procurando = Procurando::COMANDO;
            s = "";
        } else if(oarse[i] == '/') {
            procurando = Procurando::FINALIZA;
            s = "";
        } else if(parse[i] == ' ') {
            if(procurando == Procurando::COMANDO) {
                pilha.push(s);
            }
        } else {
            s += parse[i];
        }
        ++i;
    }

}

Parametro grafos::GraphMLParser::proxParametro(std::__1::string &parse, int pos) {
    Parametro p;
    string *s = p.chave;
    while(pos < parse.size()) {
        if(parse[pos] == '=' && s == p.chave) {
            s = p.valor;
        } else if("")
        ++pos;
    }
}


bool grafos::GraphMLParser::comecaCom(const string &procurar,
                                      const string &palavra, int &pos) {

    while(palavra[pos] == ' ') {
        ++pos;
    }

    for(int i = 0, j = pos; j < palavra.size(); i++, j++) {
        if(tolower(procurar[i]) != tolower(palavra[pos])) {
            return false;
        }
    }
    pos = j;
    return true;
}

void grafos::GraphMLParser::interpretaGrafo(const std::__1::string &s,
                                            int &pos) {


}
