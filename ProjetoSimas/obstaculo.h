#pragma once
#include "entidade.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Obstaculo : public Entidade {
private:
	sf::RectangleShape retangulo;
	sf::Texture textura;
protected:
	bool danoso;
public:
	Obstaculo();
	~Obstaculo();
	virtual void executar() = 0;
	virtual void obstacular() = 0; 
	void desenhar(sf::RenderWindow& window);
	void carregarTextura(const std::string& caminho);
	void setPosicao(float janelax, float janelay);
	sf::Vector2f getPosicao() const;
	const sf::RectangleShape& getRetangulo() const;
};	