#include "menu.h"
#include "jogo.h" 
#include "gerenciador_grafico.h" 
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

Menu::Menu(Gerenciadores::GerenciadorGrafico* pGG) :
    pJogo(nullptr),
    pGG_Menu(pGG),
    faseEscolhida(0),
    numJogadoresEscolhido(0),
    indiceJogadorInserindoNome(0),
    mostrarEscolhaJogadores(false),
    inserindoNome(false)
{
    if (pGG_Menu) {
        inicializarTextos();
        inicializarBotoes();
        inicializarFundoMenu("fundoMenu.png"); 
    }
    else {
        std::cerr << "Erro: GerenciadorGrafico passado para Menu eh nulo." << std::endl;
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
    textoNovoFase1.setString("Novo - Fase 1");
    textoNovoFase1.setCharacterSize(25);
    textoNovoFase1.setFillColor(sf::Color::Black);
    textoNovoFase1.setOrigin(textoNovoFase1.getLocalBounds().width / 2, textoNovoFase1.getLocalBounds().height / 2);
    textoNovoFase1.setPosition(pGG_Menu->getTamanhoJanelax() / 2, pGG_Menu->getTamanhoJanelay() / 2 - 150);

    textoNovoFase2.setFont(font);
    textoNovoFase2.setString("Novo - Fase 2");
    textoNovoFase2.setCharacterSize(25);
    textoNovoFase2.setFillColor(sf::Color::Black);
    textoNovoFase2.setOrigin(textoNovoFase2.getLocalBounds().width / 2, textoNovoFase2.getLocalBounds().height / 2);
    textoNovoFase2.setPosition(pGG_Menu->getTamanhoJanelax() / 2, pGG_Menu->getTamanhoJanelay() / 2 - 50);

    textoCarregar.setFont(font);
    textoCarregar.setString("Carregar Jogo");
    textoCarregar.setCharacterSize(25);
    textoCarregar.setFillColor(sf::Color::Black);
    textoCarregar.setOrigin(textoCarregar.getLocalBounds().width / 2, textoCarregar.getLocalBounds().height / 2);
    textoCarregar.setPosition(pGG_Menu->getTamanhoJanelax() / 2, pGG_Menu->getTamanhoJanelay() / 2 + 50);

    textoRanking.setFont(font);
    textoRanking.setString("Ranking");
    textoRanking.setCharacterSize(25);
    textoRanking.setFillColor(sf::Color::Black);
    textoRanking.setOrigin(textoRanking.getLocalBounds().width / 2, textoRanking.getLocalBounds().height / 2);
    textoRanking.setPosition(pGG_Menu->getTamanhoJanelax() / 2, pGG_Menu->getTamanhoJanelay() / 2 + 150);

    textoSair.setFont(font);
    textoSair.setString("Sair do Jogo");
    textoSair.setCharacterSize(30);
    textoSair.setFillColor(sf::Color::Black);
    textoSair.setOrigin(textoSair.getLocalBounds().width / 2, textoSair.getLocalBounds().height / 2);
    textoSair.setPosition(pGG_Menu->getTamanhoJanelax() / 2, pGG_Menu->getTamanhoJanelay() / 2 + 250);

    textoEscolhaJogadores.setFont(font);
    textoEscolhaJogadores.setString("Escolha: 1 ou 2 Jogadores");
    textoEscolhaJogadores.setCharacterSize(22);
    textoEscolhaJogadores.setFillColor(sf::Color::Black);
    textoEscolhaJogadores.setOrigin(0, textoEscolhaJogadores.getLocalBounds().height / 2);

    textoNomeJogador.setFont(font);
    textoNomeJogador.setCharacterSize(22);
    textoNomeJogador.setFillColor(sf::Color::Black);
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

    botaoCarregar.setSize(sf::Vector2f(300.f, 70.f));
    botaoCarregar.setFillColor(sf::Color::White);
    botaoCarregar.setOutlineColor(sf::Color::Black);
    botaoCarregar.setOutlineThickness(2.f);
    botaoCarregar.setOrigin(botaoCarregar.getLocalBounds().width / 2, botaoCarregar.getLocalBounds().height / 2);
    botaoCarregar.setPosition(textoCarregar.getPosition());

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

    botao1Jogador.setSize(sf::Vector2f(180.f, 40.f));
    botao1Jogador.setFillColor(sf::Color::White);
    botao1Jogador.setOutlineColor(sf::Color::Black);
    botao1Jogador.setOutlineThickness(2.f);

    texto1Jogador.setFont(font);
    texto1Jogador.setString("1 Jogador");
    texto1Jogador.setCharacterSize(18);
    texto1Jogador.setFillColor(sf::Color::Black);

    botao2Jogadores.setSize(sf::Vector2f(180.f, 40.f));
    botao2Jogadores.setFillColor(sf::Color::White);
    botao2Jogadores.setOutlineColor(sf::Color::Black);
    botao2Jogadores.setOutlineThickness(2.f);

    texto2Jogadores.setFont(font);
    texto2Jogadores.setString("2 Jogadores");
    texto2Jogadores.setCharacterSize(18);
    texto2Jogadores.setFillColor(sf::Color::Black);

    campoNomeJogador.setSize(sf::Vector2f(220.f, 40.f));
    campoNomeJogador.setFillColor(sf::Color::White);
    campoNomeJogador.setOutlineColor(sf::Color::Black);
    campoNomeJogador.setOutlineThickness(2.f);
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
    pGG_Menu->desenha(botaoCarregar);
    pGG_Menu->desenha(botaoSair);
    pGG_Menu->desenha(botaoRanking);
    pGG_Menu->getWindow().draw(textoNovoFase1);
    pGG_Menu->getWindow().draw(textoNovoFase2);
    pGG_Menu->getWindow().draw(textoCarregar);
    pGG_Menu->getWindow().draw(textoSair);
    pGG_Menu->getWindow().draw(textoRanking);

    if (mostrarEscolhaJogadores) {
        pGG_Menu->desenha(botao1Jogador);
        pGG_Menu->desenha(botao2Jogadores);
        pGG_Menu->getWindow().draw(texto1Jogador);
        pGG_Menu->getWindow().draw(texto2Jogadores);
    }

    if (inserindoNome) {
        campoNomeJogador.setPosition(posicaoCampoNomeJogador);
        std::string nomeExibido = (indiceJogadorInserindoNome == 0) ? nomeJogador1 : nomeJogador2;
        textoNomeJogador.setString(nomeExibido.empty() ? "Digite o nome..." : nomeExibido);
        textoNomeJogador.setPosition(posicaoCampoNomeJogador + sf::Vector2f(10.f, 5.f));
        pGG_Menu->desenha(campoNomeJogador);
        pGG_Menu->getWindow().draw(textoNomeJogador);
    }
    pGG_Menu->mostrar();
}

int Menu::processarEventos() {
    sf::Event evento;
    while (pGG_Menu->getWindow().pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            pGG_Menu->fechar();
            return 5; 
        }

        if (inserindoNome && evento.type == sf::Event::TextEntered) {
            std::string* nomeAtual = (indiceJogadorInserindoNome == 0) ? &nomeJogador1 : &nomeJogador2;
            if (evento.text.unicode == '\b') { 
                if (!nomeAtual->empty()) nomeAtual->pop_back();
            }
            else if (evento.text.unicode == '\r' || evento.text.unicode == '\n') { 
                if (numJogadoresEscolhido == 2 && indiceJogadorInserindoNome == 0) {
                    indiceJogadorInserindoNome = 1;
                    return -1; 
                }
                else {
                    inserindoNome = false;
                    mostrarEscolhaJogadores = false;
                    return numJogadoresEscolhido; 
                }
            }
            else if (evento.text.unicode < 128 && evento.text.unicode != '\t') {
                if (nomeAtual->size() < 16) *nomeAtual += static_cast<char>(evento.text.unicode);
            }
            return -1; 
        }

        if (evento.type == sf::Event::MouseButtonReleased && evento.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = pGG_Menu->getWindow().mapPixelToCoords(sf::Vector2i(evento.mouseButton.x, evento.mouseButton.y));

            if (botaoNovoFase1.getGlobalBounds().contains(mousePos)) {
                mostrarEscolhaJogadores = true;
                faseEscolhida = 1;
                sf::Vector2f basePos = botaoNovoFase1.getPosition() + sf::Vector2f(0, botaoNovoFase1.getSize().y / 2 + 10);
                botao1Jogador.setPosition(basePos + sf::Vector2f(-100, 0));
                texto1Jogador.setPosition(basePos + sf::Vector2f(-100, 0));
                botao2Jogadores.setPosition(basePos + sf::Vector2f(100, 0));
                texto2Jogadores.setPosition(basePos + sf::Vector2f(100, 0));
                return -1;
            }
            if (botaoNovoFase2.getGlobalBounds().contains(mousePos)) {
                mostrarEscolhaJogadores = true;
                faseEscolhida = 2;
                sf::Vector2f basePos = botaoNovoFase2.getPosition() + sf::Vector2f(0, botaoNovoFase2.getSize().y / 2 + 10);
                botao1Jogador.setPosition(basePos + sf::Vector2f(-100, 0));
                texto1Jogador.setPosition(basePos + sf::Vector2f(-100, 0));
                botao2Jogadores.setPosition(basePos + sf::Vector2f(100, 0));
                texto2Jogadores.setPosition(basePos + sf::Vector2f(100, 0));
                return -1;
            }
            if (botaoSair.getGlobalBounds().contains(mousePos)) {
                return 5; 
            }
            if (botaoRanking.getGlobalBounds().contains(mousePos)) {
                return 3;
            }
            if (botaoCarregar.getGlobalBounds().contains(mousePos)) {
                return 4;
            }
            if (mostrarEscolhaJogadores && botao1Jogador.getGlobalBounds().contains(mousePos)) {
                numJogadoresEscolhido = 1;
                nomeJogador1.clear();
                indiceJogadorInserindoNome = 0;
                inserindoNome = true;
                posicaoCampoNomeJogador = botao1Jogador.getPosition() + sf::Vector2f(0, botao1Jogador.getSize().y + 10);
                return -1;
            }
            if (mostrarEscolhaJogadores && botao2Jogadores.getGlobalBounds().contains(mousePos)) {
                numJogadoresEscolhido = 2;
                nomeJogador1.clear();
                nomeJogador2.clear();
                indiceJogadorInserindoNome = 0;
                inserindoNome = true;
                posicaoCampoNomeJogador = botao2Jogadores.getPosition() + sf::Vector2f(0, botao2Jogadores.getSize().y + 10);
                return -1;
            }
        }

        if (evento.type == sf::Event::MouseMoved) {
            sf::Vector2f mousePos = pGG_Menu->getWindow().mapPixelToCoords(sf::Vector2i(evento.mouseMove.x, evento.mouseMove.y));
            botaoNovoFase1.getGlobalBounds().contains(mousePos) ? botaoNovoFase1.setFillColor(sf::Color(200, 200, 200)) : botaoNovoFase1.setFillColor(sf::Color::White);
            botaoNovoFase2.getGlobalBounds().contains(mousePos) ? botaoNovoFase2.setFillColor(sf::Color(200, 200, 200)) : botaoNovoFase2.setFillColor(sf::Color::White);
            botaoCarregar.getGlobalBounds().contains(mousePos) ? botaoCarregar.setFillColor(sf::Color(200, 200, 200)) : botaoCarregar.setFillColor(sf::Color::White);
            botaoRanking.getGlobalBounds().contains(mousePos) ? botaoRanking.setFillColor(sf::Color(200, 200, 200)) : botaoRanking.setFillColor(sf::Color::White);
            botaoSair.getGlobalBounds().contains(mousePos) ? botaoSair.setFillColor(sf::Color(200, 200, 200)) : botaoSair.setFillColor(sf::Color::White);
        }
    }
    return -1; 
}

