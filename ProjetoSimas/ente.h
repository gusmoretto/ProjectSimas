#pragma once
#include "gerenciador_grafico.h"

class Ente {
protected:
	int id;
	static Gerenciadores::GerenciadorGrafico *pGG;
	//Figura* pFig;
public:
	Ente();
	virtual ~Ente();
	virtual void executar() = 0;
};
