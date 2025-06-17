#pragma once
#include "fase.h"

class PrimeiraFase : public Fase {
private:
	const int maxLancadores;
protected:
	PrimeiraFase();
	~PrimeiraFase();
	void criarAgua();
	void criarLancador();
	void criarInimigos() {}
	void criarObstaculos() {}
};
