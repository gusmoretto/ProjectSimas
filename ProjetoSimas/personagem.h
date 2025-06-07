#pragma once
#include <iostream>
#include "entidade.h"

class Personagem : public Entidade {
protected:
	int num_vidas;
	float velocidade;

public:
	Personagem();
	~Personagem();
	//void salvarDataBuffer();
	virtual void mover() = 0;
	virtual void executar() = 0;
	virtual void setVelocidade(float nvVelocidade) = 0;
	virtual float getVelocidade() = 0;
};
