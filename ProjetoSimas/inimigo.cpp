#include "inimigo.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int Inimigo::cont_inimigo = 0;

Inimigo::Inimigo() {
	retangulo.setSize(sf::Vector2f(100.f, 100.f));
	velocidade = 0.1f;
	vida = 50;
	ataque = 20;
	id_inimigo = cont_inimigo++;
}
Inimigo::~Inimigo() {
	vida = -1;
	ataque = -1;
}	
void Inimigo::perseguir(float dx, float dy) {
	sf::Vector2f movimento(0.f, 0.f);
	if (dx > 0) movimento.x += velocidade;
	else if (dx < 0) movimento.x -= velocidade;
	if (dy > 0) movimento.y += velocidade;
	else if (dy < 0) movimento.y -= velocidade;
	retangulo.move(movimento);
}
void Inimigo::desenhar(sf::RenderWindow& window) {
	window.draw(retangulo);
}
void Inimigo::carregarTextura(const std::string& caminho) {
	if (!textura.loadFromFile(caminho)) {
		std::cerr << "Erro ao carregar a textura: " << caminho << std::endl;
	}
	retangulo.setTexture(&textura);
}	
void Inimigo::setPosicao(float x, float y, float janelax, float janelay) {
	sf::Vector2f posicao = retangulo.getPosition();
	if (posicao.x < 0) posicao.x = 0;
	if (posicao.y < 0) posicao.y = 0;
	if (posicao.x + retangulo.getSize().x > janelax) posicao.x = janelax - retangulo.getSize().x;
	if (posicao.y + retangulo.getSize().y > janelay) posicao.y = janelay - retangulo.getSize().y;
	retangulo.setPosition(posicao);
}
sf::Vector2f Inimigo::getPosicao() const {
	return retangulo.getPosition();
}
int Inimigo::getVida() const {
	return vida;
}
int Inimigo::getAtaque() const {
	return ataque;
}
void Inimigo::setVida(int vida) {
	this->vida = vida;
}
void Inimigo::setAtaque(int ataque) {
	this->ataque = ataque;
}
int Inimigo::getIdInimigo() const {
	return id_inimigo;
}


