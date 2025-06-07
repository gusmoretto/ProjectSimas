#include "chefao.h"
#include "jogador.h"
#include "inimigo.h"
#include <iostream>

Chefao::Chefao() : Inimigo(), forca(10), vida(500), ataque(50) {
	nivel_maldade = 3;
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
	//a fazer
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

