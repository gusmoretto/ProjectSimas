#include <iostream>
#include "personagem.h"
#include "entidade.h"

Personagem::Personagem() : Entidade(), num_vidas(3) { 
	// a criar o retangulo com tamanho e posicao
	velocidade = 1.7f; 
}
Personagem::~Personagem() {
	std::cout << "Destrutor de Personagem chamado." << std::endl;
}
void Personagem::executar() {
	std::cout << "Executando Personagem com " << num_vidas << " vidas." << std::endl;
}
//void Personagem::salvarDataBuffer() {
//	std::cout << "Salvando dados do personagem com " << num_vidas << " vidas." << std::endl;
//}
