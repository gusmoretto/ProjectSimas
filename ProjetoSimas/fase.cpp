#include "fase.h"
#include "plataforma.h" 
#include "aranha.h"
#include <fstream>      
#include <iostream>     
#include <cstdlib>      
#include <ctime> 

Fase::Fase() {
    srand(time(NULL));
}
Fase::~Fase() {}

void Fase::criarCenario(int fase) {
    if (fase == 1) {
        pGG->iniciaFundo("fundo1.png");
        pGG->iniciaChao("chao.png", 3840.f, 300.f);
    }
    else
        pGG->iniciaFundo("fundo2.png");
        pGG->iniciaChao("chao2.png", 3840.f, 300.f);

}
void Fase::criarPlataformas(const std::string& nomeArquivo) {
    int numPlataformasParaCriar = rand() % (41 - 38 + 1) + 38; 

    std::ifstream arquivo("coordPlataformas.txt");
    if (!arquivo.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo de plataformas: " << nomeArquivo << std::endl;
        return;
    }

    float x, y;
    for (int i = 0; i < numPlataformasParaCriar; ++i) {
        if (arquivo >> x >> y) {
            Plataforma* p = new Plataforma();
            p->setPosicao(x, y);
            p->executar(); 
            GC.inclueEntidade(p); 
        }
        else {
            std::cerr << "Aviso: Fim do arquivo de plataformas alcancado antes de criar "
                << numPlataformasParaCriar << " plataformas. Criadas: " << i << std::endl;
            break;
        }
    }
    arquivo.close();
}
void Fase::criarAranhas(const std::string& nomeArquivo) {
    int numInimigosParaCriar = rand() % (5 - 3 + 1) + 3; 

    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo de coordenadas de aranhas: " << nomeArquivo << std::endl;
        return;
    }
    float x, y;
    for (int i = 0; i < numInimigosParaCriar; ++i) {
        if (arquivo >> x >> y) {
            Aranha* pAranha = new Aranha();
            pAranha->setPosicao(x, y);
            pAranha->executar(); 

            GC.inclueEntidade(pAranha); 
            lista_ents.incluir(pAranha); 
        }
        else {
            std::cerr << "Aviso: Fim do arquivo de aranhas alcancado antes de criar "
                << numInimigosParaCriar << " inimigos. Criados: " << i << std::endl;
            break;
        }
    }
    arquivo.close();
}
void Fase::executar() {
	criarCenario();
	criarObstaculos();
	criarInimigos();
}