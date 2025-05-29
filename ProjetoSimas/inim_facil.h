#pragma once
#include "inimigo.h"
#include "jogador.h"

class InimFacil : public Inimigo {
private:
	float raio;
	float direcaoX;
public:
	InimFacil();
	~InimFacil();
	void executar();
	void danificar(Jogador* p) ;
	void mover();
};

