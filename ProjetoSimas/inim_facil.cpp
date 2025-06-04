#include "inim_facil.h"
#include "jogador.h"
#include "inimigo.h"
#include <iostream>

InimFacil::InimFacil(): Inimigo(), raio(50.f), direcaoX(1.f) , vida(100), ataque(10){
    nivel_maldade = 1;
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
    retangulo.setSize(sf::Vector2f(100.f, 100.f));
    retangulo.setPosition(0, 0);
   
    if (!textura.loadFromFile("inimigo.png")) {
        std::cout << "Erro ao carregar jogador1.png" << std::endl;
    }
    retangulo.setTexture(&textura);  
}

void InimFacil::mover() {
    // readaptar pos add do gerenciador grafico
    sf::Vector2f posicao = getPosicao();
    posicao.x += direcaoX * (velocidade-0.15);

    if (posicao.x <= 0 || posicao.x + retangulo.getSize().x >= 1000) {
        direcaoX = -direcaoX;
        posicao.x += direcaoX * velocidade; 
    }
    posicao.y+=aplicarGravidade(0.016f);
    retangulo.setPosition(posicao);
    if (retangulo.getPosition().y >= 600.f) {
        sf::Vector2f pos = retangulo.getPosition();
        pos.y = 600.f;
        retangulo.setPosition(pos);
    }
}
int InimFacil::getVida() const {
	return vida;
}
int InimFacil::getAtaque() {
	return ataque;
}
void InimFacil::setVida(int v) {
	vida = v;
}
void InimFacil::setAtaque(int a) {
	ataque = a;
}
void InimFacil::desenhar() {
    if (pGG) {
        pGG->desenha(retangulo);
    }
}
