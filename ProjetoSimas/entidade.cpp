#include <iostream>
#include "entidade.h"

Entidade::Entidade() : x(0), y(0), buffer(&std::cout), velocidadeVertical(0.f)   {
    gravidade = 980.f;
}

Entidade::~Entidade() {
    std::cout << "Destrutor de Entidade chamado." << std::endl;
}

float Entidade::aplicarGravidade(float deltaTime, float forcaExtra) {
    const float gravidade = 980.f;
    velocidadeVertical += (gravidade + forcaExtra) * deltaTime;
    retangulo.move(0.f, velocidadeVertical * deltaTime);
	return velocidadeVertical * deltaTime;
}