void Menu::mostrarTelaRanking() {
    sf::RectangleShape fundoRanking;
    fundoRanking.setSize(sf::Vector2f(pGG_Menu->getTamanhoJanelax() * 0.8f, pGG_Menu->getTamanhoJanelay() * 0.85f));
    fundoRanking.setFillColor(sf::Color(0, 0, 0, 150)); 
    fundoRanking.setOutlineColor(sf::Color::White);
    fundoRanking.setOutlineThickness(2.f);
    fundoRanking.setOrigin(fundoRanking.getSize().x / 2.f, fundoRanking.getSize().y / 2.f);
    fundoRanking.setPosition(pGG_Menu->getTamanhoJanelax() / 2.f, pGG_Menu->getTamanhoJanelay() / 2.f);

    std::vector<std::pair<std::string, int>> ranking;
    std::ifstream arqRanking("ranking.txt");
    std::string nome;
    int pontos;

    if (arqRanking.is_open()) {
        while (arqRanking >> nome >> pontos) {
            ranking.push_back({ nome, pontos });
        }
        arqRanking.close();
    }

    std::sort(ranking.begin(), ranking.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    sf::Text textoTitulo("Ranking", font, 40);
    textoTitulo.setFillColor(sf::Color::White);
    textoTitulo.setOutlineColor(sf::Color::Black);
    textoTitulo.setOutlineThickness(2.f);
    textoTitulo.setOrigin(textoTitulo.getLocalBounds().width / 2, 0);
    textoTitulo.setPosition(pGG_Menu->getTamanhoJanelax() / 2.f, fundoRanking.getPosition().y - fundoRanking.getSize().y / 2 + 20.f);

    sf::Text textoVoltar("Pressione ESC para Voltar", font, 20);
    textoVoltar.setFillColor(sf::Color::White);
    textoVoltar.setOutlineColor(sf::Color::Black);
    textoVoltar.setOutlineThickness(2.f);
    textoVoltar.setOrigin(textoVoltar.getLocalBounds().width / 2, 0);
    textoVoltar.setPosition(pGG_Menu->getTamanhoJanelax() / 2.f, fundoRanking.getPosition().y + fundoRanking.getSize().y / 2 - 40.f);

    bool mostrando = true;
    while (mostrando && pGG_Menu->estaAberta()) {
        sf::Event evento;
        while (pGG_Menu->getWindow().pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) pGG_Menu->fechar();
            if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) mostrando = false;
        }

        pGG_Menu->clear();
        pGG_Menu->getWindow().draw(spriteFundoMenu); 
        pGG_Menu->getWindow().draw(fundoRanking);    
        pGG_Menu->getWindow().draw(textoTitulo);
        pGG_Menu->getWindow().draw(textoVoltar);

        float posY = textoTitulo.getPosition().y + 80.f;
        int count = 0;
        for (const auto& entrada : ranking) {
            if (count >= 10) break;
            sf::Text textoEntrada(std::to_string(count + 1) + ". " + entrada.first + " - " + std::to_string(entrada.second) + " pts", font, 24);
            textoEntrada.setFillColor(sf::Color::White);
            textoEntrada.setOutlineColor(sf::Color::Black); 
            textoEntrada.setOutlineThickness(2.f);        
            textoEntrada.setPosition(fundoRanking.getPosition().x - fundoRanking.getSize().x / 2 + 50.f, posY);
            pGG_Menu->getWindow().draw(textoEntrada);
            posY += 40.f;
            count++;
        }
        pGG_Menu->mostrar();
    }
}

