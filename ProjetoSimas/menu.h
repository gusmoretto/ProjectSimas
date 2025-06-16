#pragma onceJ
#include "ente.h"
#include "jogo.h"

class Menu : public Ente {
private:
	Jogo* pJogo;

public:
	Menu();
	~Menu();
	void executar();
};
