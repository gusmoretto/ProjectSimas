#pragma once
#include "obstaculo.h"
#include "jogador.h"

class Agua : public Obstaculo {
private:
	float largura;
	float lentidao;

public:
	Agua();
	~Agua();
	void executar();
	void salvar();
	void obstacular(Jogador* p, int tipoColisao = 0);
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
