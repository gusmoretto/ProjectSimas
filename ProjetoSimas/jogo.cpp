#include "jogo.h"
#include "primeira_fase.h"
#include "segunda_fase.h"
#include "inimigo.h"
#include "obstaculo.h"
#include "lancador.h"
#include "projetil.h"
#include "elemento.h"

Jogo::Jogo() : pGG(new GerenciadorGrafico()), jogador1(nullptr), jogador2(nullptr), faseAtual(nullptr) {
    Ente::setGerenciadorGrafico(pGG);
    jogador1 = new Jogador();
    jogador1->executar();
    jogador2 = new Jogador();
    jogador2->executar();
    pGG->inicializarBarraVida(2);
    vitoria = false;
    derrota = false;
    inicializarTelaFinal();
    jogador1EstaMorto = false;
    jogador2EstaMorto = false;
    if (!texturaJogador1Morto.loadFromFile("playermorto.png")) {
        std::cerr << "Erro: Nao foi possivel carregar player_morto.png" << std::endl;
    }
    if (!texturaJogador2Morto.loadFromFile("player2morto.png")) {
        std::cerr << "Erro: Nao foi possivel carregar player2_morto.png" << std::endl;
    }
}

Jogo::~Jogo() {
    if (faseAtual) delete faseAtual;
    if (pGG) delete pGG;
    if (jogador1) delete jogador1;
    if (jogador2) delete jogador2;
}

void Jogo::inicializarTelaFinal() {
    if (!texturaVitoria.loadFromFile("vitoria.png")) {
        std::cerr << "Erro: Nao foi possivel carregar vitoria.png" << std::endl;
    }
    if (!texturaDerrota.loadFromFile("derrota.png")) {
        std::cerr << "Erro: Nao foi possivel carregar derrota.png" << std::endl;
    }

    if (!fonteBotao.loadFromFile("fonteMenu.ttf")) {
        std::cerr << "Erro ao carregar fonteMenu.ttf" << std::endl;
        return;
    }

    botaoSair.setSize(sf::Vector2f(200.f, 60.f));
    botaoSair.setFillColor(sf::Color(150, 0, 0));
    botaoSair.setOutlineColor(sf::Color::White);
    botaoSair.setOutlineThickness(2.f);

    textoBotaoSair.setFont(fonteBotao);
    textoBotaoSair.setString("Sair");
    textoBotaoSair.setCharacterSize(30);
    textoBotaoSair.setFillColor(sf::Color::White);
}

void Jogo::processarEventosTelaFinal(sf::Event& evento) {
    if (evento.type == sf::Event::MouseButtonReleased) {
        if (evento.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = pGG->getWindow().mapPixelToCoords(sf::Vector2i(evento.mouseButton.x, evento.mouseButton.y));
            if (botaoSair.getGlobalBounds().contains(mousePos)) {
                pGG->fechar();
            }
        }
    }
    if (evento.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos = pGG->getWindow().mapPixelToCoords(sf::Vector2i(evento.mouseMove.x, evento.mouseMove.y));
        if (botaoSair.getGlobalBounds().contains(mousePos)) {
            botaoSair.setFillColor(sf::Color(200, 0, 0));
        }
        else {
            botaoSair.setFillColor(sf::Color(150, 0, 0));
        }
    }
}

