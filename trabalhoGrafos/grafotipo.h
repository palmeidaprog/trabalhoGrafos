#ifndef GRAFOTIPO_H
#define GRAFOTIPO_H

namespace grafos {
enum class GrafoTipo {
    NORMAL, // Sem direcao e sem valor nas arestas
    DIRECIONADO, // Sem valor nas arestas
    VALORADO, // sem direcao
    VALORADO_DIRECIONADO
};
}


#endif // GRAFOTIPO_H
