#include "chefao.h"
#include "jogador.h"
#include "inimigo.h"
#include <iostream>

Chefao::Chefao() : Inimigo(), forca(10){
	nivel_maldade = 3;
	vida = 500; 
	ataque = 30; 
}
Chefao::~Chefao() {
	forca = -1;
}
void Chefao::danificar(Jogador* p) {
	if (p) {
		p->setVida(p->getVida() - ataque);
		std::cout << "Jogador danificado! Vida restante: " << p->getVida() << std::endl;
	}
}
void Chefao::executar() {
    setId(5);
    retangulo.setSize(sf::Vector2f(128.f, 128.f));
    if (!textura.loadFromFile("chefao.png")) {
        std::cerr << "Erro fatal: Nao foi possivel carregar a textura chefao.png" << std::endl;
        return;
    }
    retangulo.setTexture(&textura);

    posicaoInicialX = retangulo.getPosition().x;
    float bloco = retangulo.getSize().x; // tamanho de um bloco
    limiteEsquerda = posicaoInicialX - bloco;
    limiteDireita  = posicaoInicialX + bloco;
}
void Chefao::mover() {
    sf::Vector2f posicao = getPosicao();
    static float direcaoX = 1.f;

    sf::Vector2f proximaPos = posicao;
    proximaPos.x += direcaoX * (velocidade - 0.50);
    if (proximaPos.x < limiteEsquerda || proximaPos.x + retangulo.getSize().x > limiteDireita + retangulo.getSize().x) {
        direcaoX = -direcaoX;
    } else {
        posicao.x = proximaPos.x;
    }

    posicao.y += aplicarGravidade(0.016f);
    if (posicao.y + retangulo.getSize().y >= 670.f) {
        posicao.y = 670.f - retangulo.getSize().y;
    }

    retangulo.setPosition(posicao);
}
short int Chefao::getForca() const {
	return forca;
}
int Chefao::getVida() const {
	return vida;
}
int Chefao::getAtaque() const {
	return ataque;
}
void Chefao::setForca(short int f) {
	forca = f;
}
void Chefao::setVida(int v) {
	vida = v;
}
void Chefao::setAtaque(int a) {
	ataque = a;
}
void Chefao::setId(int novoId) {
	id = novoId;
}
int Chefao::getId() const {
	return id;
}
void Chefao::setVelocidade(float nvVelocidade) {
	velocidade = nvVelocidade;
}
float Chefao::getVelocidade() {
	return velocidade;
}
void Chefao::desenhar() {
	if (pGG) {
		pGG->desenha(retangulo);
	}
}
void Chefao::setVelocidadeVertical(float nvVelocidadeVertical) {
	velocidadeVertical = nvVelocidadeVertical;
}
float Chefao::getVelocidadeVertical() const {
	return velocidadeVertical;
}
void Chefao::setNoChao(bool NC) {
	noChao = NC;
}
bool Chefao::getNochao() {
	return noChao;
}
void Chefao::salvar(std::ostream& os) {
    os << gravidade << " " << forcaMitico << " " << forcaMiticaAtiva << " "
        << num_vidas << " " << vida << " " << velocidade << " " << noChao << " " << ataque << " "
        << nivel_maldade << " " << forca << " " << posicaoInicialX << " " << limiteEsquerda << " "
        << limiteDireita << " " << getPosicao().x << " " << getPosicao().y << std::endl;
}
void Chefao::tratarColisaoComJogador(Jogador* jogador, int tipoColisao) {
    if (!jogador) return;

    float impulsoRepulsaoVertical = 450.f;
    float impulsoRepulsaoHorizontal = 600.f;
    float impulsoVerticalCurto = -200.f;

    sf::FloatRect areaJogador = jogador->getRetangulo().getGlobalBounds();
    sf::FloatRect areaChefao = this->getRetangulo().getGlobalBounds();

    switch (tipoColisao) {
    case 1: 
        if (getVida() > 0) {
            jogador->setNoChao(false);
            jogador->setPosicao(areaJogador.left, areaChefao.top - areaJogador.height);
            jogador->setVelocidadeVertical(-impulsoRepulsaoVertical);
            if (getVida() == 250.f) {
                jogador->setPontos(jogador->getPontos() + 50);
            }
            setVida(getVida() - 250.f);
        }
        break;
    case 4: 
        jogador->setPosicao(areaJogador.left, areaChefao.top + areaChefao.height);
        jogador->setVelocidadeVertical(impulsoRepulsaoVertical);
        break;
    case 2: 
        jogador->setPosicao(areaChefao.left - areaJogador.width, areaJogador.top);
        jogador->setVelocidadeHorizontal(-impulsoRepulsaoHorizontal);
        jogador->setVelocidadeVertical(impulsoVerticalCurto);
        this->danificar(jogador);
        jogador->setNoChao(false);
        break;
    case 3: 
        jogador->setPosicao(areaChefao.left + areaChefao.width, areaJogador.top);
        jogador->setVelocidadeHorizontal(impulsoRepulsaoHorizontal);
        jogador->setVelocidadeVertical(impulsoVerticalCurto);
        this->danificar(jogador);
        jogador->setNoChao(false);
        break;
    default:
        this->danificar(jogador);
        break;
    }
}


