#include <iostream>
#include <SFML/Graphics.hpp>
#include "entidade.h"

Entidade::Entidade() : x(0), y(0), buffer(&std::cout) { // Initialize buffer with std::cout
    // Inicializa��o padr�o
}

Entidade::~Entidade() {
    std::cout << "Destrutor de Entidade chamado." << std::endl;
}
