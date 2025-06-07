#pragma once
#include "obstaculo.h"
#include "jogador.h"

class Plataforma : public Obstaculo {
private:
	int altura;
public:
	Plataforma();
	~Plataforma();
	void executar();
	void obstacular(Jogador* p);
};
