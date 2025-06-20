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
        std::cout << "Erro ao carregar jogador1.png" << std::endl;
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
void Aranha::salvar() {
    if (auto* p_sstream = dynamic_cast<std::ostringstream*>(buffer)) {
        p_sstream->str("");
        p_sstream->clear();
    }
    else {
        return; 
    }

    Inimigo::salvarDataBuffer();
    *buffer << direcaoX << std::endl;

    std::ofstream arquivoAranha("arquivo_aranha.txt", std::ios::app);
    if (arquivoAranha.is_open()) {
        arquivoAranha << buffer;
        arquivoAranha.close();
    }
}

