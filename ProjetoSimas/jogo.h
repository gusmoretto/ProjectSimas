#pragma once
#include "jogador.h"
using namespace Gerenciadores;

class Jogo {
private:
	Jogador pjog1;
	GerenciadorGrafico GG;

public:
	Jogo();
	~Jogo();
	void executar();


};
