#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "personagem.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "inim_facil.h"

int main()
{
    Jogador jogador1;
    jogador1.executar();
	InimFacil inimigo1;
	inimigo1.executar();
    
	std::vector<Projetil> projeteis;

    sf::RenderWindow window(sf::VideoMode(1000, 800), "Minecraft 2", sf::Style::Default);
    
    sf::Texture texturaFundo;
    texturaFundo.loadFromFile("raw.png");
    sf::Sprite spriteFundo;
    spriteFundo.setTexture(texturaFundo);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        float janelax = window.getSize().x;
        float janelay = window.getSize().y;

        sf::Vector2f posInimigo1 = inimigo1.getPosicao();
        sf::Vector2f posJogador1 = jogador1.getPosicao();

        float dx = posJogador1.x - posInimigo1.x;
        float dy = posJogador1.y - posInimigo1.y;       


		jogador1.mover();

		jogador1.setPosicao( janelax, janelay);
        
        inimigo1.mover();

        inimigo1.setPosicao(janelax, janelay);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            projeteis.emplace_back(inimigo1.getPosicao(), jogador1.getPosicao());
            projeteis.back().carregarTextura("projetil.png");
        }
		for (auto& projetil : projeteis) {
			projetil.update(0.016f); // Atualiza o projetil com um deltaTime fixo
		}


        window.clear();
        window.draw(spriteFundo);
		jogador1.desenhar(window);
		inimigo1.desenhar(window);
		for (const auto& projetil : projeteis) {
			projeteis.back().desenhar(window);  
		}
        window.display();
    }

    return 0;
}