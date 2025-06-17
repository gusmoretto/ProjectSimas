#include "obstaculo.h"
#include <iostream>
#include "jogador.h"

Obstaculo::Obstaculo() : Entidade(), danoso(false) {
	gravidadeAtiva = false;
}
Obstaculo::~Obstaculo() {
	std::cout << "Destrutor de Obstaculo chamado." << std::endl;
}
void Obstaculo::executar() {
	std::cout << "Executando Obstaculo." << std::endl;
}




