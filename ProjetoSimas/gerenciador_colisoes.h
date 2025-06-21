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
		void setJogadores(Jogador* j1, Jogador* j2);
		void inclueEntidade(Entidade* ent);
		void removeEntidade(Entidade* ent);
		const int verificarColisao(Entidade* pe1, Entidade* pe2) const;
		void verificaObs();
		void verificaInim();
		void verificaProjetil();
		void verificaObsInim();
		void verificaObsProjetil();
		void executar();
	};
}
