#include "aranha.h"
#include "jogador.h"
#include "inimigo.h"
#include <iostream>

Aranha::Aranha(): Inimigo(), direcaoX(1.f) {
    nivel_maldade = 1;
	vida = 100; 
    ataque = 10;
    num_vidas = 1;
}

Aranha::~Aranha() {
}

void Aranha::danificar(Jogador* p) {
    if (p) {
        p->setVida(p->getVida() - ataque); 
    }
}
void Aranha::virarDirecao() {
    direcaoX = -direcaoX;
}

void Aranha::executar() {
    setId(3);
    retangulo.setSize(sf::Vector2f(64.f, 64.f));
    if (!textura.loadFromFile("aranha.png")) {
        std::cerr << "Erro fatal: Nao foi possivel carregar a textura aranha.png" << std::endl;
        return;
    }
	retangulo.setTexture(&textura);
}

void Aranha::mover() {
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
int Aranha::getVida() const {
	return vida;
}
int Aranha::getAtaque() const {
	return ataque;
}
void Aranha::setVida(int v) {
	vida = v;
}
void Aranha::setAtaque(int a) {
	ataque = a;
}
void Aranha::desenhar() {
    if (pGG) {
        pGG->desenha(retangulo);
    }
}
void Aranha::setId(int novoId) {
    id = novoId;
}
int Aranha::getId() const {
    return id;
}
void Aranha::setVelocidade(float nvVelocidade) {
	velocidade = nvVelocidade;
}
float Aranha::getVelocidade() {
	return velocidade;
}
void Aranha::tratarColisaoComJogador(Jogador* jogador, int tipoColisao) {
    if (tipoColisao == 1) {
        if (this->getVida() > 0) {
            jogador->setPontos(jogador->getPontos() + 10); 
        }
        this->setVida(0);
        jogador->setVelocidadeVertical(-400.f);
    }
    else {
        this->danificar(jogador);
        sf::Vector2f pos = jogador->getRetangulo().getPosition();
        pos.x += (tipoColisao == 2) ? -10.f : 10.f;
        jogador->setPosicao(pos.x, pos.y);
    }
}
void Aranha::setVelocidadeVertical(float nvVelocidadeVertical) {
    velocidadeVertical = nvVelocidadeVertical;
}
float Aranha::getVelocidadeVertical() const {
    return velocidadeVertical;
}
void Aranha::setNoChao(bool NC) {
    noChao = NC;
}
bool Aranha::getNochao() {
    return noChao;
}
void Aranha::salvar(std::ostream& os) {
    // Escreve todos os dados da aranha
    os << gravidade << " " << forcaMitico << " " << forcaMiticaAtiva << " "
        << num_vidas << " " << getVida() << " " << velocidade << " " << noChao << " " << ataque << " "
        << nivel_maldade << " " << direcaoX << " " << getPosicao().x << " " << getPosicao().y << std::endl;
}

