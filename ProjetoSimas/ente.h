#pragma once
#include <SFML/Graphics.hpp>

class Ente {
protected:
	int id;
	//static Gerenciador_Grafico* pGG;
	//Figura* pFig;
public:
	Ente();
	virtual ~Ente();
	//virtual void desenhar(sf::RenderWindow& window) = 0;
	virtual void executar() = 0;
};
