#include "inimigo.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int Inimigo::cont_inimigo = 0;

Inimigo::Inimigo() {
	id_inimigo = cont_inimigo++;
	nivel_maldade = 0;
}
Inimigo::~Inimigo() {
	id_inimigo = -1;
}
int Inimigo::getIdInimigo() const {
	return id_inimigo;
}



