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

    if (novoCentro.x < halfW)
        novoCentro.x = halfW;
    if (novoCentro.x > bgWidth - halfW)
        novoCentro.x = bgWidth - halfW;

    if (novoCentro.y < halfH)
        novoCentro.y = halfH;
    if (novoCentro.y > bgHeight - halfH)
        novoCentro.y = bgHeight - halfH;

    camera.setCenter(novoCentro);
    window.setView(camera);
}
void GerenciadorGrafico::iniciaChao(const std::string& caminho, float larguraMapa, float alturaChao) {
	if (!texturaChao.loadFromFile(caminho)) {
		std::cerr << "Erro ao carregar textura do ch�o." << std::endl;
	}
	texturaChao.setRepeated(true);
	chao.setTexture(&texturaChao);
	chao.setSize(sf::Vector2f(larguraMapa, alturaChao));
	chao.setTextureRect(sf::IntRect(0, 0, static_cast<int>(larguraMapa), static_cast<int>(alturaChao)));
	chao.setPosition(0.f, 700.f - alturaChao); // Ajuste a posi��o conforme necess�rio
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
void GerenciadorGrafico::inicializarBarraVida(int jgs) {
    if (!fonteMenu.loadFromFile("fonteMenu.TTF")) {
        std::cerr << "Erro ao carregar a fonte para a barra de vida." << std::endl;
        return;
    }
    textoVida.setFont(fonteMenu);
    textoVida.setString("Vida");
    textoVida.setCharacterSize(20);
    textoVida.setFillColor(sf::Color::White);
    textoVida.setPosition(15.f, 10.f);

    barraVidaFundo.setSize(sf::Vector2f(200.f, 25.f));
    barraVidaFundo.setFillColor(sf::Color(50, 50, 50, 200)); 
    barraVidaFundo.setOutlineColor(sf::Color::Black);
    barraVidaFundo.setOutlineThickness(2.f);
    barraVidaFundo.setPosition(15.f, 35.f);

    barraVidaAtual.setSize(sf::Vector2f(200.f, 25.f));
    barraVidaAtual.setFillColor(sf::Color::Red);
    barraVidaAtual.setPosition(15.f, 35.f);

    if (jgs == 2) {
        barraVidaFundo2.setSize(sf::Vector2f(200.f, 25.f));
        barraVidaFundo2.setFillColor(sf::Color(50, 50, 50, 200));
        barraVidaFundo2.setOutlineColor(sf::Color::Black);
        barraVidaFundo2.setOutlineThickness(2.f);
        barraVidaFundo2.setPosition(15.f, 65.f);

        barraVidaAtual2.setSize(sf::Vector2f(200.f, 25.f));
        barraVidaAtual2.setFillColor(sf::Color::Red);
        barraVidaAtual2.setPosition(15.f, 65.f);
    }
}

void GerenciadorGrafico::atualizarBarraVida(int vidaAtual, int vidaMaxima, int idJogador) {
    if (vidaAtual < 0) {
        vidaAtual = 0;
    }
    float proporcaoVida = static_cast<float>(vidaAtual) / static_cast<float>(vidaMaxima);

    if (idJogador == 1) { 
        float larguraMaxima = barraVidaFundo.getSize().x;
        barraVidaAtual.setSize(sf::Vector2f(larguraMaxima * proporcaoVida, barraVidaAtual.getSize().y));
    }
    else if (idJogador == 2) { 
        float larguraMaxima2 = barraVidaFundo2.getSize().x;
        barraVidaAtual2.setSize(sf::Vector2f(larguraMaxima2 * proporcaoVida, barraVidaAtual2.getSize().y));
    }
}

void GerenciadorGrafico::desenharBV(int jgs) {
    window.setView(window.getDefaultView());
    window.draw(barraVidaFundo);
    window.draw(barraVidaAtual);
	if (jgs == 2) {
		window.draw(barraVidaFundo2);
		window.draw(barraVidaAtual2);
	}
    window.draw(textoVida);
}


