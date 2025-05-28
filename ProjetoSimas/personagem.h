#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "entidade.h"

class Personagem : public Entidade {
protected:
	int num_vidas;
	float velocidade;
	sf::RectangleShape retangulo;
	sf::Texture textura;
	static int cont_personagem;
	int id_personagem;
public:
	Personagem();
	~Personagem();
	//void salvarDataBuffer();
	virtual void mover();
	virtual void executar() = 0;
	void desenhar(sf::RenderWindow& window);
	void carregarTextura(const std::string& caminho);
	void setPosicao(float x, float y, float janelax, float janelay);
	sf::Vector2f getPosicao() const;
	int getIdPersonagem() const;
};
