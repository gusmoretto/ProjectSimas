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
	olhandoDireita = true; 
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
    if (cont_jogador)
        setId(1);
    else
        setId(2);
	retangulo.setSize(sf::Vector2f(128.f, 128.f));
    retangulo.setOrigin(64.f, 64.f);
	retangulo.setPosition(64.f, 64.f);
	if (id_jogador == 0) {
        if (!textura.loadFromFile("jogador2.png")) {
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            movimento.x += velocidade;
            if (!olhandoDireita) {
                retangulo.setScale(1.f, 1.f); // normal
                olhandoDireita = true;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            movimento.x -= velocidade;
            if (olhandoDireita) {
                retangulo.setScale(-1.f, 1.f); // espelha
                olhandoDireita = false;
            }
        }
    }
    else if (id_jogador == 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movimento.x += velocidade;
            if (!olhandoDireita) {
                retangulo.setScale(1.f, 1.f);
                olhandoDireita = true;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movimento.x -= velocidade;
            if (olhandoDireita) {
                retangulo.setScale(-1.f, 1.f);
                olhandoDireita = false;
            }
        }
    }

    // Pulo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && noChao) {
        velocidadeVertical = impulsoPulo;
        noChao = false;
    }

    // Gravidade
    velocidadeVertical += gravidade * 0.016f;
    movimento.y += velocidadeVertical * 0.016f;

    retangulo.move(movimento);

    // Limites da janela
    sf::Vector2f pos = retangulo.getPosition();
    sf::Vector2f size = retangulo.getSize();

    // Limite chão
    if (pos.y >= 620.f) {
        pos.y = 620.f;
        velocidadeVertical = 0.f;
        noChao = true;
    }
    // Limite topo
    if (pos.y < 0.f) {
        pos.y = 0.f;
        velocidadeVertical = 0.f;
    }
    // Limite esquerda
    if (pos.x < 0.f) {
        pos.x = 0.f;
    }
    
    if (pos.x + size.x > 3900.f) {
        pos.x = 3900.f - size.x;
    }

    retangulo.setPosition(pos);
}
int Jogador::getIdJogador() const {
	return id_jogador;
}
void Jogador::desenhar() {
	if (pGG) {
		pGG->desenha(retangulo);
	}
}
void Jogador::setId(int novoId) {
    id = novoId;
}
int Jogador::getId() const {
    return id;
}
void Jogador::setVelocidade(float nvVelocidade) {
	velocidade = nvVelocidade;
}
float Jogador::getVelocidade() {
	return velocidade;
}



