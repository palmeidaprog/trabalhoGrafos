cmake_minimum_required(VERSION 3.10)
project(trabalhoGrafos)

set(CMAKE_CXX_STANDARD 11)

include_directories(trabalhoGrafos)

add_executable(trabalhoGrafos
        trabalhoGrafos/gmlparser.cpp
        trabalhoGrafos/gmlparser.h
        trabalhoGrafos/grafo.cpp
        trabalhoGrafos/grafo.h
        trabalhoGrafos/grafotipo.h
        trabalhoGrafos/graphmlparser.cpp
        trabalhoGrafos/graphmlparser.h
        trabalhoGrafos/main.cpp
        trabalhoGrafos/maincontroller.cpp
        trabalhoGrafos/maincontroller.h
        trabalhoGrafos/no.cpp
        trabalhoGrafos/no.h)
