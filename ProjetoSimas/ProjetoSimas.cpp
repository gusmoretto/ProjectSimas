#include <iostream>
#include "personagem.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "inim_facil.h"
#include "gerenciador_grafico.h"
#include "inim_medio.h"
#include "chefao.h" 
#include "entidade.h"
#include "ente.h"
using namespace Gerenciadores;


int main()
{
	GerenciadorGrafico gerenciadorGrafico;
    Jogador jogador1;
    jogador1.executar();
	InimFacil inimigo1;
	inimigo1.executar();
    

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
        
        inimigo1.mover();

		gerenciadorGrafico.clear();
        gerenciadorGrafico.desenhaFundo();
		gerenciadorGrafico.desenha(jogador1.getRetangulo());
        gerenciadorGrafico.desenha(inimigo1.getRetangulo());
		gerenciadorGrafico.mostrar();
    }

    return 0;
}