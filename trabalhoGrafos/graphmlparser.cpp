#include "graphmlparser.h"

grafos::GraphMLParser::GraphMLParser(const std::string &nomeArquivo) :
    nomeArquivo(nomeArquivo), no(nullptr), grafo(nullptr), finaliza(false),
    valorado(false), count(0), procurando(Procurando::GRAFO) {
    parse();
}

grafos::GraphMLParser::GraphMLParser(grafos::Grafo<float> *grafo) :
    no(nullptr), grafo(grafo) { }

void grafos::GraphMLParser::parse() {
    ifstream in(nomeArquivo);

    if(!in.is_open()) {
        return;
    }

    string s;
    while(in.good() && !finaliza) {
        getline(in, s);
        scanner(s);
    }

    in.close();
}

void grafos::GraphMLParser::scanner(string &s) {
    GrafoTipo tipo;
    long pos = 0;
    string grafoId;
    while(static_cast<size_t>(pos) < s.size()) {
        switch(procurando) {
            case Procurando::GRAFO:
            if(comecaCom("<graph", s, pos)) {
                procurando = Procurando::PARAMETRO_GRAFO;
            } else {
                pos = s.size();
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
                procurando = atualizaEstado(s, pos);
            }
            break;
        case Procurando::NODE_DATA:
            if(comecaCom("<data", s, pos) ||
                    comecaCom("</node>", s, pos, false)) {
                interpretaNoData(s, pos);
            } else {
                procurando = atualizaEstado(s, pos);
            }
            break;
        case Procurando::ARESTA:
            if(comecaCom("<edge", s, pos)) {
                interpretaAresta(s, pos);
            } else {
                procurando = atualizaEstado(s, pos);
            }
            break;
        case Procurando::ARESTA_DATA:
            if(comecaCom("<data", s, pos) ||
                    comecaCom("</edge>", s, pos, false)) {
                interpretaArestaData(s, pos);
            } else {
                procurando = atualizaEstado(s, pos);
            }
            break;
        default: // FIM
            if(valorado) {
                builder->enableValorado();
            }
            pos = s.size();
            grafo = builder->build();
            finaliza = true;
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
    size_t j = pos;
    for(size_t i = 0; i < procurar.size() && j < palavra.size(); i++, j++) {
        if(tolower(procurar[i]) != tolower(palavra[j])) {
            return false;
        }
    }
    if(atualiza) {
        pos = static_cast<long>(j);
    }
    removeEspacos(palavra, pos);
    return true;
}

void grafos::GraphMLParser::interpretaGrafo(const string &s, long &pos) {
    string id;
    GrafoTipo tipo = GrafoTipo::NORMAL;

    while(static_cast<size_t>(pos) < s.size()) {
        if(comecaCom("id=" ,s, pos)) {
            id = pegaValor(s, pos);
        } else if(comecaCom("edgedefault=", s, pos)) {
            tipo = (pegaValor(s, pos) == "directed") ? GrafoTipo::ORIENTADO :
                GrafoTipo::NORMAL;
        } else if(comecaCom("/", s, pos)) {
            return;
        } else if(comecaCom(">", s, pos)) {
            builder = new GrafoBuilder<float>(tipo, id);
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
string grafos::GraphMLParser::pegaValor(const string &s, long &pos,
                                        bool dentroDeData) {
    char para;
    string lido;

    if(dentroDeData) {
        para = '<';
    } else if (comecaCom("\"", s, pos)) {
        para = '\"';
    } else {
        para = ' ';
    }

    while(s[pos] != para) {
        lido += s[pos++];
    }
    ++pos;

    return lido;
}

void grafos::GraphMLParser::interpretaNo(const string &s, long &pos) {
    string id;

    while(static_cast<size_t>(pos) < s.size()) {
        if(comecaCom("id=" ,s, pos)) {
            id = pegaValor(s, pos);
        } else if(comecaCom("/", s, pos) && comecaCom(">", s, pos)) {
            no = new No<float>(id);
        } else if(comecaCom(">", s, pos)) {
            no = new No<float>(id);
            procurando = Procurando::NODE_DATA;
            return;
        }
    }
}

// atualiza o atributo da classe procurando, quando a previsão do loop do
// scanner errou a progressão entre as leituras.
grafos::GraphMLParser::Procurando grafos::GraphMLParser::atualizaEstado(
    const string &s, long &pos) {
    if(comecaCom("<node", s, pos, false)) {
        return Procurando::NODE;
    } else if(comecaCom("<data", s, pos, false)) {
        return (procurando == Procurando::ARESTA) ? Procurando::ARESTA_DATA :
            Procurando::NODE_DATA;
    } else if(comecaCom("<edge", s, pos, false)) {
        return Procurando::ARESTA;
    } else if(comecaCom("</edge>", s, pos, false)) {
        ++pos;
        return Procurando::ARESTA;
    } else if(comecaCom("</data>", s, pos)) {
        ++pos;
        return procurando;
    } else if(comecaCom("</node>", s, pos, false)) {
        ++pos;
        return Procurando::NODE;
    } else {
        return Procurando::FIM;
    }
}

void grafos::GraphMLParser::interpretaNoData(const string &s, long &pos) {
    enum class NodeData { DATA, KEY };
    NodeData d = NodeData::DATA;
    string key;
    while(static_cast<size_t>(pos) < s.size()) {
        if(d == NodeData::DATA && comecaCom("key=", s, pos)) {
            d = NodeData::KEY;
        } else if(d == NodeData::KEY) {
            key = pegaValor(s, pos);
            comecaCom(">", s, pos);
            d = NodeData::DATA;
            if (key == "label") {
                no->setVerticeLabel(pegaValor(s, pos, true));
            } else if (key == "size") {
                no->setSize(std::stof(pegaValor(s, pos, true)));
            } else if (key == "r") {
                no->setR(std::stof(pegaValor(s, pos, true)));
            } else if (key == "g") {
                no->setG(std::stof(pegaValor(s, pos, true)));
            } else if (key == "b") {
                no->setB(std::stof(pegaValor(s, pos, true)));
            } else if (key == "x") {
                no->setX(std::stof(pegaValor(s, pos, true)));
            } else if (key == "y") {
                no->setY(std::stof(pegaValor(s, pos, true)));
            } else {
                no->adicionaData(key, pegaValor(s, pos, true));
            }
        } else if(comecaCom("/data>", s, pos)) {
            d = NodeData::DATA;
        } else if(comecaCom("</node>", s, pos)) {
            d = NodeData::DATA;
            procurando = Procurando::NODE;
            builder->adicionaVertice(no);
            no = nullptr;
            return;
        }
    }
}

void grafos::GraphMLParser::interpretaAresta(const string &s, long &pos) {
    string id, source, target;
    while(static_cast<size_t>(pos) < s.size()) {
        if(comecaCom("id=", s, pos)) {
            id = pegaValor(s, pos);
        } else if(comecaCom("source=", s, pos)) {
            source = pegaValor(s, pos);
        } else if(comecaCom("target=", s, pos)){
            target = pegaValor(s, pos);
        } else if(comecaCom("/", s, pos) && comecaCom(">", s, pos)) {
            adicionaAresta(builder, id, source, target);
        } else if(comecaCom(">", s, pos)) {
            adicionaAresta(builder, id, source, target);
            procurando = Procurando::ARESTA_DATA;
        }
    }
}



void grafos::GraphMLParser::interpretaArestaData(const string &s, long &pos) {
    enum class ArestaData { DATA, KEY };
    ArestaData d = ArestaData::DATA;
    string key;
    while(static_cast<size_t>(pos) < s.size()) {
        if(d == ArestaData::DATA && comecaCom("key=", s, pos)) {
            d = ArestaData::KEY;
        } else if(d == ArestaData::KEY) {
            key = pegaValor(s, pos);
            d = ArestaData::DATA;
            comecaCom(">", s, pos);
            if (key == "edgelabel") {
                no->setArestaLabel(pegaValor(s, pos, true));
            } else if (key == "weight") {
                valorado = true;
                no->setValorAresta(std::stof(pegaValor(s, pos, true)));
            } else {
                no->adicionaArestaData(key, pegaValor(s, pos, true));
            }
        } else if(comecaCom("/data>", s, pos)) {
            d = ArestaData::DATA;
        } else if(comecaCom("</edge>", s, pos)) {
            d = ArestaData::DATA;
            procurando = Procurando::ARESTA;
            no = nullptr;
            return;
        }
    }
}

grafos::GraphMLParser::~GraphMLParser() {
    delete builder;
    if(!count) {
        delete grafo;
    }
}

void grafos::GraphMLParser::montaAresta(const string &id,
        const string &source, const string &target) {

}

grafos::Grafo<float> *grafos::GraphMLParser::getGrafo() {
    if(grafo != nullptr) {
        ++count;
    }
    return grafo;
}

void grafos::GraphMLParser::adicionaAresta(grafos::GrafoBuilder<float> *builder,
        const string &id, const string &source, const string &target) {
    no = new No<float>(builder->getNo(target));
    builder->adicionaAresta(id, source, no);
}

