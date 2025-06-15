#include <iostream>
#include <vector>
#include "personagem.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "inim_facil.h"
#include "inim_medio.h"
#include "chefao.h" 
#include "entidade.h"
#include "ente.h"
#include "gerenciador_grafico.h"
#include "gerenciador_colisoes.h"
#include "plataforma.h"
using namespace std;
using namespace Gerenciadores;

int main()
{
    GerenciadorColisoes gerenciadorColisoes;
    GerenciadorGrafico gerenciadorGrafico;

    vector<Plataforma*> plataformas;
    Plataforma* p1 = new Plataforma();
    Plataforma* p2 = new Plataforma();
    Plataforma* p3 = new Plataforma();
    Plataforma* p4 = new Plataforma();
    Plataforma* p5 = new Plataforma();
    Plataforma* p6 = new Plataforma();

    Jogador jogador1;
    jogador1.executar();
    jogador1.setGerenciadorGrafico(&gerenciadorGrafico);

    InimFacil* inimigo1 = new InimFacil();
    inimigo1->executar();
    inimigo1->setGerenciadorGrafico(&gerenciadorGrafico);

    InimMedio* inimigo2 = new InimMedio();
    inimigo2->executar();
    inimigo2->setGerenciadorGrafico(&gerenciadorGrafico);

    gerenciadorGrafico.iniciaChao("chao.png", 3840.f, 300.f);

    gerenciadorColisoes.inclueEntidade(&jogador1);
    gerenciadorColisoes.inclueEntidade(inimigo1);
    gerenciadorColisoes.inclueEntidade(inimigo2);

    gerenciadorColisoes.setJogadores(&jogador1, nullptr);

    plataformas.push_back(p1);
    plataformas.push_back(p2);
    plataformas.push_back(p3);
    plataformas.push_back(p4);
	plataformas.push_back(p5);
	plataformas.push_back(p6);

    p1->setPosicao(128.f, 478.f);
    p2->setPosicao(192.f, 478.f);
    p3->setPosicao(256.f, 478.f);
    p4->setPosicao(320.f, 478.f);
	
    p5->setPosicao(640.f, 542.f);
	p6->setPosicao(640.f, 670.f);

    for (auto& plataforma : plataformas) {
        plataforma->executar();
        gerenciadorColisoes.inclueEntidade(plataforma);
    }

    inimigo2->setPosicao(320.f, 0.f);

    while (gerenciadorGrafico.estaAberta())
    {
        View& viewatual = gerenciadorGrafico.getView();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            gerenciadorGrafico.fechar();
            for (auto* plataforma : plataformas) {
                delete plataforma;
            }
            plataformas.clear();
            break;
        }

        for (auto& plataforma : plataformas) {
            plataforma->setForcaMitico(-980.f);
            plataforma->atualizarFisica(0.016f);
        }

        float janelax = gerenciadorGrafico.getTamanhoJanelax();
        float janelay = gerenciadorGrafico.getTamanhoJanelay();

        // Só acesse métodos de inimigo1 se ele for válido!
        sf::Vector2f posInimigo1;
        if (inimigo1 != nullptr)
            posInimigo1 = inimigo1->getPosicao();
        sf::Vector2f posJogador1 = jogador1.getPosicao();

        float dx = 0, dy = 0;
        if (inimigo1 != nullptr) {
            dx = posJogador1.x - posInimigo1.x;
            dy = posJogador1.y - posInimigo1.y;
        }

        jogador1.mover();
        gerenciadorGrafico.centralizarCamera(jogador1.getRetangulo().getPosition() + 0.5f * jogador1.getRetangulo().getSize(), 3840.f, 700.f);
        if (inimigo1 != nullptr)
            inimigo1->mover();
        if (inimigo2 != nullptr)
            inimigo2->mover();

        gerenciadorColisoes.executar();

        bool inimigo1AindaExiste = false;
        for (auto inim : gerenciadorColisoes.getInimigos()) {
            if (inim == inimigo1) {
                inimigo1AindaExiste = true;
                break;
            }
        }
        if (!inimigo1AindaExiste) {
            inimigo1 = nullptr;
        }
        bool inimigo2AindaExiste = false;
        for (auto inim : gerenciadorColisoes.getInimigos()) {
            if (inim == inimigo2) {
                inimigo2AindaExiste = true;
                break;
            }
        }
        if (!inimigo2AindaExiste) {
            inimigo2 = nullptr;
        }

        if (inimigo2 != nullptr)
            inimigo2->atacar(&jogador1, nullptr, 0.016f, viewatual, &gerenciadorColisoes);

        gerenciadorGrafico.clear();
        gerenciadorGrafico.desenhaFundo();
        gerenciadorGrafico.desenhaChao();
        for (auto& plataforma : plataformas) {
            if (plataforma)
                plataforma->desenhar();
        }
        jogador1.desenhar();
        if (inimigo1 != nullptr)
            inimigo1->desenhar();
        if (inimigo2 != nullptr)
            inimigo2->desenhar();
        gerenciadorGrafico.mostrar();

    }
    for (auto* plataforma : plataformas) {
        delete plataforma;
    }
    return 0;
}
