#include <iostream>
#include <SFML/Graphics.hpp>
#include "entidade.h"

Entidade::Entidade() : x(0), y(0), buffer(&std::cout) { // Initialize buffer with std::cout
    // Inicialização padrão
}

Entidade::~Entidade() {
    std::cout << "Destrutor de Entidade chamado." << std::endl;
}
