#include "chefao.h"
#include "jogador.h"
#include "inimigo.h"
#include <iostream>

Chefao::Chefao() : Inimigo(), forca(10){
	nivel_maldade = 3;
	vida = 500; 
	ataque = 50; 
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
		std::cout << "Erro ao carregar Chefao.png" << std::endl;
	}
	retangulo.setTexture(&textura);
}
void Chefao::mover() {
	
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
void Chefao::salvar() {
	if (auto* p_sstream = dynamic_cast<std::ostringstream*>(buffer)) {
		p_sstream->str("");
		p_sstream->clear();
	}
	else {
		return;
	}

	Inimigo::salvarDataBuffer();
	*buffer << forca << std::endl;

	std::ofstream arquivoChefao("arquivo_chefao.txt", std::ios::app);
	if (arquivoChefao.is_open()) {
		arquivoChefao << buffer;
		arquivoChefao.close();
	}
}
void Chefao::tratarColisaoComJogador(Jogador* jogador, int tipoColisao) {
	if (tipoColisao == 1) {
		this->setVida(getVida()-10);
		jogador->setVelocidadeVertical(-400.f);
	}
	else {
		this->danificar(jogador);
		sf::Vector2f pos = jogador->getRetangulo().getPosition();
		pos.x += (tipoColisao == 2) ? -10.f : 10.f;
		jogador->setPosicao(pos.x, pos.y);
	}
}


