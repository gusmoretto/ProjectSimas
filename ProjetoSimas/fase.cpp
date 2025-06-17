#include "fase.h"
#include "plataforma.h" 
#include "inim_facil.h"
#include <fstream>      
#include <iostream>     
#include <cstdlib>      
#include <ctime> 

Fase::Fase() {
    srand(time(NULL));
}
Fase::~Fase() {}

void Fase::criarCenario() {
	pGG->iniciaFundo("fundo.png");
	pGG->iniciaChao("chao.png", 3840.f, 300.f);
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
void Fase::criarinimFaceis(const std::string& nomeArquivo) {
    int numInimigosParaCriar = rand() % (5 - 3 + 1) + 3; 

    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo de coordenadas de aranhas: " << nomeArquivo << std::endl;
        return;
    }
    float x, y;
    for (int i = 0; i < numInimigosParaCriar; ++i) {
        if (arquivo >> x >> y) {
            InimFacil* pAranha = new InimFacil();
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
	criarPlataformas("coordPlataformas.txt");
	criarinimFaceis("coordInimigos.txt");
	criarObstaculos();
	criarInimigos();
	GC.executar();
}