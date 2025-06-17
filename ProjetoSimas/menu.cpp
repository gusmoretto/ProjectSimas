#include "menu.h"
#include <iostream>

Menu::Menu(Gerenciadores::GerenciadorGrafico* pGG) : pJogo(nullptr), pGG_Menu(pGG) {
    if (pGG_Menu) {
        inicializarTextos();
        inicializarBotoes();
        inicializarFundoMenu("fundoMenu.png");
    }
    else {
        std::cerr << "Erro: GerenciadorGrafico passado para Menu é nulo." << std::endl;
    }
}

Menu::~Menu() {
    if (pJogo) {
        delete pJogo;
        pJogo = nullptr;
    }
}

void Menu::inicializarTextos() {
    if (!font.loadFromFile("fonteMenu.ttf")) { 
        std::cerr << "Erro ao carregar fonte arial.ttf" << std::endl; 
    }

    textoNovoJogo.setFont(font); 
    textoNovoJogo.setString("Novo Jogo"); 
    textoNovoJogo.setCharacterSize(30); 
    textoNovoJogo.setFillColor(sf::Color::Black); 
    textoNovoJogo.setOrigin(textoNovoJogo.getLocalBounds().width / 2, textoNovoJogo.getLocalBounds().height / 2); 
    textoNovoJogo.setPosition(pGG_Menu->getTamanhoJanelax() / 2, pGG_Menu->getTamanhoJanelay() / 2 - 100); 

    textoSair.setFont(font); 
    textoSair.setString("Sair do Jogo"); 
    textoSair.setCharacterSize(30); 
    textoSair.setFillColor(sf::Color::Black); 
    textoSair.setOrigin(textoSair.getLocalBounds().width / 2, textoSair.getLocalBounds().height / 2); 
    textoSair.setPosition(pGG_Menu->getTamanhoJanelax() / 2, pGG_Menu->getTamanhoJanelay() / 2 + 50); 
}

void Menu::inicializarBotoes() {
    botaoNovoJogo.setSize(sf::Vector2f(300.f, 70.f)); 
    botaoNovoJogo.setFillColor(sf::Color::White); 
    botaoNovoJogo.setOutlineColor(sf::Color::Black); 
    botaoNovoJogo.setOutlineThickness(2.f); 
    botaoNovoJogo.setOrigin(botaoNovoJogo.getLocalBounds().width / 2, botaoNovoJogo.getLocalBounds().height / 2); 
    botaoNovoJogo.setPosition(textoNovoJogo.getPosition()); 

    botaoSair.setSize(sf::Vector2f(300.f, 70.f)); 
    botaoSair.setFillColor(sf::Color::White); 
    botaoSair.setOutlineColor(sf::Color::Black); 
    botaoSair.setOutlineThickness(2.f); 
    botaoSair.setOrigin(botaoSair.getLocalBounds().width / 2, botaoSair.getLocalBounds().height / 2); 
    botaoSair.setPosition(textoSair.getPosition()); 
}
void Menu::inicializarFundoMenu(const std::string& caminhoTextura) {
    if (!texturaFundoMenu.loadFromFile(caminhoTextura)) {
        std::cerr << "Erro ao carregar imagem de fundo do menu: " << caminhoTextura << std::endl;
    }
    else {
        spriteFundoMenu.setTexture(texturaFundoMenu);
        float scaleX = (float)pGG_Menu->getTamanhoJanelax() / texturaFundoMenu.getSize().x;
        float scaleY = (float)pGG_Menu->getTamanhoJanelay() / texturaFundoMenu.getSize().y;
        spriteFundoMenu.setScale(scaleX, scaleY);
    }
}

void Menu::desenharMenu() {
    pGG_Menu->clear(); 
    pGG_Menu->getWindow().draw(spriteFundoMenu);
    pGG_Menu->desenha(botaoNovoJogo); 
    pGG_Menu->desenha(botaoSair); 
    pGG_Menu->getWindow().draw(textoNovoJogo); 
    pGG_Menu->getWindow().draw(textoSair); 
    pGG_Menu->mostrar(); 
}

int Menu::processarEventos() {
    sf::Event evento; 
    while (pGG_Menu->getWindow().pollEvent(evento)) { 
        if (evento.type == sf::Event::Closed) { 
            pGG_Menu->fechar(); 
            return 0; 
        }
        if (evento.type == sf::Event::MouseButtonReleased) { 
            if (evento.mouseButton.button == sf::Mouse::Left) { 
                sf::Vector2f mousePos = pGG_Menu->getWindow().mapPixelToCoords(sf::Vector2i(evento.mouseButton.x, evento.mouseButton.y)); 

                if (botaoNovoJogo.getGlobalBounds().contains(mousePos)) { 
                    return 1; 
                }
                if (botaoSair.getGlobalBounds().contains(mousePos)) { 
                    pGG_Menu->fechar(); 
                    return 0; 
                }
            }
        }
        if (evento.type == sf::Event::MouseMoved) { 
            sf::Vector2f mousePos = pGG_Menu->getWindow().mapPixelToCoords(sf::Vector2i(evento.mouseMove.x, evento.mouseMove.y)); 
            if (botaoNovoJogo.getGlobalBounds().contains(mousePos)) { 
                botaoNovoJogo.setFillColor(sf::Color(100, 100, 100, 150)); 
            }
            else {
                botaoNovoJogo.setFillColor(sf::Color::White);
            }
            if (botaoSair.getGlobalBounds().contains(mousePos)) {
                botaoSair.setFillColor(sf::Color(100, 100, 100, 150)); 
            }
            else {
                botaoSair.setFillColor(sf::Color::White); 
            }
        }
    }
    return -1; 
}

void Menu::executar() {
    int escolha = -1;
    while (pGG_Menu->estaAberta() && escolha == -1) { 
        desenharMenu(); 
        escolha = processarEventos(); 
    }

    if (escolha == 1) { 
        pJogo = new Jogo(); 
        pJogo->executar(); 
    }
}

void Menu::setId(int novoId) {
    id = novoId; 
}

int Menu::getId() const {
    return id; 
}