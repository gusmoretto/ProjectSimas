#pragma once

#include "lista.h" 
#include "entidade.h" 

class ListaEntidades {
private:
    Lista<Entidade> LEs; 

public:
    ListaEntidades();
    ~ListaEntidades();

    void incluir(Entidade* PE); 
    void percorrer();
};
