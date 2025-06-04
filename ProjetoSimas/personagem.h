#pragma once
#include <iostream>
#include "entidade.h"

class Personagem : public Entidade {
protected:
	int num_vidas;
	float velocidade;
	static int cont_personagem;
	int id_personagem;
public:
	Personagem();
	~Personagem();
	//void salvarDataBuffer();
	virtual void mover() = 0;
	virtual void executar() = 0;
	int getIdPersonagem() const;
};
