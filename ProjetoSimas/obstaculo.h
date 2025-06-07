#pragma once
#include "entidade.h"
#include "jogador.h"
#include <iostream>

class Obstaculo : public Entidade {
protected:
	bool danoso;
public:
	Obstaculo();
	~Obstaculo();
	virtual void executar() = 0;
	virtual void obstacular(Jogador* p) = 0; 
};	