#include "inim_medio.h"
#include "jogador.h"
#include "inimigo.h"
#include <iostream>

InimMedio::InimMedio() : Inimigo(), tamanho(50), vida(200), ataque(20) {
	nivel_maldade = 2;
}
InimMedio::~InimMedio() {
	tamanho = -1;
}
void InimMedio::danificar(Jogador* p) {
	if (p) {
		p->setVida(p->getVida() - ataque); 
		std::cout << "Jogador danificado! Vida restante: " << p->getVida() << std::endl;
	}
}
void InimMedio::executar() {
	//a fazer
}
void InimMedio::mover() {
	//Ideia de movimento do Inimigo medio: Apenas surgir em plataformas e atacar o jogador, elee seria responsavel
	// por atacar o jogador quando estiver proximo, sem se mover muito, apenas em um range maximo e seria o responsavel pelo projetil.
}
int InimMedio::getVida() const {
	return vida;
}
int InimMedio::getAtaque() {
	return ataque;
}
void InimMedio::setVida(int v) {
	vida = v;
}
void InimMedio::setAtaque(int a) {
	ataque = a;
}