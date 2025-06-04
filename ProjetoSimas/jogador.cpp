#include "jogador.h"
#include <iostream>
#include "personagem.h"

int Jogador::cont_jogador = 0;

Jogador::Jogador(): Personagem(), impulsoPulo(-400.f) {
	vida = 100;
	ataque = 10;
	pontos = 0;
	id_jogador = cont_jogador++;
	noChao = true;
    velocidadeVertical = 0.f;
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
	retangulo.setSize(sf::Vector2f(100.f, 100.f));
	retangulo.setPosition(0,0);
	if (id_jogador == 0) {
        if (!textura.loadFromFile("jogador1.png")) {
            std::cout << "Erro ao carregar jogador1.png" << std::endl;
        }
	}
	else {
		textura.loadFromFile("jogador1.png");
	}
    retangulo.setTexture(&textura);
}
void Jogador::mover() {
    
    sf::Vector2f movimento(0.f, 0.f);

    // Movimento horizontal
    if (id_jogador == 1) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) movimento.x += velocidade;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  movimento.x -= velocidade;
    }
    else if (id_jogador == 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movimento.x += velocidade;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movimento.x -= velocidade;
    }

    // Pulo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && noChao) {
        velocidadeVertical = impulsoPulo;
        noChao = false;
    }

    // Gravidade
    velocidadeVertical += gravidade * 0.016f; // deltaTime ~16ms
    movimento.y += velocidadeVertical * 0.016f;

    retangulo.move(movimento);

    // Checagem simples de chão (exemplo: y >= 600)
    if (retangulo.getPosition().y >= 600.f) {
        sf::Vector2f pos = retangulo.getPosition();
        pos.y = 600.f;
        retangulo.setPosition(pos);
        velocidadeVertical = 0.f;
        noChao = true;
    }
}

int Jogador::getIdJogador() const {
	return id_jogador;
}



