#include "lista_entidades.h"
#include <iostream>

ListaEntidades::ListaEntidades() : LEs() {}

ListaEntidades::~ListaEntidades() {
   
}

void ListaEntidades::incluir(Entidade* PE) { 
    LEs.incluir(PE);
}

void ListaEntidades::percorrer() {
    std::cout << "Lista de Entidades:" << std::endl;
    LEs.percorrer();
}