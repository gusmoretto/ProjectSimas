#pragma once
#include "ente.h"
#include "jogo.h"

class Menu : public Ente {
private:
	Jogo* pJogo;

public:
	Menu();
	~Menu();
	void executar() override;
	void setId(int novoId) override;
	int getId() const override;
};