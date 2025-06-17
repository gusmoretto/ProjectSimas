#pragma once
#include "fase.h"

class PrimeiraFase : public Fase {
    const int maxLancadores;
    int maxAguas;
public:
    PrimeiraFase(Jogador* j1, Jogador* j2);
    ~PrimeiraFase();

protected:
    void criarInimigos() override;
    void criarObstaculos() override;
};