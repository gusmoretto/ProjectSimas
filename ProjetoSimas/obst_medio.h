#pragma once
#include "obstaculo.h"
#include "jogador.h"

class ObstMedio : public Obstaculo {
private:
	float largura;
	float lentidao;

public:
	ObstMedio();
	~ObstMedio();
	void executar();
	void obstacular(Jogador* p);
	float getLargura() const;
	void setLargura(float l);
	float getLentidao() const;
	void setLentidao(float lent);
	void setId(int novoId);
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
