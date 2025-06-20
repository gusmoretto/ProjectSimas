#include "inimigo.h"
#include <iostream>


Inimigo::Inimigo() {
	nivel_maldade = 0;
}
Inimigo::~Inimigo() {

}
void Inimigo::salvarDataBuffer() {
	Personagem::salvarDataBuffer();
	if (buffer)
		*buffer << nivel_maldade << " ";
}


