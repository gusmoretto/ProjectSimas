#pragma once
#include "gerenciador_grafico.h"
#include "jogador.h"
#include "fase.h"

using namespace Gerenciadores;

class Jogo {
private:
    GerenciadorGrafico* pGG;
    Jogador* jogador1;
	Jogador* jogador2;
    Fase* faseAtual;
    bool vitoria;
    bool derrota;
    Texture texturaVitoria;
    Texture texturaDerrota;
    Sprite spriteTelaFinal;
    Font fonteBotao;
    Text textoBotaoSair;
    RectangleShape botaoSair;

public:
    Jogo();
    ~Jogo();
    void executar();
    void setFaseAtual(int fase);
    void inicializarTelaFinal();
    void processarEventosTelaFinal(sf::Event& evento);
    void desenharTelaFinal();
};