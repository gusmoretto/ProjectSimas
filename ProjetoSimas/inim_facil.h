#pragma once
#include "inimigo.h"
#include "jogador.h"

class InimFacil : public Inimigo {
private:
	float raio;
	float direcaoX;
	int vida;
	int ataque;
public:
	InimFacil();
	~InimFacil();
	void executar();
	void danificar(Jogador* p) ;
	void mover();
	int getVida() const;
	int getAtaque();	
	void setVida(int v);
	void setAtaque(int a);
	void desenhar();
};

