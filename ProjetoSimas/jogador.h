#pragma once
#include <SFML/Graphics.hpp>
#include "personagem.h"

class Jogador: public Personagem{
private:
	int vida;
	int ataque;
	int pontos;

public:
	Jogador();
	 ~Jogador();
	int getVida() const;
	int getAtaque() const;
	void setVida(int vida);
	void setAtaque(int ataque);
	void executar();
};
