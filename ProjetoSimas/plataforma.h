#pragma once
#include "obstaculo.h"
#include "jogador.h"

class Plataforma : public Obstaculo {
private:
	int altura;
	float velocidadeVertical;

public:
	Plataforma();
	~Plataforma();
	void executar();
	void salvar();
	void obstacular(Jogador* p);
	void desenhar();
	void setId(int novoId);
	int getId() const;
	void setForcaMitico(float forca);
	float getForcaMitico() const;
	void atualizarFisica(float dt = 0.016f);
	void setarTexturaFase(int fase);
};
