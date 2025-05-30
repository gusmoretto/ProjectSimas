#include "obstaculo.h"
#include <iostream>
#include "entidade.h"
#include <SFML/Graphics.hpp>

Obstaculo::Obstaculo() : Entidade(), danoso(false) {
	retangulo.setSize(sf::Vector2f(100.f, 100.f)); // Tamanho padrão do obstáculo
}
Obstaculo::~Obstaculo() {
	std::cout << "Destrutor de Obstaculo chamado." << std::endl;
}
void Obstaculo::executar() {
	std::cout << "Executando Obstaculo." << std::endl;
}
void Obstaculo::obstacular() {
	std::cout << "Obstáculo ativo." << std::endl;
}
void Obstaculo::desenhar(sf::RenderWindow& window) {
	window.draw(retangulo);
}
void Obstaculo::carregarTextura(const std::string& caminho) {
	if (!textura.loadFromFile(caminho)) {
		std::cerr << "Erro ao carregar a textura: " << caminho << std::endl;
	}
	retangulo.setTexture(&textura);
}
void Obstaculo::setPosicao(float janelax, float janelay) {
	//ainda pensando como fazer a posicao do obstaculo, a principio ele seria fixo
}
sf::Vector2f Obstaculo::getPosicao() const {
	return retangulo.getPosition();
}
const sf::RectangleShape& Obstaculo::getRetangulo() const {
	return retangulo;
}
