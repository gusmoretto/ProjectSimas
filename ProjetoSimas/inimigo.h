#pragma once
#include "personagem.h"
#include "jogador.h"

class Inimigo: public Personagem{
protected:
	int nivel_maldade;
public:
	Inimigo();
	~Inimigo();
	void salvarDataBuffer();
	virtual void salvar() = 0;
	virtual void executar() = 0;
	virtual void danificar(Jogador* p) = 0;
	virtual void mover() = 0;
	virtual void setVelocidade(float nvVelocidade) = 0;
	virtual float getVelocidade() = 0;
	virtual void tratarColisaoComJogador(Jogador* jogador, int tipoColisao) = 0;
	virtual void setForcaMitico(float forca) = 0;
	virtual float getForcaMitico() const = 0; 
	virtual void setId(int novoId) = 0;
	virtual int getId() const = 0;

};
