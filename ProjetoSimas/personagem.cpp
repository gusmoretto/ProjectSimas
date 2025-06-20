#include <iostream>
#include "personagem.h"
#include "entidade.h"

Personagem::Personagem() : Entidade(), num_vidas(1), vida(0), noChao(true), ataque(0) { 
	velocidade = 1.7f; 
}
Personagem::~Personagem() {
	std::cout << "Destrutor de Personagem chamado." << std::endl;
}
void Personagem::executar() {
	std::cout << "Executando Personagem com " << num_vidas << " vidas." << std::endl;
}
void Personagem::salvarDataBuffer() {
	Entidade::salvarDataBuffer();
	if (buffer)
		buffer << num_vidas << vida << velocidade << noChao << ataque;
}
