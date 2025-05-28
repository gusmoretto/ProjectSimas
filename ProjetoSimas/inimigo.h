#pragma once
#include <SFML/Graphics.hpp>

class Inimigo {
private:
	sf::RectangleShape retangulo;
	sf::Texture textura;
	float velocidade;
	int vida;
	int ataque;
	static int cont_inimigo;
	int id_inimigo;
public:
	Inimigo();
	~Inimigo();
	void perseguir(float dx, float dy);
	void desenhar(sf::RenderWindow& window);
	void carregarTextura(const std::string& caminho);
	void setPosicao(float x, float y, float janelax, float janelay);
	sf::Vector2f getPosicao() const;
	int getVida() const;
	int getAtaque() const;
	void setVida(int vida);
	void setAtaque(int ataque);
	int getIdInimigo() const;
};
