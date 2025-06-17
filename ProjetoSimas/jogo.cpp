#include "jogo.h"
#include "primeira_fase.h"
#include "inimigo.h"
#include "obstaculo.h"
#include "lancador.h"
#include "projetil.h"
#include "elemento.h"

Jogo::Jogo() : pGG(new GerenciadorGrafico()), jogador1(nullptr), faseAtual(nullptr) {
    Ente::setGerenciadorGrafico(pGG);
    jogador1 = new Jogador();
    jogador1->executar();
    faseAtual = new PrimeiraFase(jogador1, nullptr);
}

Jogo::~Jogo() {
    if (faseAtual) delete faseAtual;
    if (pGG) delete pGG;
}
void Jogo::executar() {
    GerenciadorColisoes* pGC = faseAtual->getGerenciadorColisoes();
    const std::vector<Inimigo*>& inimigos = pGC->getInimigos();
    ListaEntidades* pListaEnts = faseAtual->getListaEntidades(); // Ponteiro para a lista

    while (pGG->estaAberta()) {
        sf::Event evento;
        while (pGG->getWindow().pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                pGG->fechar();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            pGG->fechar();
        }

        jogador1->mover();
        for (auto* inimigo : inimigos) {
            if (inimigo) inimigo->mover();
        }
        for (auto* inimigo : inimigos) {
            if (Lancador* pLancador = dynamic_cast<Lancador*>(inimigo)) {
                pLancador->atacar(jogador1, nullptr, 0.016f, pGG->getView(), pGC, pListaEnts);
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
        
        Elemento<Entidade>* pElemento = pListaEnts->getPrimeiro();
        while (pElemento) {
            Entidade* pEnt = pElemento->getInfo();
            if (Obstaculo* pObs = dynamic_cast<Obstaculo*>(pEnt)) {
                pObs->atualizarFisica();
            }
            pElemento = pElemento->getProx();
        }

        pGC->executar();

        std::vector<Entidade*> aRemover;
        Elemento<Entidade>* pEl = pListaEnts->getPrimeiro();
        while (pEl) {
            Entidade* pEnt = pEl->getInfo();
            bool remover = false;

            if (Inimigo* pInimigo = dynamic_cast<Inimigo*>(pEnt)) {
                if (pInimigo->getVida() <= 0) {
                    remover = true;
                }
            }
        
            else if (Projetil* pProj = dynamic_cast<Projetil*>(pEnt)) {
                if (!pProj->getestaAtivo()) {
                    remover = true;
                }
            }

            if (remover) {
                aRemover.push_back(pEnt);
            }
            pEl = pEl->getProx();
        }
        for (auto pEnt : aRemover) {
            pGC->removeEntidade(pEnt);      
            pListaEnts->remover(pEnt);       
            delete pEnt;                     
        }

        pGG->centralizarCamera(jogador1->getRetangulo().getPosition(), 3840.f, 700.f);
        pGG->clear();
        pGG->desenhaFundo();
        pGG->desenhaChao();

        Elemento<Entidade>* pAux = pListaEnts->getPrimeiro();
        while (pAux) {
            if (pAux->getInfo()) {
                pAux->getInfo()->desenhar();
            }
            pAux = pAux->getProx();
        }
        jogador1->desenhar();

        pGG->mostrar();
    }
}
