#include <iostream>
#include "entidade.h"

Entidade::Entidade() : x(0), y(0), buffer(&std::cout)   {
    gravidade = 980.f;
}

Entidade::~Entidade() {
    std::cout << "Destrutor de Entidade chamado." << std::endl;
}
float Entidade::aplicarGravidade(float deltaTime) {
    return gravidade * deltaTime;
}
