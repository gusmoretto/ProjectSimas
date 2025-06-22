#pragma once
#include "fase.h"

class PrimeiraFase : public Fase {
    const int maxLancadores;
    int maxAguas;
public:
    PrimeiraFase(Jogador* j1, Jogador* j2, bool carregarJogo = false);
    ~PrimeiraFase();
    void setId(int novoId);
    int getId() const;

protected:
    void criarInimigos();
    void criarObstaculos();
};