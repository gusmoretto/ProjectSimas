#include <iostream>
#include "entidade.h"

Entidade::Entidade() : x(0), y(0), velocidadeVertical(0.f), forcaMitico(0.f){
    buffer = new std::ostringstream();
    gravidade = 980.f;
    x = retangulo.getPosition().x;
	y = retangulo.getPosition().y;
}

Entidade::~Entidade() {
    delete buffer;
    buffer = nullptr;
}

float Entidade::aplicarGravidade(float deltaTime, float forcaExtra) {
    const float gravidade = 980.f;
    velocidadeVertical += (gravidade + forcaExtra) * deltaTime;
    retangulo.move(0.f, velocidadeVertical * deltaTime);
	return velocidadeVertical * deltaTime;
}
void Entidade::salvarDataBuffer() {
    if (buffer) {
        *buffer  << gravidade << " " << forcaMitico << " " << forcaMiticaAtiva << " ";
    }
}



