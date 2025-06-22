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
    RectangleShape corpoMorto1;
	RectangleShape corpoMorto2;
    Texture texturaJogador1Morto;
    Texture texturaJogador2Morto;
    bool jogador1EstaMorto;
    bool jogador2EstaMorto;

public:
    Jogo();
    ~Jogo();
    void executar();
    void setFaseAtual(int fase);
    void inicializarTelaFinal();
    void processarEventosTelaFinal(sf::Event& evento);
    void desenharTelaFinal();
    void rodarSave();
};