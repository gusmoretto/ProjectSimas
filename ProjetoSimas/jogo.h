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
    bool jogoPausado;
    RectangleShape botaoSalvarSair;
    Text textoBotaoSalvarSair;
    RectangleShape fundoPausa; 
    Text textoPausa;
    int numJogadores;

public:
    Jogo(int numJogadores = 1);
    ~Jogo();
    void executar();
	void setFaseAtual(int fase, bool carregarJogo);
    void inicializarTelaFinal();
    void processarEventosTelaFinal(sf::Event& evento);
    void desenharTelaFinal();
    void rodarSave();
    void inicializarMenuPausa();
    void processarEventosMenuPausa(sf::Event& evento);
    void desenharMenuPausa();
};