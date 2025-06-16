#pragma once
#include "obstaculo.h"
#include "jogador.h"

class ObstDificil : public Obstaculo {
private:
	bool elasticidade;
public:
	ObstDificil();
	~ObstDificil();
	void executar() ;
	void obstacular(Jogador* p) ;
	bool getElasticidade() const;
	void setElasticidade(bool e);
	void setId(int novoId) ;
	int getId() const ;
	void desenhar();
	void setForcaMitico(float forca) {
		forcaMitico = forca;
	};
	float getForcaMitico() const {
		return forcaMitico;
	};
	void atualizarFisica(float dt = 0.016f);
};
