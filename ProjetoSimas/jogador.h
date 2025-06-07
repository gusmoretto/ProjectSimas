#pragma once
#include "personagem.h"

class Jogador: public Personagem{
private:
	int vida;
	int ataque;
	int pontos;
	static int cont_jogador;
	int id_jogador;
	bool noChao;
	float velocidadeVertical;
	const float impulsoPulo;
	bool olhandoDireita;

public:
	Jogador();
	 ~Jogador();
	int getVida() const;
	int getAtaque() const;
	void setVida(int vida);
	void setAtaque(int ataque);
	void executar();
	virtual void mover();
	int getIdJogador() const;
	void desenhar();
	void setId(int novoId);
	int getId() const;
	void setVelocidade(float nvVelocidade);
	float getVelocidade();
};
