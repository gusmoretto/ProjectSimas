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
	int getVida() const;
	int getAtaque() const;	
	void setVida(int v);
	void setAtaque(int a);
	void desenhar();
	void setId(int novoId);
	int getId() const;
	void setVelocidade(float nvVelocidade);
	float getVelocidade();
	void tratarColisaoComJogador(Jogador* jogador, int tipoColisao);
	void setForcaMitico(float forca) {
		forcaMitico = forca;
	};
	float getForcaMitico() const {
		return forcaMitico;
	};
};

