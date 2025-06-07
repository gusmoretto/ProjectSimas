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
	virtual void setId(int novoId) = 0;
	virtual int getId() const  = 0;
	void setGerenciadorGrafico(Gerenciadores::GerenciadorGrafico* p) { pGG = p; }
};
