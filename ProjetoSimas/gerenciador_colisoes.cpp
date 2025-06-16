#include "gerenciador_colisoes.h"
#include "inim_facil.h"
#include "obst_medio.h"

namespace Gerenciadores {
	GerenciadorColisoes::GerenciadorColisoes() : jogador1(nullptr), jogador2(nullptr) {}
	GerenciadorColisoes::~GerenciadorColisoes() {
		lInimigos.clear();
		lObstaculos.clear();
		lProjetis.clear();
		jogador1 = nullptr;
		jogador2 = nullptr;
	}
    void GerenciadorColisoes::setJogadores(Jogador* j1, Jogador* j2) {
        jogador1 = j1;
        jogador2 = j2;
    }
    const int GerenciadorColisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const{
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

		// --- Lógica para o Jogador 1 ---
		if (jogador1) {
			bool jogador1_estaLentoPorObstMedioNesteFrame = false;

			for (auto obs : lObstaculos) {
				if (obs == nullptr) {
					continue; 
				}

				if (verificarColisao(jogador1, obs)) {
					obs->obstacular(jogador1);
					if (obs->getId() == 9) {
						ObstMedio* obstaculoMedio = dynamic_cast<ObstMedio*>(obs);
						if (obstaculoMedio) { 
							obstaculoMedio->obstacular(jogador1); 
							jogador1_estaLentoPorObstMedioNesteFrame = true; 
						}
					}
				}
			}
			if (!jogador1_estaLentoPorObstMedioNesteFrame) {
				jogador1->setVelocidade(jogador1->getVelocidadeBase());
			}
		}
		if (jogador2) {
			bool jogador2_estaLentoPorObstMedioNesteFrame = false;

			for (auto obs : lObstaculos) {
				if (obs == nullptr) {
					continue;
				}

				if (verificarColisao(jogador2, obs)) {
					obs->obstacular(jogador2); 

					if (obs->getId() == 9) {
						ObstMedio* obstaculoMedio = dynamic_cast<ObstMedio*>(obs);
						if (obstaculoMedio) {
							obstaculoMedio->obstacular(jogador2);
							jogador2_estaLentoPorObstMedioNesteFrame = true;
						}
					}
				}
			}

			if (!jogador2_estaLentoPorObstMedioNesteFrame) {
				jogador2->setVelocidade(jogador2->getVelocidadeBase());
			}
		}
	}

	void GerenciadorColisoes::verificaInim() {
		for (auto inim : lInimigos) {
			// Jogador 1
			if (jogador1) {
				int tipoColisao = verificarColisao(jogador1, inim);
				if (tipoColisao) {
					inim->tratarColisaoComJogador(jogador1, tipoColisao);

					// Impede que o jogador 1 fique dentro do inimigo
					sf::FloatRect areaInimigo = inim->getRetangulo().getGlobalBounds();
					sf::FloatRect areaJogador = jogador1->getRetangulo().getGlobalBounds();

					float sobreposicaoEsquerda = (areaJogador.left + areaJogador.width) - areaInimigo.left;
					float sobreposicaoDireita = (areaInimigo.left + areaInimigo.width) - areaJogador.left;
					float sobreposicaoCima = (areaJogador.top + areaJogador.height) - areaInimigo.top;
					float sobreposicaoBaixo = (areaInimigo.top + areaInimigo.height) - areaJogador.top;

					float menorSobreposicaoX = std::min(sobreposicaoEsquerda, sobreposicaoDireita);
					float menorSobreposicaoY = std::min(sobreposicaoCima, sobreposicaoBaixo);

					sf::Vector2f pos = jogador1->getRetangulo().getPosition();

					if (menorSobreposicaoX < menorSobreposicaoY) {
						if (sobreposicaoEsquerda < sobreposicaoDireita)
							pos.x = areaInimigo.left - areaJogador.width;
						else
							pos.x = areaInimigo.left + areaInimigo.width;
					}
					else {
						if (sobreposicaoCima < sobreposicaoBaixo)
							pos.y = areaInimigo.top - areaJogador.height;
						else
							pos.y = areaInimigo.top + areaInimigo.height;
					}
					jogador1->setPosicao(pos.x, pos.y);
				}
			}

			// Jogador 2
			if (jogador2) {
				int tipoColisao = verificarColisao(jogador2, inim);
				if (tipoColisao) {
					inim->tratarColisaoComJogador(jogador2, tipoColisao);

					// Impede que o jogador 2 fique dentro do inimigo
					sf::FloatRect areaInimigo = inim->getRetangulo().getGlobalBounds();
					sf::FloatRect areaJogador = jogador2->getRetangulo().getGlobalBounds();

					float sobreposicaoEsquerda = (areaJogador.left + areaJogador.width) - areaInimigo.left;
					float sobreposicaoDireita = (areaInimigo.left + areaInimigo.width) - areaJogador.left;
					float sobreposicaoCima = (areaJogador.top + areaJogador.height) - areaInimigo.top;
					float sobreposicaoBaixo = (areaInimigo.top + areaInimigo.height) - areaJogador.top;

					float menorSobreposicaoX = std::min(sobreposicaoEsquerda, sobreposicaoDireita);
					float menorSobreposicaoY = std::min(sobreposicaoCima, sobreposicaoBaixo);

					sf::Vector2f pos = jogador2->getRetangulo().getPosition();

					if (menorSobreposicaoX < menorSobreposicaoY) {
						if (sobreposicaoEsquerda < sobreposicaoDireita)
							pos.x = areaInimigo.left - areaJogador.width;
						else
							pos.x = areaInimigo.left + areaInimigo.width;
					}
					else {
						if (sobreposicaoCima < sobreposicaoBaixo)
							pos.y = areaInimigo.top - areaJogador.height;
						else
							pos.y = areaInimigo.top + areaInimigo.height;
					}
					jogador2->setPosicao(pos.x, pos.y);
				}
			}
		}
		auto it = lInimigos.begin();
		while (it != lInimigos.end()) {
			if ((*it)->getVida() <= 0) {
				delete* it;
				(*it) = nullptr;
				it = lInimigos.erase(it);
			}
			else {
				++it;
			}
		}
	}


