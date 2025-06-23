#include "gerenciador_colisoes.h"
#include "aranha.h"
#include "agua.h"
#include <iostream>

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
		if (jogador1) {
			bool jogador1_estaLentoPorAguaNesteFrame = false;

			for (auto obs : lObstaculos) {
				if (obs == nullptr) {
					continue; 
				}
				int tipoColisao = verificarColisao(jogador1, obs);
				if (tipoColisao) {
					obs->obstacular(jogador1, tipoColisao);
					if (obs->getId() == 9) {
						Agua* obstaculoMedio = dynamic_cast<Agua*>(obs);
						if (obstaculoMedio) { 
							obs->obstacular(jogador1, tipoColisao);
							jogador1_estaLentoPorAguaNesteFrame = true; 
						}
					}
				}
			}
			if (!jogador1_estaLentoPorAguaNesteFrame) {
				jogador1->setPulo(jogador1->getPuloBase());
				jogador1->setVelocidade(jogador1->getVelocidadeBase());
			}
		}
		if (jogador2) {
			bool jogador2_estaLentoPorAguaNesteFrame = false;

			for (auto obs : lObstaculos) {
				if (obs == nullptr) {
					continue;
				}
				int tipoColisao = verificarColisao(jogador2, obs);
				if (tipoColisao) {
					obs->obstacular(jogador2, tipoColisao);

					if (obs->getId() == 9) {
						Agua* obstaculoMedio = dynamic_cast<Agua*>(obs);
						if (obstaculoMedio) {
							obs->obstacular(jogador2, tipoColisao);
							jogador2_estaLentoPorAguaNesteFrame = true;
						}
					}
				}
			}

			if (!jogador2_estaLentoPorAguaNesteFrame) {
				jogador2->setPulo(jogador2->getPuloBase());
				jogador2->setVelocidade(jogador2->getVelocidadeBase());
			}
		}
	}

	void Gerenciadores::GerenciadorColisoes::verificaInim() {
		for (auto inim : lInimigos) {
			if (jogador1) {
				int tipoColisao = verificarColisao(jogador1, inim);
				if (tipoColisao) {
					int vidaInimigoAntesColisao = inim->getVida();

					inim->tratarColisaoComJogador(jogador1, tipoColisao);

					bool inimigoFoiMortoPorCima = (inim->getVida() <= 0 && vidaInimigoAntesColisao > 0 && tipoColisao == 1);

					if (inimigoFoiMortoPorCima) {
    jogador1->adicionarPontos(100); // ajuste o valor conforme desejar
}
					sf::FloatRect areaInimigo = inim->getRetangulo().getGlobalBounds();
					sf::FloatRect areaJogador = jogador1->getRetangulo().getGlobalBounds();

					float dx = (areaJogador.left + areaJogador.width / 2) - (areaInimigo.left + areaInimigo.width / 2);
					float dy = (areaJogador.top + areaJogador.height / 2) - (areaInimigo.top + areaInimigo.height / 2);

					float intersectX = std::min(areaJogador.left + areaJogador.width, areaInimigo.left + areaInimigo.width) - std::max(areaJogador.left, areaInimigo.left);
					float intersectY = std::min(areaJogador.top + areaJogador.height, areaInimigo.top + areaInimigo.height) - std::max(areaJogador.top, areaInimigo.top);

					sf::Vector2f pos = jogador1->getRetangulo().getPosition();

					if (intersectX < intersectY) { 
						if (dx > 0) {
							pos.x = areaInimigo.left + areaInimigo.width;
						}
						else { 
							pos.x = areaInimigo.left - areaJogador.width;
						}
						if (Aranha* pAranha = dynamic_cast<Aranha*>(inim)) {
							pAranha->virarDirecao();
							sf::Vector2f posAranha = pAranha->getPosicao();
							pAranha->setPosicao(posAranha.x + (dx > 0 ? -pAranha->getVelocidade() * 0.05f : pAranha->getVelocidade() * 0.05f), posAranha.y);
						}
					}
					else { 
						if (dy > 0) { 
							pos.y = areaInimigo.top + areaInimigo.height;
							jogador1->setVelocidadeVertical(0.f);
						}
						else { 
							pos.y = areaInimigo.top - areaJogador.height;
							if (!inimigoFoiMortoPorCima) { 
								jogador1->setVelocidadeVertical(0.f);
							}
							jogador1->setNoChao(true);
						}
					}
					jogador1->setPosicao(pos.x, pos.y);
				}
			}
			if (jogador2) {
				int tipoColisao = verificarColisao(jogador2, inim);
				if (tipoColisao) {
					int vidaInimigoAntesColisao = inim->getVida();

					inim->tratarColisaoComJogador(jogador2, tipoColisao);

					bool inimigoFoiMortoPorCima = (inim->getVida() <= 0 && vidaInimigoAntesColisao > 0 && tipoColisao == 1);
					sf::FloatRect areaInimigo = inim->getRetangulo().getGlobalBounds();
					sf::FloatRect areaJogador = jogador2->getRetangulo().getGlobalBounds();

					float dx = (areaJogador.left + areaJogador.width / 2) - (areaInimigo.left + areaInimigo.width / 2);
					float dy = (areaJogador.top + areaJogador.height / 2) - (areaInimigo.top + areaInimigo.height / 2);

					float intersectX = std::min(areaJogador.left + areaJogador.width, areaInimigo.left + areaInimigo.width) - std::max(areaJogador.left, areaInimigo.left);
					float intersectY = std::min(areaJogador.top + areaJogador.height, areaInimigo.top + areaInimigo.height) - std::max(areaJogador.top, areaInimigo.top);

					sf::Vector2f pos = jogador2->getRetangulo().getPosition();

					if (intersectX < intersectY) {
						if (dx > 0) {
							pos.x = areaInimigo.left + areaInimigo.width;
						}
						else {
							pos.x = areaInimigo.left - areaJogador.width;
						}
						if (Aranha* pAranha = dynamic_cast<Aranha*>(inim)) {
							pAranha->virarDirecao();
							sf::Vector2f posAranha = pAranha->getPosicao();
							pAranha->setPosicao(posAranha.x + (dx > 0 ? -pAranha->getVelocidade() * 0.05f : pAranha->getVelocidade() * 0.05f), posAranha.y);
						}
					}
					else {
						if (dy > 0) {
							pos.y = areaInimigo.top + areaInimigo.height;
							jogador2->setVelocidadeVertical(0.f);
						}
						else {
							pos.y = areaInimigo.top - areaJogador.height;
							if (!inimigoFoiMortoPorCima) {
								jogador2->setVelocidadeVertical(0.f);
							}
							jogador2->setNoChao(true);
						}
					}
					jogador2->setPosicao(pos.x, pos.y);
				}
			}
		}
	}

	void GerenciadorColisoes::verificaProjetil() {
		for (auto proj : lProjetis) {
			if (jogador1 && verificarColisao(proj, jogador1)) {
				jogador1->setVida(jogador1->getVida() - 10); 
				proj->setAtivo(false); 
			}
			if (jogador2 && verificarColisao(proj, jogador2)) {
				jogador2->setVida(jogador2->getVida() - 10);
				proj->setAtivo(false);
			}
		}
	}
	void GerenciadorColisoes::verificaObsInim() {
		for (auto inim : lInimigos) {
			if (!inim) continue;

			bool estaApoiado = false;

			for (auto obs : lObstaculos) {
				if (!obs) continue;

				sf::FloatRect areaInimigo = inim->getRetangulo().getGlobalBounds();
				sf::FloatRect areaObs = obs->getRetangulo().getGlobalBounds();

				bool x_overlap = areaInimigo.left < areaObs.left + areaObs.width &&
					areaInimigo.left + areaInimigo.width > areaObs.left;

				bool y_overlap_support = areaInimigo.top + areaInimigo.height >= areaObs.top &&
					areaInimigo.top < areaObs.top;

				if (x_overlap && y_overlap_support && inim->getVelocidadeVertical() >= 0) {
					inim->setPosicao(areaInimigo.left, areaObs.top - areaInimigo.height);
					inim->setVelocidadeVertical(0.f);
					estaApoiado = true;
					break;
				}
			}
			inim->setNoChao(estaApoiado);

			for (auto obs : lObstaculos) {
				if (!obs) continue;

				int tipoColisao = verificarColisao(inim, obs);

				if (tipoColisao == 2 || tipoColisao == 3) {
					if (Aranha* pAranha = dynamic_cast<Aranha*>(inim)) {
						pAranha->virarDirecao();
						sf::Vector2f pos = pAranha->getPosicao();
						pAranha->setPosicao(pos.x + (tipoColisao == 2 ? -1.f : 1.f), pos.y);
					}
				}
				else if (tipoColisao == 4) { 
					if (inim->getVelocidadeVertical() < 0) {
						inim->setVelocidadeVertical(0.f);
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
					proj->setAtivo(false); 
					break; 
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

	void GerenciadorColisoes::executar() {
		verificaObs();
		verificaInim();
		verificaProjetil();
		verificaObsInim();
		verificaObsProjetil();
	}
}

