#include <iostream>
#include "personagem.h"
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
void Personagem::mover() {
	sf::Vector2f movimento(0.f, 0.f);
	if (id_personagem == 0) {
		// Jogador 1: setas
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) movimento.x += velocidade;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  movimento.x -= velocidade;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    movimento.y -= velocidade;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  movimento.y += velocidade;
	}
	else if (id_personagem == 1) {
		// Jogador 2: WASD
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movimento.x += velocidade;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movimento.x -= velocidade;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movimento.y -= velocidade;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movimento.y += velocidade;
	}
		
	retangulo.move(movimento);
	
}
void Personagem::desenhar(sf::RenderWindow& window) {
	window.draw(retangulo);
}
void Personagem::carregarTextura(const std::string& caminho) {
	if (!textura.loadFromFile(caminho)) {
		std::cerr << "Erro ao carregar a textura: " << caminho << std::endl;
	}
	retangulo.setTexture(&textura);
}
void Personagem::setPosicao(float x, float y, float janelax, float janelay) {
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