	void GerenciadorColisoes::verificaProjetil() {
		for (auto proj : lProjetis) {
			// Colisão com jogadores
			if (jogador1 && verificarColisao(proj, jogador1)) {
				jogador1->setVida(jogador1->getVida() - 10); // Exemplo de dano
				proj->setAtivo(false); // Ou remova do jogo
			}
			if (jogador2 && verificarColisao(proj, jogador2)) {
				jogador2->setVida(jogador2->getVida() - 10);
				proj->setAtivo(false);
			}
			// Colisão com inimigos (se projetil do jogador)
			for (auto inim : lInimigos) {
				if (verificarColisao(proj, inim)) {
					proj->setAtivo(false);
				}
			}
		}
	}
	void GerenciadorColisoes::verificaObsInim() {
		for (auto inim : lInimigos) {
			if (!inim) continue; // Garante que o ponteiro do inimigo não é nulo

			for (auto obs : lObstaculos) {
				if (!obs) continue; // Garante que o ponteiro do obstáculo não é nulo

				int tipoColisao = verificarColisao(inim, obs);
				if (tipoColisao != 0) { // Se houver colisão
					sf::FloatRect areaInimigo = inim->getRetangulo().getGlobalBounds();
					sf::FloatRect areaObs = obs->getRetangulo().getGlobalBounds();
					sf::Vector2f posInimigo = inim->getRetangulo().getPosition(); // Pega a posição ATUAL do inimigo

					switch (tipoColisao) {
					case 1: // Inimigo colidiu por CIMA do obstáculo (caiu sobre ele)
						posInimigo.y = areaObs.top - areaInimigo.height;
						// inim->setVelocidadeVertical(0.f); // Zera velocidade de queda
						// inim->noChao(true); // Indica que o inimigo está no chão
						break;
					case 2: // Inimigo colidiu pela ESQUERDA do obstáculo
						posInimigo.x = areaObs.left - areaInimigo.width;
						// inim->setVelocidadeX(0.f); // Zera velocidade horizontal
						break;
					case 3: // Inimigo colidiu pela DIREITA do obstáculo
						posInimigo.x = areaObs.left + areaObs.width;
						// inim->setVelocidadeX(0.f); // Zera velocidade horizontal
						break;
					case 4: // Inimigo colidiu por BAIXO do obstáculo (cabeça no teto)
						posInimigo.y = areaObs.top + areaObs.height;
						// inim->setVelocidadeVertical(0.f); // Zera velocidade de subida
						break;
					}
					inim->setPosicao(posInimigo.x, posInimigo.y);
					if (inim->getId() == 3) { 
						InimFacil* inimigoFacil = dynamic_cast<InimFacil*>(inim);
						if (inimigoFacil) {
							if (tipoColisao == 2 || tipoColisao == 3) { 
								inimigoFacil->virarDirecao(); 
							}
						}
					}
				}
			}
		}
	}

	void GerenciadorColisoes::verificaObsProjetil() {
		for (auto proj : lProjetis) {
			if (!proj->getestaAtivo())
				continue;
			for (auto obs : lObstaculos) {
				if (verificarColisao(proj, obs)) {
					proj->setAtivo(false); // Desativa o projetil ao colidir
					break; // Não precisa checar outros obstáculos
				}
			}
		}
		
		for (auto it = lProjetis.begin(); it != lProjetis.end(); ) {
			Projetil* proj = *it;
			if (!proj->getestaAtivo()) {
				it = lProjetis.erase(it);
			}
			else {
				++it;
			}
		}
	}
	bool GerenciadorColisoes::projetilExiste(const Projetil* p) const {
		return lProjetis.find(const_cast<Projetil*>(p)) != lProjetis.end();
	}

	void GerenciadorColisoes::executar() {
		verificaObs();
		verificaInim();
		verificaProjetil();
		verificaObsInim();
		verificaObsProjetil();
	}
}

