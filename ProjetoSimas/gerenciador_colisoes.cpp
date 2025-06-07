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
    void GerenciadorColisoes::setJogadores(Jogador* j1, Jogador* j2) {
        jogador1 = j1;
        jogador2 = j2;
    }
    int GerenciadorColisoes::verificarColisao(Entidade* pe1, Entidade* pe2) {
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
	void GerenciadorColisoes::inclueEntidade(Entidade* ent) {
		if (ent->getId() == 1 || ent->getId() == 2) {
			if (jogador1 == nullptr) {
				jogador1 = dynamic_cast<Jogador*>(ent);
			}
			else if (jogador2 == nullptr) {
				jogador2 = dynamic_cast<Jogador*>(ent);
			}
		}
		else if (ent->getId() >= 3 && ent->getId() <= 5) {
			Inimigo* inimigo = dynamic_cast<Inimigo*>(ent);
			if (inimigo) {
				lInimigos.push_back(inimigo);
			}
		}
		else if (ent->getId() >= 7 && ent->getId() <= 10) {
			Obstaculo* obstaculo = dynamic_cast<Obstaculo*>(ent);
			if (obstaculo) {
				lObstaculos.push_back(obstaculo);
			}
		}
		else if (ent->getId() == 6) {
			Projetil* projetil = dynamic_cast<Projetil*>(ent);
			if (projetil) {
				lProjetis.insert(projetil);
			}
		}
	}
	void GerenciadorColisoes::removeEntidade(Entidade* ent) {
		if (ent->getId() == 1 || ent->getId() == 2) {
			if (jogador1 == ent) {
				jogador1 = nullptr;
			}
			else if (jogador2 == ent) {
				jogador2 = nullptr;
			}
		}
		else if (ent->getId() >= 3 && ent->getId() <= 5) {
			Inimigo* inimigo = dynamic_cast<Inimigo*>(ent);
			if (inimigo) {
				lInimigos.erase(std::remove(lInimigos.begin(), lInimigos.end(), inimigo), lInimigos.end());
			}
		}
		else if (ent->getId() >= 7 && ent->getId() <= 10) {
			Obstaculo* obstaculo = dynamic_cast<Obstaculo*>(ent);
			if (obstaculo) {
				lObstaculos.remove(obstaculo);
			}
		}
		else if (ent->getId() == 6) {
			Projetil* projetil = dynamic_cast<Projetil*>(ent);
			if (projetil) {
				lProjetis.erase(projetil);
			}
		}
	}
	void GerenciadorColisoes::verificaObs() {
		for (auto obs : lObstaculos) {
			if (jogador1 && verificarColisao(jogador1, obs))
				obs->obstacular(jogador1); // ou trate a colisão conforme sua lógica
			if (jogador2 && verificarColisao(jogador2, obs))
				obs->obstacular(jogador2);
		}
	}
	void GerenciadorColisoes::verificaInim() {
		for (auto inim : lInimigos) {
			if (jogador1 && verificarColisao(jogador1, inim))
				inim->danificar(jogador1);
			if (jogador2 && verificarColisao(jogador2, inim))
				inim->danificar(jogador2);
		}
	}
	void GerenciadorColisoes::verificaProjetil() {
		for (auto proj : lProjetis) {
			for (auto inim : lInimigos) {
				if (verificarColisao(proj, inim)) {
					// Trate dano ao inimigo, remova projétil, etc.
				}
			}
			if (jogador1 && verificarColisao(proj, jogador1)) {
				// Trate dano ao jogador, remova projétil, etc.
			}
			if (jogador2 && verificarColisao(proj, jogador2)) {
				// Trate dano ao jogador, remova projétil, etc.
			}
		}
	}
	void GerenciadorColisoes::verificaObsInim() {
		for (auto inim : lInimigos) {
			for (auto obs : lObstaculos) {
				if (verificarColisao(inim, obs)) {
					// Trate a colisão (ex: parar movimento, rebater, etc.)
				}
			}
		}
	}
	void GerenciadorColisoes::verificaObsProjetil() {
		for (auto proj : lProjetis) {
			for (auto obs : lObstaculos) {
				if (verificarColisao(proj, obs)) {
					// Remova projétil, trate efeito, etc.
				}
			}
		}
	}
}
