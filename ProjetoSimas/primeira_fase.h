#pragma once
#include "fase.h"

class PrimeiraFase : public Fase {
private:
	const int maxAranhas;
protected:
	void criarAgua();
	void criarAranhas();
};
