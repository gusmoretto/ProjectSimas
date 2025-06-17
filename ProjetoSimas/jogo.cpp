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
                pLancador->atacar(jogador1, nullptr, 0.016f, pGG->getView(), pGC);
                for (auto* proj : pLancador->getProjeteis()) {
                    if (proj && proj->getestaAtivo()) {
                        proj->executar();
                    }
                }
            }
        }
        pGC->executar();
        pGG->centralizarCamera(jogador1->getRetangulo().getPosition(), 3840.f, 700.f);
        pGG->clear();
        pGG->desenhaFundo();
        pGG->desenhaChao();

        Elemento<Entidade>* pAux = faseAtual->getListaEntidades()->getPrimeiro();
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

int main()
{
    Jogo jogoPrincipal;
    jogoPrincipal.executar();
    return 0;
}