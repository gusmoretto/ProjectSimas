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
	void salvar(std::ostream& os);
	void obstacular(Jogador* p, int tipoColisao = 0);
	void desenhar();
	void setId(int novoId);
	int getId() const;
	void setForcaMitico(float forca);
	float getForcaMitico() const;
	void atualizarFisica(float dt = 0.016f);
	void setarTexturaFase(int fase);
};
