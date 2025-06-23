#include "jogo.h"
#include "primeira_fase.h"
#include "segunda_fase.h"
#include "inimigo.h"
#include "plataforma.h"
#include "aranha.h"
#include "espinho.h"
#include "agua.h"
#include "chefao.h"
#include "obstaculo.h"
#include "lancador.h"
#include "projetil.h"
#include "elemento.h"
#include <fstream>
#include <sstream>
#include <string>

int determinarFaseSalva() {
    std::ifstream arqChefao("arquivo_chefao.txt");
    if (arqChefao.good() && arqChefao.peek() != std::ifstream::traits_type::eof()) {
        return 2;
    }
    return 1;
}

Jogo::Jogo(int numJogadores) : pGG(new GerenciadorGrafico()), jogador1(nullptr), jogador2(nullptr), faseAtual(nullptr), numJogadores(numJogadores) {
    Ente::setGerenciadorGrafico(pGG);

    if (numJogadores >= 1) {
        jogador1 = new Jogador();
        jogador1->executar();
    }
    if (numJogadores == 2) {
        jogador2 = new Jogador();
        jogador2->executar();
    }

    pGG->inicializarBarraVida(numJogadores);
    vitoria = false;
    derrota = false;
    inicializarTelaFinal();
    inicializarMenuPausa();
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
            else if (jogoPausado) {
                processarEventosMenuPausa(evento);
                if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
                    jogoPausado = false; 
                }
            }
            else {
                if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
                    jogoPausado = true; // Pausa o jogo
                }
            }
        }

        if (!vitoria && !derrota && !jogoPausado) {

            // Verifica se os jogadores morreram
            if (jogador1 && jogador1->getVida() <= 0) {
                corpoMorto1.setSize(sf::Vector2f(64.f, 64.f));
                corpoMorto1.setTexture(&texturaJogador1Morto);
                corpoMorto1.setPosition(jogador1->getPosicao());
                pGC->removeEntidade(jogador1);
                pListaEnts->remover(jogador1);
                delete jogador1;
                jogador1 = nullptr;
                jogador1EstaMorto = true;
            }
            if (jogador2 && jogador2->getVida() <= 0) {
                corpoMorto2.setSize(sf::Vector2f(64.f, 64.f));
                corpoMorto2.setTexture(&texturaJogador2Morto);
                corpoMorto2.setPosition(jogador2->getPosicao());
                pGC->removeEntidade(jogador2);
                pListaEnts->remover(jogador2);
                delete jogador2;
                jogador2 = nullptr;
                jogador2EstaMorto = true;
            }

            // Verifica condi��o de derrota
            if (!jogador1 && !jogador2) {
                derrota = true;
            }

            // Verifica condi��o de vit�ria
            vector<Inimigo*> inimigos;
            Elemento<Entidade>* pElementoInim = pListaEnts->getPrimeiro();
            while (pElementoInim) {
                if (Inimigo* pInimigo = dynamic_cast<Inimigo*>(pElementoInim->getInfo())) {
                    inimigos.push_back(pInimigo);
                }
                pElementoInim = pElementoInim->getProx();
            }
            if (inimigos.empty() && faseAtual && faseAtual->getFase() > 0) {
                vitoria = true;
            }

            if (!vitoria && !derrota) {
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
                    if (Obstaculo* pObs = dynamic_cast<Obstaculo*>(pElementoObs->getInfo())) {
                        pObs->atualizarFisica();
                    }
                    pElementoObs = pElementoObs->getProx();
                }

                pGC->executar();

                // Remove entidades que precisam ser destru�das
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

        // Desenha todas as entidades da lista
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
        else if (jogoPausado) {
            desenharMenuPausa(); 
        }

        pGG->mostrar();
    }
}