void Jogo::desenharTelaFinal() {
    if (vitoria) {
        spriteTelaFinal.setTexture(texturaVitoria);
    }
    else if (derrota) {
        spriteTelaFinal.setTexture(texturaDerrota);
    }
    spriteTelaFinal.setScale(5.f, 5.f);

    sf::View view = pGG->getWindow().getView();
    sf::Vector2f centroView = view.getCenter();

    sf::FloatRect spriteBounds = spriteTelaFinal.getLocalBounds();
    spriteTelaFinal.setOrigin(spriteBounds.left + spriteBounds.width / 2.0f, spriteBounds.top + spriteBounds.height / 2.0f);
    spriteTelaFinal.setPosition(centroView.x, centroView.y - 50);

    sf::FloatRect botaoBounds = botaoSair.getLocalBounds();
    botaoSair.setOrigin(botaoBounds.left + botaoBounds.width / 2.0f, botaoBounds.top + botaoBounds.height / 2.0f);
    botaoSair.setPosition(centroView.x, spriteTelaFinal.getPosition().y + spriteBounds.height / 2.0f + 130.f);

    sf::FloatRect textoBotaoBounds = textoBotaoSair.getLocalBounds();
    textoBotaoSair.setOrigin(textoBotaoBounds.left + textoBotaoBounds.width / 2.0f, textoBotaoBounds.top + textoBotaoBounds.height / 2.0f);
    textoBotaoSair.setPosition(botaoSair.getPosition());

    pGG->getWindow().draw(spriteTelaFinal);
    pGG->desenha(botaoSair);
    pGG->getWindow().draw(textoBotaoSair);
}
void Jogo::executar() {
    GerenciadorColisoes* pGC = faseAtual->getGerenciadorColisoes();
    ListaEntidades* pListaEnts = faseAtual->getListaEntidades();

    while (pGG->estaAberta()) {
        sf::Event evento;
        while (pGG->getWindow().pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                pGG->fechar();
            }
            if (vitoria || derrota) {
                processarEventosTelaFinal(evento);
            }
        }

        if (!vitoria && !derrota) {
            if (jogador1 && jogador1->getVida() <= 0) {
                corpoMorto1.setSize(sf::Vector2f(64.f, 64.f));
                corpoMorto1.setTexture(&texturaJogador1Morto);
                corpoMorto1.setPosition(jogador1->getPosicao());
                pGC->removeEntidade(jogador1);
                delete jogador1; 
                jogador1 = nullptr;
                jogador1EstaMorto = true; 
            }

            if (jogador2 && jogador2->getVida() <= 0) {
                corpoMorto2.setSize(sf::Vector2f(64.f, 64.f));
                corpoMorto2.setTexture(&texturaJogador2Morto);
                corpoMorto2.setPosition(jogador2->getPosicao());
                pGC->removeEntidade(jogador2);
                delete jogador2; 
                jogador2 = nullptr;
                jogador2EstaMorto = true; 
            }

            if (!jogador1 && !jogador2) {
                derrota = true;
            }

            std::vector<Inimigo*> inimigos;
            Elemento<Entidade>* pElemento = pListaEnts->getPrimeiro();
            while (pElemento) {
                if (Inimigo* pInimigo = dynamic_cast<Inimigo*>(pElemento->getInfo())) {
                    inimigos.push_back(pInimigo);
                }
                pElemento = pElemento->getProx();
            }

            if (inimigos.empty()) {
                vitoria = true;
            }

            if (!vitoria && !derrota) { 
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    Elemento<Entidade>* pElementoEntidade = pListaEnts->getPrimeiro();
                    while (pElementoEntidade) {
                        pElementoEntidade->getInfo()->salvar();
                        pElementoEntidade = pElementoEntidade->getProx();
                    }
                    pGG->fechar();
                }

                if (jogador1) jogador1->mover();
                if (jogador2) jogador2->mover();

                for (auto* inimigo : inimigos) {
                    if (inimigo) inimigo->mover();
                }
                for (auto* inimigo : inimigos) {
                    if (Lancador* pLancador = dynamic_cast<Lancador*>(inimigo)) {
                        pLancador->atacar(jogador1, jogador2, 0.016f, pGG->getView(), pGC, pListaEnts);
                        
                    }
                }

                Elemento<Entidade>* pElementoProj = pListaEnts->getPrimeiro();
                while (pElementoProj) {
                    if (Projetil* pProj = dynamic_cast<Projetil*>(pElementoProj->getInfo())) {
                        if (pProj->getestaAtivo()) {
                            pProj->executar();
                        }
                    }
                    pElementoProj = pElementoProj->getProx();
                }

                Elemento<Entidade>* pElementoObs = pListaEnts->getPrimeiro();
                while (pElementoObs) {
                    Entidade* pEnt = pElementoObs->getInfo();
                    if (Obstaculo* pObs = dynamic_cast<Obstaculo*>(pEnt)) {
                        pObs->atualizarFisica();
                    }
                    pElementoObs = pElementoObs->getProx();
                }

                pGC->executar();

                std::vector<Entidade*> aRemover;
                Elemento<Entidade>* pEl = pListaEnts->getPrimeiro();
                while (pEl) {
                    Entidade* pEnt = pEl->getInfo();
                    bool remover = false;

                    if (Inimigo* pInimigo = dynamic_cast<Inimigo*>(pEnt)) {
                        if (pInimigo->getVida() <= 0) remover = true;
                    }
                    else if (Projetil* pProj = dynamic_cast<Projetil*>(pEnt)) {
                        if (!pProj->getestaAtivo()) remover = true;
                    }

                    if (remover) aRemover.push_back(pEnt);
                    pEl = pEl->getProx();
                }

                for (auto pEnt : aRemover) {
                    pGC->removeEntidade(pEnt);
                    pListaEnts->remover(pEnt);
                    delete pEnt;
                }
            }
        }

        sf::Vector2f mediaCamera(1920.f, 350.f); 
        if (jogador1 && jogador2) {
            mediaCamera = (jogador1->getRetangulo().getPosition() + jogador2->getRetangulo().getPosition()) / 2.f;
        }
        else if (jogador1) {
            mediaCamera = jogador1->getRetangulo().getPosition();
        }
        else if (jogador2) {
            mediaCamera = jogador2->getRetangulo().getPosition();
        }
        pGG->centralizarCamera(mediaCamera, 3840.f, 700.f);

        pGG->clear();
        pGG->desenhaFundo();
        pGG->desenhaChao();

        Elemento<Entidade>* pAux = pListaEnts->getPrimeiro();
        while (pAux) {
            if (pAux->getInfo()) {
                pAux->getInfo()->desenhar();
            }
            pAux = pAux->getProx();
        }
        if (jogador1EstaMorto) {
            pGG->desenha(corpoMorto1);
        }
        if (jogador2EstaMorto) {
            pGG->desenha(corpoMorto2);
        }

        if (jogador1) jogador1->desenhar();
        if (jogador2) jogador2->desenhar();

        pGG->atualizarBarraVida(jogador1 ? jogador1->getVida() : 0, 150, 1);
        pGG->atualizarBarraVida(jogador2 ? jogador2->getVida() : 0, 150, 2);
        pGG->desenharBV(2);

        if (vitoria || derrota) {
            desenharTelaFinal();
        }

        pGG->mostrar();
    }
}
void Jogo::setFaseAtual(int fase) {
    if (fase == 1) {
        faseAtual = new PrimeiraFase(jogador1, jogador2);
    }
    else if (fase == 2) {
        faseAtual = new SegundaFase(jogador1, jogador2);
    }
}