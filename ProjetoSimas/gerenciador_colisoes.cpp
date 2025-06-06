#include "gerenciador_colisoes.h"

namespace Gerenciadores {
	GerenciadorColisoes::GerenciadorColisoes() : jogador1(nullptr), jogador2(nullptr) {}
	GerenciadorColisoes::~GerenciadorColisoes() {
		lObstaculos.clear();
		lInimigos.clear();
		lProjetis.clear();
		jogador1 = nullptr;
		jogador2 = nullptr;
	}
    void GerenciadorColisoes::setJogador1(Jogador* j1, Jogador* j2) {
        jogador1 = j1;
        jogador2 = j2;
    }
    int GerenciadorColisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const {
        if (!pe1 || !pe2)
            return 0;

        sf::FloatRect ent1 = pe1->getRetangulo().getGlobalBounds();
        sf::FloatRect ent2 = pe2->getRetangulo().getGlobalBounds();

        if (!ent1.intersects(ent2))
            return 0; 

        float sobreposicaoEsquerda = (ent1.left + ent1.width) - ent2.left;
        float sobreposicaoDireita = (ent2.left + ent2.width) - ent1.left;
        float sobreposicaoCima = (ent1.top + ent1.height) - ent2.top;
        float sobreposicaoBaixo = (ent2.top + ent2.height) - ent1.top;

        float menorSobreposicaoX = std::min(sobreposicaoEsquerda, sobreposicaoDireita);
        float menorSobreposicaoY = std::min(sobreposicaoCima, sobreposicaoBaixo);

        if (menorSobreposicaoX < menorSobreposicaoY) {
            if (sobreposicaoEsquerda < sobreposicaoDireita)
                return 2; 
            else
                return 3; 
        }
        else {
            if (sobreposicaoCima < sobreposicaoBaixo)
                return 1; 
            else
                return 4; 
        }
    }
}