void Jogo::rodarSave() {
    int faseId = determinarFaseSalva();
    setFaseAtual(faseId, true);

    GerenciadorColisoes* pGC = faseAtual->getGerenciadorColisoes();
    ListaEntidades* pListaEnts = faseAtual->getListaEntidades();

    std::ifstream arquivo;
    std::string linha;

    arquivo.open("arquivo_jogador.txt");
    if (arquivo.is_open()) {
        if (getline(arquivo, linha) && jogador1) {
            std::istringstream iss(linha);
            float grav, fMitico, vel, pulo, velBase, puloBase, x, y;
            bool fMiticoAtivo, noChao, olhando;
            int nVidas, vida, ataque, id_j;
            iss >> grav >> fMitico >> fMiticoAtivo >> nVidas >> vida >> vel >> noChao >> ataque >> id_j >> pulo >> olhando >> velBase >> puloBase >> x >> y;
            jogador1->setVida(vida);
            jogador1->setPosicao(x, y);
            pListaEnts->incluir(jogador1);
            pGC->inclueEntidade(jogador1);
        }
        if (getline(arquivo, linha) && jogador2) {
            std::istringstream iss(linha);
            float grav, fMitico, vel, pulo, velBase, puloBase, x, y;
            bool fMiticoAtivo, noChao, olhando;
            int nVidas, vida, ataque, id_j;
            iss >> grav >> fMitico >> fMiticoAtivo >> nVidas >> vida >> vel >> noChao >> ataque >> id_j >> pulo >> olhando >> velBase >> puloBase >> x >> y;
            jogador2->setVida(vida);
            jogador2->setPosicao(x, y);
            pListaEnts->incluir(jogador2);
            pGC->inclueEntidade(jogador2);
        }
        arquivo.close();
    }

    arquivo.open("arquivo_plataforma.txt");
    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            std::istringstream iss(linha);
            float grav, fMit, altura, velVert, x, y;
            bool fMitAtiva, danoso, gravAtiva;
            iss >> grav >> fMit >> fMitAtiva >> danoso >> gravAtiva >> altura >> velVert >> x >> y;
            Plataforma* p = new Plataforma();
            p->setarTexturaFase(faseId);
            p->setPosicao(x, y);
            p->setGravidadeAtiva(gravAtiva); 
            p->executar();
            pGC->inclueEntidade(p);
            pListaEnts->incluir(p);
        }
        arquivo.close();
    }

    arquivo.open("arquivo_aranha.txt");
    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            std::istringstream iss(linha);
            float grav, fMit, vel, dirX, x, y;
            bool fMitAtiva, noChao;
            int nVidas, vida, ataq, nMal;
            iss >> grav >> fMit >> fMitAtiva >> nVidas >> vida >> vel >> noChao >> ataq >> nMal >> dirX >> x >> y;
            Aranha* pAranha = new Aranha();
            pAranha->setGerenciadorGrafico(pGG);
            pAranha->setVida(vida);
            pAranha->setAtaque(ataq);
            pAranha->setPosicao(x, y);
            pAranha->executar();
            pGC->inclueEntidade(pAranha);
            pListaEnts->incluir(pAranha);
        }
        arquivo.close();
    }

    arquivo.open("arquivo_lancador.txt");
    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            std::istringstream iss(linha);
            float grav, fMit, vel, tempoAt, intervaloAt, x, y;
            bool fMitAtiva, noChao;
            int nVidas, vida, ataq, nMal, tamanho;
            iss >> grav >> fMit >> fMitAtiva >> nVidas >> vida >> vel >> noChao >> ataq >> nMal >> tamanho >> tempoAt >> intervaloAt >> x >> y;
            Lancador* pLancador = new Lancador();
            pLancador->setGerenciadorGrafico(pGG);
            pLancador->setVida(vida);
            pLancador->setAtaque(ataq);
            pLancador->setPosicao(x, y);
            pLancador->executar();
            pGC->inclueEntidade(pLancador);
            pListaEnts->incluir(pLancador);
        }
        arquivo.close();
    }

    arquivo.open("arquivo_chefao.txt");
    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            std::istringstream iss(linha);
            float grav, fMit, vel, posIniX, limEsq, limDir, x, y;
            bool fMitAtiva, noChao;
            int nVidas, vida, ataq, nMal;
            short int forca;
            iss >> grav >> fMit >> fMitAtiva >> nVidas >> vida >> vel >> noChao >> ataq >> nMal >> forca >> posIniX >> limEsq >> limDir >> x >> y;
            Chefao* pChefao = new Chefao();
            pChefao->setGerenciadorGrafico(pGG);
            pChefao->setVida(vida);
            pChefao->setAtaque(ataq);
            pChefao->setForca(forca);
            pChefao->setPosicao(x, y);
            pChefao->executar();
            pGC->inclueEntidade(pChefao);
            pListaEnts->incluir(pChefao);
        }
        arquivo.close();
    }

    arquivo.open("arquivo_agua.txt");
    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            std::istringstream iss(linha);
            float grav, fMit, largura, lentidao, x, y;
            bool fMitAtiva, danoso, gravAtiva;
            iss >> grav >> fMit >> fMitAtiva >> danoso >> gravAtiva >> largura >> lentidao >> x >> y;
            Agua* pAgua = new Agua();
            pAgua->setLentidao(lentidao);
            pAgua->setPosicao(x, y);
            pAgua->setGravidadeAtiva(gravAtiva); 
            pAgua->executar();
            pGC->inclueEntidade(pAgua);
            pListaEnts->incluir(pAgua);
        }
        arquivo.close();
    }

    arquivo.open("arquivo_espinho.txt");
    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            std::istringstream iss(linha);
            float grav, fMit, x, y;
            bool fMitAtiva, danoso, gravAtiva, elasticidade;
            iss >> grav >> fMit >> fMitAtiva >> danoso >> gravAtiva >> elasticidade >> x >> y;
            Espinho* pEspinho = new Espinho();
            pEspinho->setElasticidade(elasticidade);
            pEspinho->setPosicao(x, y);
            pEspinho->setGravidadeAtiva(gravAtiva); 
            pEspinho->executar();
            pGC->inclueEntidade(pEspinho);
            pListaEnts->incluir(pEspinho);
        }
        arquivo.close();
    }
    arquivo.open("arquivo_projetil.txt");
    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            std::istringstream iss(linha);
            float grav, fMit, velX, velY, dano, x, y;
            bool fMitAtiva, ativo;
            iss >> grav >> fMit >> fMitAtiva >> velX >> velY >> ativo >> dano >> x >> y;
            if (ativo) {
                Projetil* pProj = new Projetil();
                pProj->restaurar(sf::Vector2f(x, y), sf::Vector2f(velX, velY), ativo, dano, fMitAtiva);
                pGC->inclueEntidade(pProj);
                pListaEnts->incluir(pProj);
            }
        }
        arquivo.close();
    }

    executar();
}

