cmake_minimum_required(VERSION 3.10)
project(trabalhoGrafos)

set(CMAKE_CXX_STANDARD 11)

include_directories(trabalhoGrafos)

add_executable(trabalhoGrafos
        trabalhoGrafos/teste.cpp
        trabalhoGrafos/gmlparser.cpp
        trabalhoGrafos/gmlparser.h
        trabalhoGrafos/grafo.cpp
        trabalhoGrafos/grafo.h
        trabalhoGrafos/grafobuilder.cpp
        trabalhoGrafos/grafobuilder.h
        trabalhoGrafos/grafotipo.h
        trabalhoGrafos/graphmlparser.cpp
        trabalhoGrafos/graphmlparser.h
        trabalhoGrafos/no.cpp
        trabalhoGrafos/geradorgraphml.cpp
        trabalhoGrafos/geradorgraphml.h
        trabalhoGrafos/centroid.h
        trabalhoGrafos/centroid.cpp
        trabalhoGrafos/kmeans.h
        trabalhoGrafos/kmeans.cpp
        trabalhoGrafos/cluster.h
        trabalhoGrafos/cluster.cpp
        trabalhoGrafos/kmeansmodo.h
        trabalhoGrafos/no.h)
