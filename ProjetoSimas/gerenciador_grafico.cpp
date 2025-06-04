#include "gerenciador_grafico.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace Gerenciadores;

GerenciadorGrafico::GerenciadorGrafico(){
	window.create(VideoMode(1200, 700), "Globix", Style::Default);
	window.setFramerateLimit(120);
	texturaFundo.loadFromFile("fundo1.png");
	spriteFundo.setTexture(texturaFundo);
	spriteFundo.setPosition(0, 0);
}
Gerenciadores::GerenciadorGrafico::~GerenciadorGrafico() {
	std::cout << "Destrutor de GerenciadorGrafico chamado." << std::endl;
}
const bool GerenciadorGrafico::estaAberta() const {
	return window.isOpen();
}
void GerenciadorGrafico::desenha(const RectangleShape& retangulo) {
	window.draw(retangulo);
}
void GerenciadorGrafico::desenhaFundo() {
	window.draw(spriteFundo);
}
void GerenciadorGrafico::mostrar() {
	window.display();
}
void GerenciadorGrafico::clear() {
	window.clear();
}
void GerenciadorGrafico::fechar() {
	window.close();
}