void Menu::executar() {
    while (pGG_Menu->estaAberta()) {

        int escolha = -1;
        while (pGG_Menu->estaAberta() && escolha == -1) {
            desenharMenu();
            escolha = processarEventos();
        }

        if (!pGG_Menu->estaAberta() || escolha == 5) {
            break; 
        }

        if ((escolha == 1 || escolha == 2)) {
            pJogo = new Jogo(escolha);

            if (pJogo->getJogador1()) pJogo->getJogador1()->setNome(nomeJogador1);
            if (pJogo->getJogador2()) pJogo->getJogador2()->setNome(nomeJogador2);

            pJogo->setFaseAtual(faseEscolhida, false);
            pJogo->executar();

            delete pJogo;
            pJogo = nullptr;
        }
        else if (escolha == 3) {
            mostrarTelaRanking();
        }
        else if (escolha == 4) {
            if (nomeJogador1.empty()) {
                std::cout << "Por favor, insira o nome do jogador 1 antes de carregar." << std::endl;
                continue; 
            }

            int numJogadoresSalvos = 1;
            std::ifstream arqJogo("arquivo_jogo.txt");
            if (arqJogo.is_open()) {
                arqJogo >> numJogadoresSalvos;
                arqJogo.close();
            }

            pJogo = new Jogo(numJogadoresSalvos);

            if (pJogo->getJogador1()) pJogo->getJogador1()->setNome(nomeJogador1);
            if (numJogadoresSalvos == 2 && pJogo->getJogador2() && !nomeJogador2.empty()) {
                pJogo->getJogador2()->setNome(nomeJogador2);
            }

            pJogo->rodarSave();

            delete pJogo;
            pJogo = nullptr;
        }
    }
}

void Menu::setId(int novoId) {
    id = novoId;
}

int Menu::getId() const {
    return id;
}
