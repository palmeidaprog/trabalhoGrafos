#include "geradorgraphml.h"

grafos::GeradorGraphML::GeradorGraphML(const string &nomeArquivo,
                                       No<float> **lista, int tamanho,
                                       const vector<No<float>*> vertices,
                                       GrafoTipo tipo)
    : nomeArquivo(nomeArquivo), lista(lista), tamanho(vertices.size()),
      vertices(vertices), tipo(tipo) {
    salva();
}

grafos::GeradorGraphML::GeradorGraphML(const string &nomeArquivo,
        Grafo<float> *grafo) : nomeArquivo(nomeArquivo),
    lista(grafo->getListaAdjacente()), tamanho(vertices.size()),
          vertices(grafo->getVertices()) {
    tipo = grafo->getTipo();
    salva();
}

void grafos::GeradorGraphML::salva() {
    ofstream arq(nomeArquivo);

    arq << "<?xml version=\"1.0\" encoding=\"UTF-8\"?><graphml xmlns=" <<
           "\"http://graphml.graphdrawing.org/xmlns\">" << endl;
    arq << "<key attr.name=\"label\" attr.type=\"string\" for=\"node\"" <<
           " id=\"label\"/>" << endl;
    arq << "<key attr.name=\"Edge Label\" attr.type=\"string\" " <<
           "for=\"edge\" id=\"edgelabel\"/>" << endl;
    arq << "<key attr.name=\"weight\" attr.type=\"double\" " <<
           "for=\"edge\" id=\"weight\"/>" << endl;
    arq << "<key attr.name=\"r\" attr.type=\"int\" for=\"node\" " <<
           "id=\"r\"/>" << endl <<
           "<key attr.name=\"g\" attr.type=\"int\" for=\"node\" " <<
           "id=\"g\"/>" << endl << "<key attr.name=\"b\" " <<
           "attr.type=\"int\" for=\"node\" id=\"b\"/>" << endl <<
           "<key attr.name=\"x\" attr.type=\"float\" for=\"node\" " <<
           "id=\"x\"/>" << endl <<
           "<key attr.name=\"y\" attr.type=\"float\" for=\"node\" " <<
           "id=\"y\"/>" << endl <<
           "<key attr.name=\"size\" attr.type=\"float\" for=\"node\"" <<
           " id=\"size\"/>" << endl;

    arq << "<graph edgedefault=\"";
    if(tipo == GrafoTipo::VALORADO_ORIENTADO
            || tipo == GrafoTipo::ORIENTADO) {
        arq << "directed";
    } else {
        arq << "undirected";
    }

    arq << "\">" << endl;

    for(No<float> *i : vertices) {
        arq << "<node id=\"" << i->getVerticeId() << "\">" << endl;
        if(i->getVerticeLabel() != "") {
            arq << "<data key=\"label\">" << i->getVerticeLabel() <<
                   "</data>" << endl;
        }

        arq << "<data key=\"size\">" << i->getSize() << "</data>" << endl;
        arq << "<data key=\"r\">" << i->getR() << "</data>" << endl;
        arq << "<data key=\"g\">" << i->getG() << "</data>" << endl;
        arq << "<data key=\"b\">" << i->getB() << "</data>" << endl;
        arq << "<data key=\"x\">" << i->getX() << "</data>" << endl;
        arq << "<data key=\"y\">" << i->getY() << "</data>" << endl;
        arq << "</node>" << endl;
    }

    for(int i = 0; i < vertices.size(); i++) {
        No<float> *no = lista[i];
        while(no != nullptr) {
            arq << "<edge id=\"" << no->getArestaId() << "\" source=\"" <<
                vertices.at(i)->getVerticeId() <<"\" target=\"" <<
                   no->getVerticeId() << "\">" << endl;
            if(no->getArestaLabel() != "") {
                arq << "<data key=\"edgelabel\">" << no->getArestaLabel()
                    << "</data>" << endl;
            }
            if(tipo == GrafoTipo::VALORADO_ORIENTADO
                    || tipo == GrafoTipo::ORIENTADO) {
                arq << "<data key=\"weight\">" << no->getValorAresta()
                    << "</data>" << endl;
            }
            arq << "</edge>" << endl;
            no = no->getProx();
        }
    }

    arq << "</graph>" << endl << "</graphml>" << endl;
    arq.close();
}

