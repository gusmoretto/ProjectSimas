#include <iostream>
#include "personagem.h"
#include "entidade.h"
#include <SFML/Graphics.hpp>

int Personagem::cont_personagem = 0;

Personagem::Personagem() : Entidade(), num_vidas(3) { 
	retangulo.setSize(sf::Vector2f(100.f, 100.f)); 
	velocidade = 0.3f; 
	id_personagem = cont_personagem++;
}
Personagem::~Personagem() {
	std::cout << "Destrutor de Personagem chamado." << std::endl;
}
void Personagem::executar() {
	std::cout << "Executando Personagem com " << num_vidas << " vidas." << std::endl;
}
//void Personagem::salvarDataBuffer() {
//	std::cout << "Salvando dados do personagem com " << num_vidas << " vidas." << std::endl;
//}
void Personagem::desenhar(sf::RenderWindow& window) {
	window.draw(retangulo);
}
void Personagem::carregarTextura(const std::string& caminho) {
	if (!textura.loadFromFile(caminho)) {
		std::cerr << "Erro ao carregar a textura: " << caminho << std::endl;
	}
	retangulo.setTexture(&textura);
}
void Personagem::setPosicao(float janelax, float janelay) {
	sf::Vector2f posicao = retangulo.getPosition();
	if (posicao.x < 0) posicao.x = 0;
	if (posicao.y < 0) posicao.y = 0;
	if (posicao.x + retangulo.getSize().x > janelax) posicao.x = janelax - retangulo.getSize().x;
	if (posicao.y + retangulo.getSize().y > janelay) posicao.y = janelay - retangulo.getSize().y;
	retangulo.setPosition(posicao);
}
sf::Vector2f Personagem::getPosicao() const {
	return retangulo.getPosition();
}
int Personagem::getIdPersonagem() const {
	return id_personagem;
}
const sf::RectangleShape& Personagem::getRetangulo() const {
	return retangulo;
}