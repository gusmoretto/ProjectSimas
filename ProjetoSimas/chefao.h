#pragma once
#include "inimigo.h"
#include "jogador.h"

class Chefao : public Inimigo {
private:
	short int forca;
	float direcaoX = 1.f;
	float posicaoInicialX;
    float limiteEsquerda;
    float limiteDireita;
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
	void desenhar();
	void setForcaMitico(float forca) {
		forcaMitico = forca;
	};
	float getForcaMitico() const {
		return forcaMitico;
	};
	void setVelocidadeVertical(float nvVelocidadeVertical);
	float getVelocidadeVertical() const;
	void setNoChao(bool NC);
	bool getNochao();
	void tratarColisaoComJogador(Jogador* jogador, int tipoColisao);
	void salvar();
};
	