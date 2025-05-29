#include "inimigo.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int Inimigo::cont_inimigo = 0;

Inimigo::Inimigo() {
	vida = 50;
	ataque = 20;
	id_inimigo = cont_inimigo++;
}
Inimigo::~Inimigo() {
	vida = -1;
	ataque = -1;
}	
int Inimigo::getVida() const {
	return vida;
}
int Inimigo::getAtaque() const {
	return ataque;
}
void Inimigo::setVida(int vida) {
	this->vida = vida;
}
void Inimigo::setAtaque(int ataque) {
	this->ataque = ataque;
}
int Inimigo::getIdInimigo() const {
	return id_inimigo;
}



