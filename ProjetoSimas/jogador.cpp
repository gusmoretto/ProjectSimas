#include "jogador.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Jogador::Jogador(): Personagem() {
	vida = 100;
	ataque = 10;
	pontos = 0;
}
Jogador::~Jogador() {
	vida = -1;
	ataque = -1;
}
int Jogador::getVida() const {
	return vida;
}
int Jogador::getAtaque() const {
	return ataque;
}
void Jogador::setVida(int novaVida) {
	vida = novaVida;
}
void Jogador::setAtaque(int novoAtaque) {
	ataque = novoAtaque;
}
void Jogador::executar() {
	Personagem::carregarTextura("pekka.png");
}



