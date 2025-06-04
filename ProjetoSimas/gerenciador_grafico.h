#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
namespace Gerenciadores {
	class GerenciadorGrafico {
	private:
		Sprite sprite;
		RenderWindow window;
		sf::Texture texturaFundo;
		sf::Sprite spriteFundo;

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
	};
}


