#pragma once
#include "gerenciador_grafico.h"
#include "jogador.h"
#include "fase.h"

using namespace Gerenciadores;

class Jogo {
private:
    GerenciadorGrafico* pGG;
    Jogador* jogador1;
    Fase* faseAtual;

public:
    Jogo();
    ~Jogo();
    void executar();
};