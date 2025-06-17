#pragma once
#include "ente.h"
#include "jogo.h"
#include "gerenciador_grafico.h" 

class Menu : public Ente {
private:
    Jogo* pJogo;
    Gerenciadores::GerenciadorGrafico* pGG_Menu;

    sf::Font font;
    sf::Text textoNovoJogo;
    sf::Text textoSair;
    sf::RectangleShape botaoNovoJogo;
    sf::RectangleShape botaoSair;
    sf::Texture texturaFundoMenu; 
    sf::Sprite spriteFundoMenu;

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
};