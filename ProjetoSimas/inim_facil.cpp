#include "inim_facil.h"
#include "jogador.h"
#include "inimigo.h"
#include <iostream>

InimFacil::InimFacil(): Inimigo(), direcaoX(1.f) {
    nivel_maldade = 1;
	vida = 100; 
    ataque = 10;
}

InimFacil::~InimFacil() {
}

void InimFacil::danificar(Jogador* p) {
    if (p) {
        p->setVida(p->getVida() - ataque); // Example: Reduce player's health by 10
        
    }
}
void InimFacil::virarDirecao() {
    direcaoX = -direcaoX;
}

void InimFacil::executar() {
    setId(3);
    retangulo.setSize(sf::Vector2f(64.f, 64.f));
    retangulo.setOrigin(0.f, 0.f);
    retangulo.setPosition(x, y);
   
    if (!textura.loadFromFile("aranha.png")) {
        std::cout << "Erro ao carregar jogador1.png" << std::endl;
    }
    retangulo.setTexture(&textura);  
}

void InimFacil::mover() {
    sf::Vector2f posicao = getPosicao(); 
    posicao.x += direcaoX * (velocidade - 0.50);


    if (posicao.x <= 0) { 
        posicao.x = 0; 
        virarDirecao();
    }
    else if (posicao.x + retangulo.getSize().x >= 3840) { 
        posicao.x = 3840 - retangulo.getSize().x; 
        virarDirecao();
    }

    posicao.y += aplicarGravidade(0.016f); 

    if (posicao.y + retangulo.getSize().y >= 670.f) {
        posicao.y = 670.f - retangulo.getSize().y; 
    }
    retangulo.setPosition(posicao); 
}
int InimFacil::getVida() const {
	return vida;
}
int InimFacil::getAtaque() const {
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
void InimFacil::setId(int novoId) {
    id = novoId;
}
int InimFacil::getId() const {
    return id;
}
void InimFacil::setVelocidade(float nvVelocidade) {
	velocidade = nvVelocidade;
}
float InimFacil::getVelocidade() {
	return velocidade;
}
void InimFacil::tratarColisaoComJogador(Jogador* jogador, int tipoColisao) {
    // tipoColisao: 1 = por cima, 2/3 = laterais, 4 = por baixo (ajuste conforme seu verificarColisao)
    if (tipoColisao == 1) { // Por cima
        // Elimina o inimigo (pode ser delete this, ou sinalizar para o gerenciador remover)
        this->setVida(0); // ou outro mecanismo de remoção
        // Opcional: jogador pode quicar/pular ao eliminar o inimigo
        jogador->setVelocidadeVertical(-400.f); // impulso de pulo, ajuste conforme seu jogo
    }
    else {
        // Dano e empurra pouco o jogador
        this->danificar(jogador);
        sf::Vector2f pos = jogador->getRetangulo().getPosition();
        pos.x += (tipoColisao == 2) ? -10.f : 10.f; // empurra para o lado oposto
        jogador->setPosicao(pos.x, pos.y);
    }
}
void InimFacil::setVelocidadeVertical(float nvVelocidadeVertical) {
    velocidadeVertical = nvVelocidadeVertical;
}
float InimFacil::getVelocidadeVertical() const {
    return velocidadeVertical;
}
void InimFacil::setNoChao(bool NC) {
    noChao = NC;
}
bool InimFacil::getNochao() {
    return noChao;
}

