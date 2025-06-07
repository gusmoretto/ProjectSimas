#include "projetil.h"
#include <iostream>

Projetil::Projetil(): raio(10){ 
	//a fazer TUDO!!
}
Projetil::~Projetil() {
	// Destrutor vazio, pois não há recursos alocados dinamicamente
}
void Projetil::update(float deltaTime) {
	
}
void Projetil::executar() {
	setId(6);
}
void Projetil::setId(int novoId) {
	id = novoId;
}
int Projetil::getId() const {
	return id;
}


