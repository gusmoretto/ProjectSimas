#pragma once
#include "personagem.h"
#include "jogador.h"

class Inimigo: public Personagem{
private:
	static int cont_inimigo;
	int id_inimigo;
protected:
	int nivel_maldade;
public:
	Inimigo();
	~Inimigo();
	int getIdInimigo() const;
	//void salvarDataBuffer();
	//virtual void salva() = 0;
	virtual void executar() = 0;
	virtual void danificar(Jogador* p) = 0;
	virtual void mover() = 0;
	virtual void setVelocidade(float nvVelocidade) = 0;
	virtual float getVelocidade() = 0;
	virtual void tratarColisaoComJogador(Jogador* jogador, int tipoColisao) = 0;
	virtual void setForcaMitico(float forca) = 0;
	virtual float getForcaMitico() const = 0; 

};
