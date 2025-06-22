#pragma once
#include "fase.h"

class SegundaFase : public Fase {
    const int maxEspinhos;
    const int maxChefoes;
public:
    SegundaFase(Jogador* j1, Jogador* j2, bool carregarJogo = false);
    ~SegundaFase();
    void setId(int novoId);
    int getId() const;

protected:
    void criarInimigos();
    void criarObstaculos();
};