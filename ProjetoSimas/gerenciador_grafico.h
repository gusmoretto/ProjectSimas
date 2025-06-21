#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
namespace Gerenciadores {
	class GerenciadorGrafico {
	private:
		Sprite sprite;
		RenderWindow window;
		Texture texturaFundo;
		Sprite spriteFundo;
		View camera;
		Texture texturaChao;
		RectangleShape chao;
		RectangleShape barraVidaFundo; 
		RectangleShape barraVidaAtual; 
		RectangleShape barraVidaFundo2;
		RectangleShape barraVidaAtual2;
		Text textoVida;                
		Font fonteMenu;

	public:
		GerenciadorGrafico();
		~GerenciadorGrafico();
		RenderWindow& getWindow() { return window; }
		const bool estaAberta() const;
		void clear();
		void desenha(const RectangleShape& retangulo);
		void desenhaFundo();
		void mostrar();
		void fechar();
		float getTamanhoJanelax() const {
			return window.getSize().x;
		}
		float getTamanhoJanelay() const {
			return window.getSize().y;
		}
		void centralizarCamera(const sf::Vector2f& centro, float bgWidth, float bgHeight);
		void iniciaChao(const std::string& caminho, float larguraMapa, float alturaChao);
		void iniciaFundo(const std::string& caminho);
		void desenhaChao();
		void inicializarBarraVida(int jgs = 1);
		void atualizarBarraVida(int vidaAtual, int vidaMaxima, int idJogador);
		void desenharBV(int jgs = 1);
		View& getView() { return camera; }
	};
}


