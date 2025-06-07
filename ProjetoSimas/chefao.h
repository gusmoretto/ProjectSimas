#pragma once
#include "inimigo.h"
#include "jogador.h"

class Chefao : public Inimigo {
private:
	short int forca;
	int vida;
	int ataque;
public:
	Chefao();
	~Chefao();
	void executar();
	void danificar(Jogador* p);
	void mover();
	short int getForca() const;
	int getVida() const;
	int getAtaque() const;
	void setForca(short int f);
	void setVida(int v);
	void setAtaque(int a);
	void setId(int novoId);
	int getId() const;
	void setVelocidade(float nvVelocidade);
	float getVelocidade();
};
	