#include "segunda_fase.h"
#include "chefao.h"
#include "agua.h"
#include "espinho.h"
#include <fstream>
#include <iostream>

SegundaFase::SegundaFase(Jogador* j1, Jogador* j2) : Fase(j1, j2), maxEspinhos(5), maxChefoes(3) {
	fase = 2;
	criarCenario(fase);
	Fase::executar();
}
SegundaFase::~SegundaFase() {}

void SegundaFase::criarInimigos() {
	int numChefoes = rand() % (maxChefoes - 3 + 1) + 3; 
	std::ifstream arqChefoes("coordChefoes.txt");
	if (!arqChefoes.is_open()) {
		std::cerr << "Erro: Nao foi possivel abrir o arquivo de Chefes." << std::endl;
		return;
	}
	float x, y;
	for (int i = 0; i < numChefoes; ++i) {
		if (arqChefoes >> x >> y) {
			Chefao* pChefao = new Chefao();
			pChefao->setGerenciadorGrafico(pGG);
			pChefao->setPosicao(x, y);
			pChefao->executar();
			GC.inclueEntidade(pChefao);
			lista_ents.incluir(dynamic_cast<Entidade*>(pChefao));
		}
		else {
			break;
		}
	}
	arqChefoes.close();
}