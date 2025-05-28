#include "projetil.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Projetil::Projetil(const sf::Vector2f& pos, const sf::Vector2f& target, float speed) : raio(100.f) { // Remove default argument here
	circulo.setRadius(raio);
	this->direcao = direcao;
	circulo.setPosition(pos);

	sf::Vector2f vetorDirecao = target - pos;
	float comprimento = std::sqrt(vetorDirecao.x * vetorDirecao.x + vetorDirecao.y * vetorDirecao.y);
	if (comprimento != 0) {
		direcao = vetorDirecao / comprimento; // Normaliza o vetor direção
	}
	else {
		direcao = sf::Vector2f(0.f, 0.f); // Se a direção for zero, não se move
	}
	direcao = vetorDirecao * (speed / comprimento); // Ajusta a direção para a velocidade desejada
}
Projetil::~Projetil() {
	// Destrutor vazio, pois não há recursos alocados dinamicamente
}
void Projetil::update(float deltaTime) {
	circulo.move(direcao * deltaTime);
}
void Projetil::desenhar(sf::RenderWindow& window) {
	window.draw(circulo);
}
sf::Vector2f Projetil::getPosicao() const {
	return circulo.getPosition();
}
void Projetil::carregarTextura(const std::string& caminho) {
	if (!textura.loadFromFile(caminho)) {
		std::cerr << "Erro ao carregar a textura: " << caminho << std::endl;
	}
	circulo.setTexture(&textura);
}

