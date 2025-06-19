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
	//ainda pensando como fazer a movimentacao do chefao, a principio ele seria lento
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
	Inimigo::salvarDataBuffer();
	if (buffer) {
		*buffer << forca << endl; 
	}
	ofstream arquivoChefao;
	arquivoChefao.open("arquivo_chefao.txt");
	arquivoChefao << buffer;
	arquivoChefao.close();
}
void Chefao::tratarColisaoComJogador(Jogador* jogador, int tipoColisao) {
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


