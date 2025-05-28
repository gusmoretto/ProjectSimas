#pragma once
#include <SFML/Graphics.hpp>

class Projetil {
private:
	sf::CircleShape circulo;
	sf::Vector2f direcao;
	sf::Texture textura;
	const float raio;

public:
	Projetil(const sf::Vector2f& pos, const sf::Vector2f& target, float speed = 300.f); // Default argument remains here
	~Projetil();
	void update(float deltaTime);
	void desenhar(sf::RenderWindow& window);
	sf::Vector2f getPosicao() const;
	void carregarTextura(const std::string& caminho);
};
