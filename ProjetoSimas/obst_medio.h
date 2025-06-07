#pragma once
#include "obstaculo.h"
#include "jogador.h"

class ObstMedio : public Obstaculo {
private:
	float largura;
public:
	ObstMedio();
	~ObstMedio();
	void executar();
	void obstacular(Jogador* p);
	float getLargura() const;
	void setLargura(float l);
	void setId(int novoId);
	int getId() const ;
};
