#pragma once
#include "personagem.h"

class Jogador: public Personagem{
private:
	int pontos;
	static int cont_jogador;
	int id_jogador;
	const float impulsoPulo;
	bool olhandoDireita;
	float velocidadeBase;

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
	void setNoChao(bool NC);
	bool getNochao();
	void setVelocidadeVertical(float nvVelocidadeVertical);
	float getVelocidadeVertical() const;
	void setForcaMitico(float forca) {
		forcaMitico = forca;
	};
	float getForcaMitico() const {
		return forcaMitico;
	};
	float getVelocidadeBase() const { return velocidadeBase; }
};
