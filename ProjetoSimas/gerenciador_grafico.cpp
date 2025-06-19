#include "gerenciador_grafico.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace Gerenciadores;

GerenciadorGrafico::GerenciadorGrafico(){
	window.create(VideoMode(1200, 700), "Cavalheiro do dia e noite++", Style::Default);
	window.setFramerateLimit(120);
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
void GerenciadorGrafico::iniciaChao(const std::string& caminho, float larguraMapa, float alturaChao) {
	if (!texturaChao.loadFromFile(caminho)) {
		std::cerr << "Erro ao carregar textura do chão." << std::endl;
	}
	texturaChao.setRepeated(true);
	chao.setTexture(&texturaChao);
	chao.setSize(sf::Vector2f(larguraMapa, alturaChao));
	chao.setTextureRect(sf::IntRect(0, 0, static_cast<int>(larguraMapa), static_cast<int>(alturaChao)));
	chao.setPosition(0.f, 700.f - alturaChao); // Ajuste a posição conforme necessário
}
void GerenciadorGrafico::desenhaChao() {
	window.draw(chao);
}
void GerenciadorGrafico::iniciaFundo(const std::string& caminho) {
	if (!texturaFundo.loadFromFile(caminho)) {
		std::cerr << "Erro ao carregar textura de fundo." << std::endl;
	}
	spriteFundo.setTexture(texturaFundo);
	spriteFundo.setPosition(0, 0);
}


