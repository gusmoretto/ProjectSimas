#include <iostream>
#include <SFML/Graphics.hpp>
#include "ente.h"

Ente::Ente(){ id++;}

Ente::~Ente() {
	std::cout << "Destrutor de Ente chamado." << std::endl;
}
//void desenhar(sf::RenderWindow& window) {
	// Implementar a lógica de desenho aqui
	// Exemplo: window.draw(someDrawable);
//}
void Ente::executar() {
	std::cout << "Executando Ente com ID: " << id << std::endl;
}