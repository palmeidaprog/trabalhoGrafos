#include "graphmlparser.h"

grafos::GraphMLParser::GraphMLParser(const std::string &nomeArquivo) :
    nomeArquivo(nomeArquivo), procurando(Procurando::GRAFO) grafo(nullptr) {
    parse();
}

grafos::GraphMLParser::GraphMLParser(grafos::Grafo *grafo) :
    grafo(grafo) { }

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
    }

    in.close();
}

void grafos::GraphMLParser::scanner(string &parse, stack<string>
                                         &pilha) {
    GrafoTipo tipo;
    long pos = 0;
    string s, grafoId;
    while(pos < parse.size()) {
        switch(procurando) {
            case Procurando::GRAFO:
            if(comecaCom("<graph", s, pos) {
                procurando = Procurando::PARAMETRO_GRAFO;
            } else {
                pos = parse.size();
            }
            break;
        case Procurando::PARAMETRO_GRAFO:
            interpretaGrafo(s, pos);
            procurando = Procurando::NODE;
            break;
        case Procurando::NODE:
            if(comecaCom("<node", s, pos)) {
                interpretaNo(s, pos);
            } else {
                atualizaEstado(s, pos);
            }
            break;
        case Procurando::NODE_DATA:
            if(comecaCom("<node", s, pos)) {
                interpretaNoData(s, pos);
            } else {
                atualizaEstado(s, pos);
            }
            break;
        case Procurando::ARESTA:
            if(comecaCom("<edge", s, pos)) {
                interpretaAresta(s, pos);
            } else {
                atualizaEstado(s, pos);
            }
            break;
        case Procurando::ARESTA_DATA:
            if(comecaCom("<node", s, pos)) {
                interpretaArestaData(s, pos);
            } else {
                atualizaEstado(s, pos);
            }
            break;
        default: // FIM
            break;
        }
    }
}


// se "atualizar" nao for informado ou for true, no final o pos marcará a
// posição da proxima palavra, se falso pos so mudara se for para pular
// espaços.
bool grafos::GraphMLParser::comecaCom(const string &procurar,
                                      const string &palavra, long &pos,
                                      bool atualiza) {
    removeEspacos(palavra, pos);
    long j = pos;
    for(int i = 0; j < palavra.size(); i++, j++) {
        if(tolower(procurar[i]) != tolower(palavra[pos])) {
            return false;
        }
    }
    if(atualiza) {
        pos = j;
    }
    removeEspacos(palavra, pos);
    return true;
}

void grafos::GraphMLParser::interpretaGrafo(const string &s, long &pos) {
    string id;
    GrafoTipo tipo = GrafoTipo::NORMAL;

    while(pos < s.size()) {
        if(comecaCom("id=" ,s, pos)) {
            id = pegaValor(s, pos);
        } else if(comecaCom("defaultgraph=", s, pos)) {
            tipo = (pegaValor(s, pos) == "directed") ? GrafoTipo::ORIENTADO :
                GrafoTipo::NORMAL;
        } else if(comecaCom("/", s, pos)) {
            return;
        } else if(comecaCom(">", s, pos)) {
            grafo = new Grafo(tipo, id);
            return;
        }
    }
}

// move a posicao pos para onde nao há espacos
void grafos::GraphMLParser::removeEspacos(const string &s, long &pos) {
    while(s[pos] == ' ') {
        ++pos;
    }
}

// pega o valor da prox string
string grafos::GraphMLParser::pegaValor(const string &s, long &pos) {
    char para;
    string lido;

    if(comecaCom("\"", s, pos)) {
        para = '\"';
    } else {
        para = ' ';
    }

    while(s[pos] != para) {
        lido += s[pos];
    }
    ++pos;
    return lido;
}

void grafos::GraphMLParser::interpretaNo(const string &s, long &pos) {

}

// atualiza o atributo da classe procurando, quando a previsão do loop do
// scanner errou a progressão entre as leituras.
grafos::GraphMLParser::Procurando grafos::GraphMLParser::atualizaEstado(
    const string &s, long &pos) {
    if(comecaCom("<node", s, pos, false)) {
        return Procurando::NODE;
    } else if(comecaCom("<data", s, pos, false)) {
        return (procurando == Procurando::ARESTA) ? Procurando::ARESTA_DATA ?
            Procurando::NODE_DATA;
    } else if(comecaCom("<edge", s, pos, false)) {
        return Procurando::ARESTA;
    } else if(comecaCom("</edge", s, pos)) {
        ++pos;
        return Procurando::ARESTA;
    } else if(comecaCom("</data", s, pos)) {
        ++pos;
        return procurando;
    } else if(comecaCom("</node", s, pos)) {
        ++pos;
        return Procurando::NODE;
    } else {
        return Procurando::FIM;
    }
}

