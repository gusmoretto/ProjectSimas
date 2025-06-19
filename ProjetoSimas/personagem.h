#pragma once
#include <iostream>
#include "entidade.h"

class Personagem : public Entidade {
protected:
	int num_vidas;
	float velocidade;
	int vida;
	int ataque;
	bool noChao;

public:
	Personagem();
	~Personagem();
	void salvarDataBuffer();
	virtual void salvar() = 0;
	virtual void mover() = 0;
	virtual void executar() = 0;
	virtual void setVelocidade(float nvVelocidade) = 0;
	virtual float getVelocidade() = 0;
	virtual int getVida() const = 0;
	virtual int getAtaque() const = 0;
	virtual void setVida(int v) = 0;
	virtual void setAtaque(int a) = 0;
	virtual void setVelocidadeVertical(float nvVelocidadeVertical) = 0;
	virtual float getVelocidadeVertical() const = 0;
	virtual void setNoChao(bool NC) = 0;
	virtual bool getNochao() = 0;
};
