#include <iostream>
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
using namespace Gerenciadores;

int main()
{
	GerenciadorGrafico gerenciadorGrafico;
    Jogador jogador1;
    jogador1.executar();
	jogador1.setGerenciadorGrafico(&gerenciadorGrafico);
	InimFacil inimigo1;
	inimigo1.executar();
    inimigo1.setGerenciadorGrafico(&gerenciadorGrafico);
	gerenciadorGrafico.iniciaChao("chao.png", 3840.f, 300.f);

    while (gerenciadorGrafico.estaAberta())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            gerenciadorGrafico.fechar();

		float janelax = gerenciadorGrafico.getTamanhoJanelax();
        float janelay = gerenciadorGrafico.getTamanhoJanelay();

        sf::Vector2f posInimigo1 = inimigo1.getPosicao();
        sf::Vector2f posJogador1 = jogador1.getPosicao();

        float dx = posJogador1.x - posInimigo1.x;
        float dy = posJogador1.y - posInimigo1.y;  

		jogador1.mover();

        gerenciadorGrafico.centralizarCamera(
        jogador1.getRetangulo().getPosition() + 0.5f * jogador1.getRetangulo().getSize(), 3840.f, 700.f);
        inimigo1.mover();

		gerenciadorGrafico.clear();
        gerenciadorGrafico.desenhaFundo();
		gerenciadorGrafico.desenhaChao();
		jogador1.desenhar();
        inimigo1.desenhar();
		gerenciadorGrafico.mostrar();
    }

    return 0;
}