#pragma once
#include "personagem.h"
#include "jogador.h"
#include <SFML/Graphics.hpp>

class Inimigo: public Personagem{
private:
	static int cont_inimigo;
	int id_inimigo;
protected:
	int vida;
	int ataque;
	int nivel_maldade;
public:
	Inimigo();
	~Inimigo();
	int getVida() const;
	int getAtaque() const;
	void setVida(int vida);
	void setAtaque(int ataque);
	int getIdInimigo() const;
	//void salvarDataBuffer();
	virtual void executar() = 0;
	virtual void danificar(Jogador* p) = 0;
	virtual void mover() = 0;
	//virtual void salva() = 0;
};
