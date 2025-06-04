#include "obstaculo.h"
#include <iostream>
#include "entidade.h"

Obstaculo::Obstaculo() : Entidade(), danoso(false) {
	// a contruir o retangulo com tamanho e posicao
}
Obstaculo::~Obstaculo() {
	std::cout << "Destrutor de Obstaculo chamado." << std::endl;
}
void Obstaculo::executar() {
	std::cout << "Executando Obstaculo." << std::endl;
}
void Obstaculo::obstacular() {
	std::cout << "Obstáculo ativo." << std::endl;
}


