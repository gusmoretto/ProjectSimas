#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "gerenciador_grafico.h"
#include "gerenciador_colisoes.h"
#include "jogador.h"
#include "plataforma.h"
#include "inim_facil.h"
#include "inim_medio.h"
#include "obst_medio.h"
#include "projetil.h"

using namespace std;
using namespace Gerenciadores;

int main()
{
    srand(time(NULL));

    // --- Gerenciadores ---
    GerenciadorGrafico gerenciadorGrafico;
    GerenciadorColisoes gerenciadorColisoes;

    // --- Jogador ---
    Jogador jogador1;
    jogador1.setGerenciadorGrafico(&gerenciadorGrafico);
    jogador1.executar();
    gerenciadorColisoes.inclueEntidade(&jogador1);
    gerenciadorColisoes.setJogadores(&jogador1, nullptr);

    // --- Vetores de Entidades ---
    vector<Plataforma*> plataformas;
    vector<Obstaculo*> obstaculos;

    // --- Inicialização Gráfica ---
    gerenciadorGrafico.iniciaFundo("fundo1.png");
    gerenciadorGrafico.iniciaChao("chao.png", 3840.f, 300.f);

    // --- Carregar Plataformas do Arquivo ---
    int numPlataformasParaCriar = rand() % (41 - 38 + 1) + 38;
    std::ifstream arqPlataformas("coordPlataformas.txt");
    if (!arqPlataformas.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo de plataformas." << std::endl;
    }
    else {
        float x, y;
        for (int i = 0; i < numPlataformasParaCriar; ++i) {
            if (arqPlataformas >> x >> y) {
                Plataforma* p = new Plataforma();
                p->setPosicao(x, y);
                p->executar();
                gerenciadorColisoes.inclueEntidade(p);
                plataformas.push_back(p);
            }
            else {
                break;
            }
        }
        arqPlataformas.close();
    }
    int numInimigosFaceis = rand() % (5 - 3 + 1) + 3;
    std::ifstream arqAranhas("coordAranhas.txt");
    if (!arqAranhas.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo de aranhas." << std::endl;
    }
    else {
        float x, y;
        for (int i = 0; i < numInimigosFaceis; ++i) {
            if (arqAranhas >> x >> y) {
                InimFacil* pAranha = new InimFacil();
                pAranha->setGerenciadorGrafico(&gerenciadorGrafico);
                pAranha->setPosicao(x, y);
                pAranha->executar();
                gerenciadorColisoes.inclueEntidade(pAranha);
            }
            else {
                break;
            }
        }
        arqAranhas.close();
    }


    int numInimigosMedios = rand() % (4 - 3 + 1) + 3; 
    std::ifstream arqInimMedios("coordLancadores.txt"); 
    if (!arqInimMedios.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo de Lancadores." << std::endl;
    }
    else {
        float x, y;
        for (int i = 0; i < numInimigosMedios; ++i) {
            if (arqInimMedios >> x >> y) {
                InimMedio* pInimMedio = new InimMedio();
                pInimMedio->setGerenciadorGrafico(&gerenciadorGrafico);
                pInimMedio->setPosicao(x, y);
                pInimMedio->executar();
                gerenciadorColisoes.inclueEntidade(pInimMedio);
            }
            else {
                break;
            }
        }
        arqInimMedios.close();
    }

    ObstMedio* obstaculo1 = new ObstMedio();
    obstaculo1->setPosicao(768.f, 660.f);
    obstaculo1->executar();
    gerenciadorColisoes.inclueEntidade(obstaculo1);
    obstaculos.push_back(obstaculo1);

    ObstMedio* obstaculo2 = new ObstMedio();
    obstaculo2->setPosicao(832.f, 660.f);
    obstaculo2->executar();
    gerenciadorColisoes.inclueEntidade(obstaculo2);
    obstaculos.push_back(obstaculo2);
  
    ObstMedio* obstaculo3 = new ObstMedio();
    obstaculo3->setPosicao(704.f, 660.f);
    obstaculo3->executar();
    gerenciadorColisoes.inclueEntidade(obstaculo3);
    obstaculos.push_back(obstaculo3);
   
    ObstMedio* obstaculo4 = new ObstMedio();
    obstaculo4->setPosicao(896.f, 660.f);
    obstaculo4->executar();
    gerenciadorColisoes.inclueEntidade(obstaculo4);
    obstaculos.push_back(obstaculo4);

    // --- Loop Principal ---
    while (gerenciadorGrafico.estaAberta())
    {
        sf::Event evento;
        while (gerenciadorGrafico.getWindow().pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                gerenciadorGrafico.fechar();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            gerenciadorGrafico.fechar();
        }

        // --- Movimento ---
        jogador1.mover();

        for (auto* inimigo : gerenciadorColisoes.getInimigos()) {
            if (inimigo) inimigo->mover();
        }

        // --- Física ---
        for (auto* p : plataformas) {
            if (p) {
                p->setForcaMitico(-980.f);
                p->atualizarFisica(0.016f);
            }
        }
        for (auto* o : obstaculos) {
            if (o) {
                o->setForcaMitico(-980.f);
                o->atualizarFisica(0.016f);
            }
        }

        // --- Lógica de Ataque Generalizada para Inimigos Médios ---
        for (auto* inimigo : gerenciadorColisoes.getInimigos()) {
            if (inimigo) {
                // Tenta converter o ponteiro de Inimigo para InimMedio
                InimMedio* pInimMedio = dynamic_cast<InimMedio*>(inimigo);
                if (pInimMedio) {
                    // Se a conversão deu certo, chama o ataque
                    pInimMedio->atacar(&jogador1, nullptr, 0.016f, gerenciadorGrafico.getView(), &gerenciadorColisoes);
                    for (auto* proj : pInimMedio->getProjeteis()) {
                        if (proj && proj->getestaAtivo()) {
                            proj->executar();
                        }
                    }
                }
            }
        }

        // --- Colisões ---
        gerenciadorColisoes.executar();

        // --- Câmera ---
        gerenciadorGrafico.centralizarCamera(jogador1.getRetangulo().getPosition() + 0.5f * jogador1.getRetangulo().getSize(), 3840.f, 700.f);

        // --- Desenho ---
        gerenciadorGrafico.clear();
        gerenciadorGrafico.desenhaFundo();
        gerenciadorGrafico.desenhaChao();

        for (auto* p : plataformas) {
            if (p) p->desenhar();
        }
        for (auto* o : obstaculos) {
            if (o) o->desenhar();
        }
        for (auto* inimigo : gerenciadorColisoes.getInimigos()) {
            if (inimigo) inimigo->desenhar();
        }

        jogador1.desenhar();
        gerenciadorGrafico.mostrar();
    }

    auto inimigosVivos = gerenciadorColisoes.getInimigos();
    for (auto* inim : inimigosVivos) {
        delete inim;
    }

    for (auto* p : plataformas) {
        delete p;
    }
    for (auto* o : obstaculos) {
        delete o;
    }

    plataformas.clear();
    obstaculos.clear();

    return 0;
}