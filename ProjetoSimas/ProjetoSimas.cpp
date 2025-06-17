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
    // Inicializa a semente para números aleatórios uma única vez
    srand(time(NULL));

    // --- Gerenciadores ---
    GerenciadorGrafico gerenciadorGrafico;
    GerenciadorColisoes gerenciadorColisoes;

    // --- Entidades ---
    Jogador jogador1;
    jogador1.setGerenciadorGrafico(&gerenciadorGrafico);
    jogador1.executar();
    gerenciadorColisoes.inclueEntidade(&jogador1);

    // Inimigo especial com ataque de projétil
    InimMedio* inimigo2 = new InimMedio();
    inimigo2->setGerenciadorGrafico(&gerenciadorGrafico);
    inimigo2->executar();
    inimigo2->setPosicao(190.f, 400.f);
    gerenciadorColisoes.inclueEntidade(inimigo2);

    gerenciadorColisoes.setJogadores(&jogador1, nullptr);

    // --- Vetores para gerenciar a memória ---
    vector<Plataforma*> plataformas;
    vector<Obstaculo*> obstaculos;

    // --- Cenário ---
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
                break; // Fim do arquivo
            }
        }
        arqPlataformas.close();
    }

    // --- Carregar Inimigos Fáceis (Aranhas) do Arquivo ---
    int numInimigosParaCriar = rand() % (5 - 3 + 1) + 3;
    std::ifstream arqAranhas("coordAranhas.txt");
    if (!arqAranhas.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo de aranhas." << std::endl;
    }
    else {
        float x, y;
        for (int i = 0; i < numInimigosParaCriar; ++i) {
            if (arqAranhas >> x >> y) {
                InimFacil* pAranha = new InimFacil();
                pAranha->setGerenciadorGrafico(&gerenciadorGrafico);
                pAranha->setPosicao(x, y);
                pAranha->executar();
                gerenciadorColisoes.inclueEntidade(pAranha);
            }
            else {
                break; // Fim do arquivo
            }
        }
        arqAranhas.close();
    }

    // --- Carregar Obstáculos ---
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


    // ===================================================================
    //                          LOOP PRINCIPAL
    // ===================================================================
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

        // --- Atualização da Física e Movimento ---

        jogador1.mover();

        // Move todos os inimigos da lista do gerenciador de colisões
        for (auto* inimigo : gerenciadorColisoes.getInimigos()) {
            if (inimigo) inimigo->mover();
        }

        // CORREÇÃO: Física das plataformas com gravidade neutralizada
        for (auto* p : plataformas) {
            if (p) {
                p->setForcaMitico(-980.f); // Neutraliza a gravidade
                p->atualizarFisica(0.016f);
            }
        }

        // Física dos obstáculos (eles caem normalmente)
        for (auto* o : obstaculos) {
            if (o) {
                o->atualizarFisica(0.016f);
            }
        }

        // --- Lógica de Ataque ---
        bool inimigo2AindaExiste = false;
        for (auto* inim : gerenciadorColisoes.getInimigos()) {
            if (inim == inimigo2) {
                inimigo2AindaExiste = true;
                break;
            }
        }
        if (!inimigo2AindaExiste) {
            inimigo2 = nullptr; // Define como nulo para não ser mais usado
        }

        if (inimigo2 != nullptr) {
            inimigo2->atacar(&jogador1, nullptr, 0.016f, gerenciadorGrafico.getView(), &gerenciadorColisoes);
            for (auto* proj : inimigo2->getProjeteis()) {
                if (proj->getestaAtivo()) {
                    proj->executar();
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

    // ===================================================================
    //                      LIMPEZA DE MEMÓRIA
    // ===================================================================

    // O Gerenciador de Colisões já deleta os inimigos quando a vida deles acaba.
    // Os ponteiros restantes na lista dele são os que sobraram vivos.
    // O ideal seria o Gerenciador de Colisões limpar sua própria lista no destrutor,
    // mas como ele não faz, limpamos a memória dos sobreviventes aqui.
    auto inimigosVivos = gerenciadorColisoes.getInimigos();
    for (auto* inim : inimigosVivos) {
        // O inimigo2 já está nesta lista, então não precisa de delete separado.
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