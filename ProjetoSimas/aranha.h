#pragma once
#include "inimigo.h"
#include "jogador.h"

class Aranha : public Inimigo {
private:
	float direcaoX;

public:
	Aranha();
	~Aranha();
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
	void virarDirecao();
	void tratarColisaoComJogador(Jogador* jogador, int tipoColisao);
	void setForcaMitico(float forca) {
		forcaMitico = forca;
	};
	float getForcaMitico() const {
		return forcaMitico;
	}
	void setVelocidadeVertical(float nvVelocidadeVertical);
	float getVelocidadeVertical() const;
	void setNoChao(bool NC);
	bool getNochao();
};

