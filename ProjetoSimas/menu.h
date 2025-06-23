#pragma once
#include "ente.h"
#include "jogo.h"
#include "gerenciador_grafico.h" 

class Menu : public Ente {
private:
    Jogo* pJogo;
    Gerenciadores::GerenciadorGrafico* pGG_Menu;

    Font font;
    Text textoNovoFase1;
    Text textoNovoFase2;
    Text textoSair;
    RectangleShape botaoNovoFase1;
    RectangleShape botaoNovoFase2;
    Text textoRanking;
    RectangleShape botaoRanking;
    RectangleShape botaoSair;
    Texture texturaFundoMenu; 
    Sprite spriteFundoMenu;
    Text textoCarregar; 
    RectangleShape botaoCarregar;
    Text textoEscolhaJogadores;
    bool mostrarEscolhaJogadores = false;
    sf::Vector2f posicaoEscolhaJogadores;
    RectangleShape botao1Jogador;
    RectangleShape botao2Jogadores;
    Text texto1Jogador;
    Text texto2Jogadores;
    int faseEscolhida = 0; 
    std::string nomeJogador1, nomeJogador2;
    sf::Text textoNomeJogador;
    sf::RectangleShape campoNomeJogador;
    bool inserindoNome = false;
    int numJogadoresEscolhido = 1;
    sf::Vector2f posicaoCampoNomeJogador;
    int indiceJogadorInserindoNome = 0; 

public:
    Menu(Gerenciadores::GerenciadorGrafico* pGG);
    ~Menu();
    void executar();
    void setId(int novoId);
    int getId() const;
    void inicializarTextos();
    void inicializarBotoes();
    void inicializarFundoMenu(const std::string& caminhoTextura);
    void desenharMenu();
    int processarEventos(); 
    void mostrarTelaRanking();
};