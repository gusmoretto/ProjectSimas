#include "jogador.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "personagem.h"

int Jogador::cont_jogador = 0;

Jogador::Jogador(): Personagem() {
	vida = 100;
	ataque = 10;
	pontos = 0;
	id_jogador = cont_jogador++;
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
void Jogador::mover() {
	sf::Vector2f movimento((float)x, (float)y);
	if (id_jogador == 1) {
		// Jogador 1: setas
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) movimento.x += velocidade;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  movimento.x -= velocidade;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    movimento.y -= velocidade;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  movimento.y += velocidade;
	}
	else if (id_jogador == 0) {
		// Jogador 2: WASD
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movimento.x += velocidade;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movimento.x -= velocidade;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movimento.y -= velocidade;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movimento.y += velocidade;
	}

	retangulo.move(movimento);

}
int Jogador::getIdJogador() const {
	return id_jogador;
}



