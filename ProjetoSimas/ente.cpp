#include <iostream>
#include "ente.h"

Gerenciadores::GerenciadorGrafico* Ente::pGG = nullptr;

Ente::Ente() { id++;  }

Ente::~Ente() {
	std::cout << "Destrutor de Ente chamado." << std::endl;
}
void Ente::executar() {
	std::cout << "Executando Ente com ID: " << id << std::endl;
}