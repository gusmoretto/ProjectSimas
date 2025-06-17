#include "primeira_fase.h"
#include "lancador.h"
#include "agua.h"
#include <fstream>
#include <iostream>

PrimeiraFase::PrimeiraFase(Jogador* j1, Jogador* j2) : Fase(j1, j2) , maxLancadores(4), maxAguas(12){
    criarCenario("fundo1.png", "chao.png");
    Fase::executar();
}

PrimeiraFase::~PrimeiraFase() {}

void PrimeiraFase::criarInimigos() {
    int numInimigosMedios = rand() % (maxLancadores - 3 + 1) + 3; //
    std::ifstream arqLancadores("coordLancadores.txt");
    if (!arqLancadores.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo de Lancadores." << std::endl; //
        return;
    }
    float x, y;
    for (int i = 0; i < numInimigosMedios; ++i) {
        if (arqLancadores >> x >> y) {
            Lancador* pLancador = new Lancador();
            pLancador->setGerenciadorGrafico(pGG); //
            pLancador->setPosicao(x, y); //
            pLancador->executar(); //
            GC.inclueEntidade(pLancador); //
            lista_ents.incluir(dynamic_cast<Entidade*>(pLancador));
        }
        else {
            break; //
        }
    }
    arqLancadores.close(); //
}

void PrimeiraFase::criarObstaculos() {
    int numObstaculosMedios = rand() % (maxAguas - 10 + 1) + 10; //
    std::ifstream arqAguas("coordAguas.txt");
    if (!arqAguas.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo de aguas." << std::endl; //
        return;
    }
    float x, y;
    if (numObstaculosMedios == 11) numObstaculosMedios = 10; //
    for (int i = 0; i < numObstaculosMedios; ++i) {
        if (arqAguas >> x >> y) {
            Agua* pAgua = new Agua();
            pAgua->setPosicao(x, y); //
            pAgua->executar(); //
            GC.inclueEntidade(pAgua); //
            lista_ents.incluir(dynamic_cast<Entidade*>(pAgua));
        }
        else {
            break; //
        }
    }
    arqAguas.close(); //
}