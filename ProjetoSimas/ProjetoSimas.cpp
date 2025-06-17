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
#include "obst_medio.h"
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
    Plataforma* p7 = new Plataforma();
    Plataforma* p8 = new Plataforma();
    Plataforma* p9 = new Plataforma();
    Plataforma* p10 = new Plataforma();
    Plataforma* p11 = new Plataforma();
    Plataforma* p12 = new Plataforma();
    Plataforma* p13 = new Plataforma();
    Plataforma* p14 = new Plataforma();
    Plataforma* p15 = new Plataforma();
    Plataforma* p16 = new Plataforma();
    Plataforma* p17 = new Plataforma();
    Plataforma* p18 = new Plataforma();
    Plataforma* p19 = new Plataforma();
    Plataforma* p20 = new Plataforma();
    Plataforma* p21 = new Plataforma();


	ObstMedio* obstaculo1 = new ObstMedio();
	ObstMedio* obstaculo2 = new ObstMedio();

    Jogador jogador1;
    jogador1.executar();
    jogador1.setGerenciadorGrafico(&gerenciadorGrafico);

    InimFacil* inimigo1 = new InimFacil();
    inimigo1->executar();
    inimigo1->setGerenciadorGrafico(&gerenciadorGrafico);

    InimMedio* inimigo2 = new InimMedio();
    inimigo2->executar();
    inimigo2->setGerenciadorGrafico(&gerenciadorGrafico);

	gerenciadorGrafico.iniciaFundo("fundo1.png");
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
	plataformas.push_back(p7);
	plataformas.push_back(p8);
	plataformas.push_back(p9);
	plataformas.push_back(p10);
	plataformas.push_back(p11);
	plataformas.push_back(p12);
	plataformas.push_back(p13);
	plataformas.push_back(p14);
	plataformas.push_back(p15);
    plataformas.push_back(p16);
    plataformas.push_back(p17);
    plataformas.push_back(p18);
    plataformas.push_back(p19);
    plataformas.push_back(p20);
    plataformas.push_back(p21);



    p1->setPosicao(128.f, 478.f);
    p2->setPosicao(192.f, 478.f);
    p3->setPosicao(256.f, 478.f);
    p4->setPosicao(320.f, 478.f);
	
    p5->setPosicao(640.f, 542.f);
	p6->setPosicao(640.f, 670.f);

	p7->setPosicao(960.f, 670.f);
	p8->setPosicao(1024.f, 670.f);
	p9->setPosicao(1024.f, 542.f);
	p10->setPosicao(1088.f, 670.f);
	p11->setPosicao(1088.f, 542.f);
	p12->setPosicao(1088.f, 478.f);
	p13->setPosicao(1152.f, 478.f);
	p14->setPosicao(1216.f, 478.f);
	p15->setPosicao(1280.f, 478.f);
    p16->setPosicao(1536.f, 670.f);
    p17->setPosicao(1664.f, 670.f);
    p18->setPosicao(1664.f, 542.f);
    p19->setPosicao(1792.f, 478.f);
    p20->setPosicao(1856.f, 478.f);
    p21->setPosicao(1920.f, 478.f);


	obstaculo1->setPosicao(768.f, 660.f);
	obstaculo2->setPosicao(832.f, 660.f);

	obstaculo1->executar();
    gerenciadorColisoes.inclueEntidade(obstaculo1);
	obstaculo2->executar();
    gerenciadorColisoes.inclueEntidade(obstaculo2);

    for (auto& plataforma : plataformas) {
        plataforma->executar();
        gerenciadorColisoes.inclueEntidade(plataforma);
    }

    inimigo2->setPosicao(190.f, 400.f);

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
		obstaculo1->setForcaMitico(-980.f);
		obstaculo1->atualizarFisica(0.016f);
		obstaculo2->setForcaMitico(-980.f);
		obstaculo2->atualizarFisica(0.016f);

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

        if (inimigo2 != nullptr) {
            inimigo2->atacar(&jogador1, nullptr, 0.016f, viewatual, &gerenciadorColisoes);
            for (auto& proj : inimigo2->getProjeteis()) { 
                if (proj->getestaAtivo()) {
                    proj->executar();
                }
            }
        }

        gerenciadorGrafico.clear();
        gerenciadorGrafico.desenhaFundo();
        gerenciadorGrafico.desenhaChao();
        for (auto& plataforma : plataformas) {
            if (plataforma)
                plataforma->desenhar();
        }
		if (obstaculo1 != nullptr)
			obstaculo1->desenhar();
		if (obstaculo2 != nullptr)
			obstaculo2->desenhar();
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
