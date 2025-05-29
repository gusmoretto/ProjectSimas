#include "inim_facil.h"
#include "jogador.h"
#include "inimigo.h"
#include <iostream>

InimFacil::InimFacil(): Inimigo(), raio(50.f), direcaoX(1.f) {
}

InimFacil::~InimFacil() {
    raio = -1;
}

void InimFacil::danificar(Jogador* p) {
    if (p) {
        p->setVida(p->getVida() - ataque); // Example: Reduce player's health by 10
        std::cout << "Jogador danificado! Vida restante: " << p->getVida() << std::endl;
    }
}

void InimFacil::executar() {
	Personagem::carregarTextura("inimigo.png");
}

void InimFacil::mover() {
    sf::Vector2f posicao = getPosicao();
    posicao.x += direcaoX * velocidade;

    if (posicao.x <= 0 || posicao.x + retangulo.getSize().x >= 1000) {
        direcaoX = -direcaoX;
        posicao.x += direcaoX * velocidade; 
    }

    retangulo.setPosition(posicao);
}
