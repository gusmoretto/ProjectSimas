#pragma once
#include "obstaculo.h"
#include "jogador.h"

class ObstFacil : public Obstaculo {
private:
	float lentidao;
public:
	ObstFacil();
	~ObstFacil();
	void executar();
	void obstacular(Jogador* p);
	float getLentidao() const;
	void setLentidao(float lent);
	void setId(int novoId);
	int getId() const;
};
