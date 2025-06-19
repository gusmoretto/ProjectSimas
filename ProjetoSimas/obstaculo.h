#pragma once
#include "entidade.h"
#include "jogador.h"
#include <iostream>

class Obstaculo : public Entidade {
protected:
	bool danoso;
	bool gravidadeAtiva;
public:
	Obstaculo();
	~Obstaculo();
	virtual void salvar() = 0;
	void salvarDataBuffer();
	virtual void executar() = 0;
	virtual void obstacular(Jogador* p) = 0; 
	virtual void setForcaMitico(float forca) = 0; 
	virtual float getForcaMitico() const = 0; 
	virtual void atualizarFisica(float dt = 0.016f) = 0;
};	