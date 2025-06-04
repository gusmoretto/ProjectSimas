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
	camera = window.getDefaultView();
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
void GerenciadorGrafico::centralizarCamera(const sf::Vector2f& centro, float bgWidth, float bgHeight) {
    float halfW = window.getSize().x / 2.f;
    float halfH = window.getSize().y / 2.f;

    sf::Vector2f novoCentro = centro;

    // Limite horizontal
    if (novoCentro.x < halfW)
        novoCentro.x = halfW;
    if (novoCentro.x > bgWidth - halfW)
        novoCentro.x = bgWidth - halfW;

    // Limite vertical
    if (novoCentro.y < halfH)
        novoCentro.y = halfH;
    if (novoCentro.y > bgHeight - halfH)
        novoCentro.y = bgHeight - halfH;

    camera.setCenter(novoCentro);
    window.setView(camera);
}


