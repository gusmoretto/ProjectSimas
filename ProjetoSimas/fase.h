#pragma once
#include "ente.h"
#include "lista_entidades.h"
#include "gerenciador_colisoes.h"

class Fase : public Ente {
protected:
	ListaEntidades lista_ents;
	Gerenciadores::GerenciadorColisoes GC;
	
protected:
	void criarAranhas(const std::string& nomeArquivo);
	void criarPlataformas(const std::string& nomeArquivo);
	virtual void criarInimigos() = 0;
	virtual void criarObstaculos() = 0;
	void criarCenario(int fase);

public:
	Fase();
	~Fase();
	virtual void executar();

};
