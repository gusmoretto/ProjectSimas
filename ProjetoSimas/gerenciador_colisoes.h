#pragma once
#include "inimigo.h"
#include "jogador.h"
#include "obstaculo.h"
#include "projetil.h"
#include <vector>
#include <list>
#include <set>
using namespace std;
namespace Gerenciadores {
	class GerenciadorColisoes {
	private:
		vector<Inimigo*> lInimigos;
		list<Obstaculo*> lObstaculos;
		set<Projetil*> lProjetis;
		Jogador* jogador1;
		Jogador* jogador2;

	public:
		GerenciadorColisoes();
		~GerenciadorColisoes();
		void setJogador1(Jogador* j1, Jogador* j2);
		int verificarColisao(Entidade* pe1, Entidade* pe2) const;
		void tratarColisoesJogsObstaculos();
		void tratarColisoesJogsInimigos();
		void tratarColisoesJogsProjeteis();
		void incluirInimigo(Inimigo* inimigo) {
			lInimigos.push_back(inimigo);
		};
		void incluirObstaculo(Obstaculo* obstaculo) {
			lObstaculos.push_back(obstaculo);
		};
		void incluirProjetil(Projetil* projetil) {
			lProjetis.insert(projetil);
		};
		void executar() {
			tratarColisoesJogsObstaculos();
			tratarColisoesJogsInimigos();
			tratarColisoesJogsProjeteis();
		};
	};
}