void Jogo::setFaseAtual(int fase, bool carregarJogo) {
    if (faseAtual) {
        delete faseAtual;
        faseAtual = nullptr;
    }
    if (fase == 1) {
        faseAtual = new PrimeiraFase(jogador1, jogador2, carregarJogo);
    }
    else if (fase == 2) {
        faseAtual = new SegundaFase(jogador1, jogador2, carregarJogo);
    }
}
void Jogo::inicializarMenuPausa() {
    if (!fonteBotao.loadFromFile("fonteMenu.ttf")) {
        std::cerr << "Erro ao carregar fonteMenu.ttf para o menu de pausa." << std::endl;
        return;
    }

    fundoPausa.setSize(sf::Vector2f(pGG->getTamanhoJanelax(), pGG->getTamanhoJanelay()));
    fundoPausa.setFillColor(sf::Color(0, 0, 0, 150));

    textoPausa.setFont(fonteBotao);
    textoPausa.setString("JOGO PAUSADO");
    textoPausa.setCharacterSize(50);
    textoPausa.setFillColor(sf::Color::White);

    botaoSalvarSair.setSize(sf::Vector2f(300.f, 70.f));
    botaoSalvarSair.setFillColor(sf::Color(150, 0, 0));
    botaoSalvarSair.setOutlineColor(sf::Color::White);
    botaoSalvarSair.setOutlineThickness(2.f);

    textoBotaoSalvarSair.setFont(fonteBotao);
    textoBotaoSalvarSair.setString("Salvar e Sair");
    textoBotaoSalvarSair.setCharacterSize(25);
    textoBotaoSalvarSair.setFillColor(sf::Color::White);

    botaoSair.setSize(sf::Vector2f(300.f, 70.f));
    botaoSair.setFillColor(sf::Color(150, 0, 0));
    textoBotaoSair.setCharacterSize(30);
    textoBotaoSair.setString("Sair");
}
void Jogo::desenharMenuPausa() {
    sf::View view = pGG->getWindow().getView();
    sf::Vector2f centroView = view.getCenter();
    sf::Vector2f tamanhoView = view.getSize();

    fundoPausa.setSize(tamanhoView);
    fundoPausa.setOrigin(tamanhoView / 2.f);
    fundoPausa.setPosition(centroView);

    sf::FloatRect textoPausaBounds = textoPausa.getLocalBounds();
    textoPausa.setOrigin(textoPausaBounds.left + textoPausaBounds.width / 2.0f, textoPausaBounds.top + textoPausaBounds.height / 2.0f);
    textoPausa.setPosition(centroView.x, centroView.y - 150);

    sf::FloatRect botaoSalvarSairBounds = botaoSalvarSair.getLocalBounds();
    botaoSalvarSair.setOrigin(botaoSalvarSairBounds.width / 2.0f, botaoSalvarSairBounds.height / 2.0f);
    botaoSalvarSair.setPosition(centroView.x, centroView.y);

    sf::FloatRect textoBotaoSalvarSairBounds = textoBotaoSalvarSair.getLocalBounds();
    textoBotaoSalvarSair.setOrigin(textoBotaoSalvarSairBounds.left + textoBotaoSalvarSairBounds.width / 2.0f, textoBotaoSalvarSairBounds.top + textoBotaoSalvarSairBounds.height / 2.0f);
    textoBotaoSalvarSair.setPosition(botaoSalvarSair.getPosition());

    sf::FloatRect botaoSairBounds = botaoSair.getLocalBounds();
    botaoSair.setOrigin(botaoSairBounds.width / 2.0f, botaoSairBounds.height / 2.0f);
    botaoSair.setPosition(centroView.x, centroView.y + 100);

    sf::FloatRect textoBotaoSairBounds = textoBotaoSair.getLocalBounds();
    textoBotaoSair.setOrigin(textoBotaoSairBounds.left + textoBotaoSairBounds.width / 2.0f, textoBotaoSairBounds.top + textoBotaoSairBounds.height / 2.0f);
    textoBotaoSair.setPosition(botaoSair.getPosition());

    pGG->getWindow().setView(pGG->getWindow().getDefaultView()); 
    pGG->getWindow().draw(fundoPausa);
    pGG->getWindow().draw(textoPausa);
    pGG->desenha(botaoSalvarSair);
    pGG->getWindow().draw(textoBotaoSalvarSair);
    pGG->desenha(botaoSair);
    pGG->getWindow().draw(textoBotaoSair);
    pGG->getWindow().setView(view); 
}
void Jogo::processarEventosMenuPausa(sf::Event& evento) {
    if (evento.type == sf::Event::MouseButtonReleased) {
        if (evento.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = pGG->getWindow().mapPixelToCoords(sf::Vector2i(evento.mouseButton.x, evento.mouseButton.y), pGG->getWindow().getView());

            if (botaoSair.getGlobalBounds().contains(mousePos)) {
                pGG->fechar();
            }
            if (botaoSalvarSair.getGlobalBounds().contains(mousePos)) {
                // L�gica de salvar o jogo (copiada do seu c�digo original)
                std::ofstream arqJogadores("arquivo_jogador.txt", std::ios::trunc);
                std::ofstream arqAranhas("arquivo_aranha.txt", std::ios::trunc);
                std::ofstream arqLancadores("arquivo_lancador.txt", std::ios::trunc);
                std::ofstream arqChefoes("arquivo_chefao.txt", std::ios::trunc);
                std::ofstream arqPlataformas("arquivo_plataforma.txt", std::ios::trunc);
                std::ofstream arqAguas("arquivo_agua.txt", std::ios::trunc);
                std::ofstream arqEspinhos("arquivo_espinho.txt", std::ios::trunc);
                std::ofstream arqProjeteis("arquivo_projetil.txt", std::ios::trunc);

                Elemento<Entidade>* pElemento = faseAtual->getListaEntidades()->getPrimeiro();
                while (pElemento != nullptr) {
                    Entidade* pEnt = pElemento->getInfo();
                    if (pEnt) {
                        if (Jogador* p = dynamic_cast<Jogador*>(pEnt)) { p->salvar(arqJogadores); }
                        else if (Aranha* p = dynamic_cast<Aranha*>(pEnt)) { p->salvar(arqAranhas); }
                        else if (Lancador* p = dynamic_cast<Lancador*>(pEnt)) { p->salvar(arqLancadores); }
                        else if (Chefao* p = dynamic_cast<Chefao*>(pEnt)) { p->salvar(arqChefoes); }
                        else if (Plataforma* p = dynamic_cast<Plataforma*>(pEnt)) { p->salvar(arqPlataformas); }
                        else if (Agua* p = dynamic_cast<Agua*>(pEnt)) { p->salvar(arqAguas); }
                        else if (Espinho* p = dynamic_cast<Espinho*>(pEnt)) { p->salvar(arqEspinhos); }
                        else if (Projetil* p = dynamic_cast<Projetil*>(pEnt)) { p->salvar(arqProjeteis); }
                    }
                    pElemento = pElemento->getProx();
                }
                arqJogadores.close();
                arqAranhas.close();
                arqLancadores.close();
                arqChefoes.close();
                arqPlataformas.close();
                arqAguas.close();
                arqEspinhos.close();
                arqProjeteis.close();

                pGG->fechar();
            }
        }
    }
    if (evento.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos = pGG->getWindow().mapPixelToCoords(sf::Vector2i(evento.mouseMove.x, evento.mouseMove.y), pGG->getWindow().getView());
        if (botaoSair.getGlobalBounds().contains(mousePos)) {
            botaoSair.setFillColor(sf::Color(200, 0, 0));
        }
        else {
            botaoSair.setFillColor(sf::Color(150, 0, 0));
        }
        if (botaoSalvarSair.getGlobalBounds().contains(mousePos)) {
            botaoSalvarSair.setFillColor(sf::Color(200, 0, 0));
        }
        else {
            botaoSalvarSair.setFillColor(sf::Color(150, 0, 0));
        }
    }
}
