#include "fase.h"
#include "plataforma.h"
#include "aranha.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

Fase::Fase(Jogador* j1, Jogador* j2, bool carregarJogo) : jogador1(j1), jogador2(j2), fase(0) {
    srand(time(NULL));
    GC.setJogadores(jogador1, jogador2);
}

Fase::~Fase() {

}

void Fase::criarCenario(int fase) {
    if (fase == 1) {
        pGG->iniciaFundo("fundo1.png");
        pGG->iniciaChao("chao.png", 3840.f, 300.f);
    }
    else if (fase == 2) {
        pGG->iniciaFundo("fundo2.png");
        pGG->iniciaChao("chao2.png", 3840.f, 300.f);
    }
    else {
        std::cerr << "Fase invalida!" << std::endl;
    }
}

void Fase::criarPlataformas(int fase) {
    if (fase == 1) {
        int numPlataformasParaCriar = rand() % (41 - 38 + 1) + 38;
        std::ifstream arquivo("coordPlataformas.txt");
        if (!arquivo.is_open()) {
            std::cerr << "Erro: Nao foi possivel abrir o arquivo de plataformas: " << "plataformas.txt" << std::endl;
            return;
        }

        float x, y;
        for (int i = 0; i < numPlataformasParaCriar; ++i) {
            if (arquivo >> x >> y) {
                Plataforma* p = new Plataforma();
                p->setPosicao(x, y);
                p->executar();
                p->setarTexturaFase(fase);
                GC.inclueEntidade(p);
                lista_ents.incluir(dynamic_cast<Entidade*>(p));
            }
            else {
                break;
            }
        }
        arquivo.close();
    }
    else if (fase == 2) {
        int numPlataformasParaCriar = rand() % (41 - 38 + 1) + 38;
        if (numPlataformasParaCriar == 40) numPlataformasParaCriar = 39;
        std::ifstream arquivo("coordPlataformas2.txt");
        if (!arquivo.is_open()) {
            std::cerr << "Erro: Nao foi possivel abrir o arquivo de plataformas: " << "plataformas2.txt" << std::endl;
            return;
        }

        float x, y;
        for (int i = 0; i < numPlataformasParaCriar; ++i) {
            if (arquivo >> x >> y) {
                Plataforma* p = new Plataforma();
                p->setPosicao(x, y);
                p->executar();
                p->setarTexturaFase(fase);
                GC.inclueEntidade(p);
                lista_ents.incluir(dynamic_cast<Entidade*>(p));
            }
            else {
                break;
            }
        }
        arquivo.close();
    }
}

void Fase::criarAranhas(int fase) {
    if (fase == 1) {
        int numInimigosFaceis = rand() % (5 - 3 + 1) + 3; //
        std::ifstream arquivo("coordAranhas.txt");
        if (!arquivo.is_open()) {
            std::cerr << "Erro: Nao foi possivel abrir o arquivo de aranhas." << std::endl; //
            return;
        }
        float x, y;
        for (int i = 0; i < numInimigosFaceis; ++i) {
            if (arquivo >> x >> y) {
                Aranha* pAranha = new Aranha();
                pAranha->setGerenciadorGrafico(pGG); //
                pAranha->setPosicao(x, y); //
                pAranha->executar(); //
                GC.inclueEntidade(pAranha); //
                lista_ents.incluir(dynamic_cast<Entidade*>(pAranha));
            }
            else {
                break;
            }
        }
        arquivo.close();
    }
    else if (fase == 2) {
        int numInimigosFaceis = rand() % (3 - 3 + 1) + 3; //
        std::ifstream arquivo("coordAranhas2.txt");
        if (!arquivo.is_open()) {
            std::cerr << "Erro: Nao foi possivel abrir o arquivo de aranhas." << std::endl; //
            return;
        }
        float x, y;
        for (int i = 0; i < numInimigosFaceis; ++i) {
            if (arquivo >> x >> y) {
                Aranha* pAranha = new Aranha();
                pAranha->setGerenciadorGrafico(pGG); //
                pAranha->setPosicao(x, y); //
                pAranha->executar(); //
                GC.inclueEntidade(pAranha); //
                lista_ents.incluir(dynamic_cast<Entidade*>(pAranha));
            }
            else {
                break;
            }
        }
        arquivo.close();
    }
}

void Fase::executar() {
    criarPlataformas(getFase());
    criarAranhas(getFase());
    criarInimigos();
    criarObstaculos();
}