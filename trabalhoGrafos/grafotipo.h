#ifndef GRAFOTIPO_H
#define GRAFOTIPO_H

namespace grafos {
enum class GrafoTipo {
    NORMAL, // Sem orientação e sem valor nas arestas
    ORIENTADO, // Sem valor nas arestas
    VALORADO, // sem orientacao
    VALORADO_ORIENTADO
};
}


#endif // GRAFOTIPO_H
