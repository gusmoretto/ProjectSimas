#include "menu.h"
#include <iostream>

Menu::Menu(Gerenciadores::GerenciadorGrafico* pGG) : pJogo(nullptr), pGG_Menu(pGG) {
    if (pGG_Menu) {
        inicializarTextos();
        inicializarBotoes();
        inicializarFundoMenu("fundoMenu.png");
    }
    else {
        std::cerr << "Erro: GerenciadorGrafico passado para Menu � nulo." << std::endl;
    }
}

Menu::~Menu() {
    if (pJogo) {
        delete pJogo;
        pJogo = nullptr;
    }
}

void Menu::inicializarTextos() {
    if (!font.loadFromFile("fonteMenu.TTF")) {
        std::cerr << "Erro ao carregar fonte arial.ttf" << std::endl;
    }

    textoNovoFase1.setFont(font);
    textoNovoFase1.setString("Novo Fase 1");
    textoNovoFase1.setCharacterSize(25);
    textoNovoFase1.setFillColor(sf::Color::Black);
    textoNovoFase1.setOrigin(textoNovoFase1.getLocalBounds().width / 2, textoNovoFase1.getLocalBounds().height / 2);
    textoNovoFase1.setPosition(pGG_Menu->getTamanhoJanelax() / 2, pGG_Menu->getTamanhoJanelay() / 2 - 100);

    textoNovoFase2.setFont(font);
    textoNovoFase2.setString("Novo Fase 2");
    textoNovoFase2.setCharacterSize(25);
    textoNovoFase2.setFillColor(sf::Color::Black);
    textoNovoFase2.setOrigin(textoNovoFase2.getLocalBounds().width / 2, textoNovoFase2.getLocalBounds().height / 2);
    textoNovoFase2.setPosition(pGG_Menu->getTamanhoJanelax() / 2, pGG_Menu->getTamanhoJanelay() / 2);

    textoRanking.setFont(font);
    textoRanking.setString("Ranking");
    textoRanking.setCharacterSize(25);
    textoRanking.setFillColor(sf::Color::Black);
    textoRanking.setOrigin(textoRanking.getLocalBounds().width / 2, textoRanking.getLocalBounds().height / 2);
    // Agora o ranking fica logo abaixo do Novo Fase 2
    textoRanking.setPosition(pGG_Menu->getTamanhoJanelax() / 2, pGG_Menu->getTamanhoJanelay() / 2 + 100);

    textoSair.setFont(font);
    textoSair.setString("Sair do Jogo");
    textoSair.setCharacterSize(30);
    textoSair.setFillColor(sf::Color::Black);
    textoSair.setOrigin(textoSair.getLocalBounds().width / 2, textoSair.getLocalBounds().height / 2);
    // Agora o sair fica abaixo do ranking
    textoSair.setPosition(pGG_Menu->getTamanhoJanelax() / 2, pGG_Menu->getTamanhoJanelay() / 2 + 200);
}

void Menu::inicializarBotoes() {
    botaoNovoFase1.setSize(sf::Vector2f(300.f, 70.f)); 
    botaoNovoFase1.setFillColor(sf::Color::White);
    botaoNovoFase1.setOutlineColor(sf::Color::Black);
    botaoNovoFase1.setOutlineThickness(2.f);
    botaoNovoFase1.setOrigin(botaoNovoFase1.getLocalBounds().width / 2, botaoNovoFase1.getLocalBounds().height / 2);
    botaoNovoFase1.setPosition(textoNovoFase1.getPosition());

    botaoNovoFase2.setSize(sf::Vector2f(300.f, 70.f));
    botaoNovoFase2.setFillColor(sf::Color::White);
    botaoNovoFase2.setOutlineColor(sf::Color::Black);
    botaoNovoFase2.setOutlineThickness(2.f);
    botaoNovoFase2.setOrigin(botaoNovoFase2.getLocalBounds().width / 2, botaoNovoFase2.getLocalBounds().height / 2);
    botaoNovoFase2.setPosition(textoNovoFase2.getPosition());

    botaoSair.setSize(sf::Vector2f(300.f, 70.f)); 
    botaoSair.setFillColor(sf::Color::White); 
    botaoSair.setOutlineColor(sf::Color::Black); 
    botaoSair.setOutlineThickness(2.f); 
    botaoSair.setOrigin(botaoSair.getLocalBounds().width / 2, botaoSair.getLocalBounds().height / 2); 
    botaoSair.setPosition(textoSair.getPosition()); 

    botaoRanking.setSize(sf::Vector2f(300.f, 70.f));
    botaoRanking.setFillColor(sf::Color::White);
    botaoRanking.setOutlineColor(sf::Color::Black);
    botaoRanking.setOutlineThickness(2.f);
    botaoRanking.setOrigin(botaoRanking.getLocalBounds().width / 2, botaoRanking.getLocalBounds().height / 2);
    botaoRanking.setPosition(textoRanking.getPosition());
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
    pGG_Menu->desenha(botaoNovoFase1); 
    pGG_Menu->desenha(botaoNovoFase2);
    pGG_Menu->desenha(botaoSair); 
    pGG_Menu->desenha(botaoRanking);
    pGG_Menu->getWindow().draw(textoNovoFase1); 
    pGG_Menu->getWindow().draw(textoNovoFase2);
    pGG_Menu->getWindow().draw(textoSair); 
    pGG_Menu->getWindow().draw(textoRanking);
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

                if (botaoNovoFase1.getGlobalBounds().contains(mousePos)) { 
                    return 1; 

                }
                if (botaoNovoFase2.getGlobalBounds().contains(mousePos)) {
                    return 2;
                }
                if (botaoSair.getGlobalBounds().contains(mousePos)) { 
                    pGG_Menu->fechar(); 
                    return 0; 
                }
                if (botaoRanking.getGlobalBounds().contains(mousePos)) {
                    return 3; 
                }
            }
        }
        if (evento.type == sf::Event::MouseMoved) { 
            sf::Vector2f mousePos = pGG_Menu->getWindow().mapPixelToCoords(sf::Vector2i(evento.mouseMove.x, evento.mouseMove.y)); 
            if (botaoNovoFase1.getGlobalBounds().contains(mousePos)) {
                botaoNovoFase1.setFillColor(sf::Color(100, 100, 100, 150)); 
            }
            else {
                botaoNovoFase1.setFillColor(sf::Color::White);
            }
            if (botaoNovoFase2.getGlobalBounds().contains(mousePos)) {
                botaoNovoFase2.setFillColor(sf::Color(100, 100, 100, 150));
            }
            else {
                botaoNovoFase2.setFillColor(sf::Color::White);
            }
            if (botaoSair.getGlobalBounds().contains(mousePos)) {
                botaoSair.setFillColor(sf::Color(100, 100, 100, 150)); 
            }
            else {
                botaoSair.setFillColor(sf::Color::White); 
            }
            if (botaoRanking.getGlobalBounds().contains(mousePos)) {
                botaoRanking.setFillColor(sf::Color(100, 100, 100, 150));
            } else {
                botaoRanking.setFillColor(sf::Color::White);
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
        pGG_Menu->fechar();
        pJogo = new Jogo(); 
        pJogo->setFaseAtual(escolha);
        pJogo->executar(); 
    }
    else if (escolha == 2) {
        pGG_Menu->fechar();
        pJogo = new Jogo();
        pJogo->setFaseAtual(escolha);
		pJogo->executar();
    }
	else if (escolha == 3) {
    }
}

void Menu::setId(int novoId) {
    id = novoId; 
}

int Menu::getId() const {
    return id; 
}