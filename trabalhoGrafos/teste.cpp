//
// Created by Paulo Roberto Almeida Filho on 11/20/18.
//

#include "graphmlparser.h"
#include "grafo.h"
#include "kmeans.h"
#include "geradorgraphml.h"
#include "kmeansmodo.h"
#include <iostream>

using grafos::GraphMLParser;
using grafos::GeradorGraphML;
using grafos::Grafo;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using grafos::kmeans::Kmeans;
using grafos::kmeans::KmeansModo;

int main() {
    GraphMLParser parser("g1.graphml");
    Grafo<float> *grafo = parser.getGrafo();
    cout << "V: " << grafo->getVerticesNum() << " A: " <<
        grafo->getArestasNum() << endl;
    //grafo->gerarPesosAleatorios(1);
    Kmeans<float> *kmeans = new Kmeans<float>(5, grafo, 10, true,
            KmeansModo::DISTANCIA_EUCLIDIANA);
    cout << kmeans->toString() << endl;
    cout << "================================" << endl << endl;
    cout << grafo->getLista() << endl;
    //KmeansModo::DISTANCIA_EUCLIDIANA
    //KmeansModo::PESO_ARESTAS))
    GeradorGraphML gerador("/Users/paulo/Desktop/grafo_gerado.graphml", grafo);
    return 0;
}
