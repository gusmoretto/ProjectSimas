#include "fase.h"
#include "plataforma.h"
#include "aranha.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

Fase::Fase(Jogador* j1, Jogador* j2) : jogador1(j1), jogador2(j2) {
    srand(time(NULL));
    GC.setJogadores(jogador1, jogador2);
    if (jogador1) GC.inclueEntidade(jogador1);
    if (jogador2) GC.inclueEntidade(jogador2);
}

Fase::~Fase() {

}

void Fase::criarCenario(const std::string& fundo, const std::string& chao) {
    pGG->iniciaFundo(fundo);
    pGG->iniciaChao(chao, 3840.f, 300.f);
}

void Fase::criarPlataformas(const char* caminhoArquivo) {
    int numPlataformasParaCriar = rand() % (41 - 38 + 1) + 38; //
    std::ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo de plataformas: " << caminhoArquivo << std::endl; //
        return;
    }

    float x, y;
    for (int i = 0; i < numPlataformasParaCriar; ++i) {
        if (arquivo >> x >> y) {
            Plataforma* p = new Plataforma();
            p->setPosicao(x, y); //
            p->executar(); //
            GC.inclueEntidade(p); //
            lista_ents.incluir(dynamic_cast<Entidade*>(p));
        }
        else {
            break; //
        }
    }
    arquivo.close(); //
}

void Fase::criarAranhas(const char* caminhoArquivo) {
    int numInimigosFaceis = rand() % (5 - 3 + 1) + 3; //
    std::ifstream arquivo(caminhoArquivo);
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

void Fase::executar() {
    criarPlataformas("coordPlataformas.txt");
    criarAranhas("coordAranhas.txt");
    criarInimigos(); 
    criarObstaculos();
}

void Fase::setId(int novoId) {
    id = novoId;
}

int Fase::getId() const {
    return id;
}