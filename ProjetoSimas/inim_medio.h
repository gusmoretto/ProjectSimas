#pragma once
#include "inimigo.h"
#include "jogador.h"

class InimMedio : public Inimigo {
private:
	int tamanho;
	int vida;
	int ataque;
public:
	InimMedio();
	~InimMedio();
	void executar();
	void danificar(Jogador* p);
	void mover();
	int getVida() const;
	int getAtaque();
	void setVida(int v);
	void setAtaque(int a);
};
