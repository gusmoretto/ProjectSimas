#include "jogador.h"
#include <iostream>
#include "personagem.h"

int Jogador::cont_jogador = 0;

Jogador::Jogador(): Personagem(), impulsoPulo(-650.f), velocidadeBase(0.f), puloBase(0.f) , velocidadeHorizontal(0.f) {
	vida = 150;
	ataque = 10;
	pontos = 0;
	id_jogador = cont_jogador++;
    noChao = true;
    velocidadeVertical = 0.f;
	olhandoDireita = true; 
    num_vidas = 5;
    velocidade = 2.2f;
}
Jogador::~Jogador() {
	vida = -1;
	ataque = -1;
}
int Jogador::getVida() const {
	return vida;
}
int Jogador::getAtaque() const {
	return ataque;
}
void Jogador::setVida(int novaVida) {
	vida = novaVida;
}
void Jogador::setAtaque(int novoAtaque) {
	ataque = novoAtaque;
}
void Jogador::executar() {
    if (cont_jogador)
        setId(1);
    else
        setId(2);
    retangulo.setSize(sf::Vector2f(64.f, 64.f));
    retangulo.setOrigin(0.f, 0.f); 
    retangulo.setPosition(x, y);
	if (id_jogador == 0) {
        if (!textura.loadFromFile("player.png")) {
            std::cout << "Erro ao carregar jogador1.png" << std::endl;
        }
	}
	else {
		textura.loadFromFile("player2.png");
	}
    retangulo.setTexture(&textura);
    velocidadeBase = getVelocidade();
    puloBase = getPulo();
}
void Jogador::mover() {
    sf::Vector2f movimento(0.f, 0.f);
    float dt = 0.016f; 

    if (id_jogador == 1) { 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            movimento.x += velocidade;
            if (!olhandoDireita) {
                olhandoDireita = true;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            movimento.x -= velocidade;
            if (olhandoDireita) {
                olhandoDireita = false;
            }
        }
    }
    else if (id_jogador == 0) { // Lógica para o Jogador 1 (teclas A e D)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movimento.x += velocidade;
            if (!olhandoDireita) {
                olhandoDireita = true;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movimento.x -= velocidade;
            if (olhandoDireita) {
                olhandoDireita = false;
            }
        }
    }

    // --- Movimento horizontal externo (repulsão/knockback) ---
    movimento.x += velocidadeHorizontal * dt;

    // Aplica um "atrito" para que a velocidade de repulsão diminua com o tempo
    velocidadeHorizontal *= 0.92f; // Fator de atrito, ajuste se necessário
    if (std::abs(velocidadeHorizontal) < 1.0f) {
        velocidadeHorizontal = 0.f;
    }

    // --- Movimento Vertical (Pulo e Gravidade) ---
    // Verifica a tecla de pulo baseado no id do jogador
    bool puloPressionado = false;
    if (id_jogador == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { // Pulo do Jogador 1 na tecla 'W'
        puloPressionado = true;
    }
    else if (id_jogador == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { // Pulo do Jogador 2 na tecla 'Seta para Cima'
        puloPressionado = true;
    }

    if (puloPressionado && noChao) {
        velocidadeVertical = impulsoPulo;
        noChao = false;
    }

    // Aplica gravidade
    velocidadeVertical += gravidade * dt;
    movimento.y += velocidadeVertical * dt;

    retangulo.move(movimento);

    // --- Verificação de limites (lógica original com melhorias) ---
    sf::Vector2f pos = retangulo.getPosition();
    sf::Vector2f size = retangulo.getSize();

    if (pos.y + size.y >= 670.f) {
        pos.y = 670.f - size.y;
        retangulo.setPosition(pos);
        noChao = true;
        if (velocidadeVertical > 0)
            velocidadeVertical = 0.f;
    }

    if (pos.y < 0.f) {
        pos.y = 0.f;
        velocidadeVertical = 0.f;
    }
    if (pos.x < 0.f) {
        pos.x = 0.f;
        if (velocidadeHorizontal < 0)
            velocidadeHorizontal = 0.f;
    }

    if (pos.x + size.x > 3840.f) {
        pos.x = 3840.f - size.x;
        if (velocidadeHorizontal > 0)
            velocidadeHorizontal = 0.f;
    }

    retangulo.setPosition(pos);
}
void Jogador::desenhar() {
	if (pGG) {
		pGG->desenha(retangulo);
	}
}
void Jogador::setId(int novoId) {
    id = novoId;
}
int Jogador::getId() const {
    return id;
}
void Jogador::setVelocidade(float nvVelocidade) {
	velocidade = nvVelocidade;
}
float Jogador::getVelocidade() {
	return velocidade;
}
void Jogador::setVelocidadeHorizontal(float nvVelocidadeHorizontal) {
    velocidadeHorizontal = nvVelocidadeHorizontal;
}
float Jogador::getVelocidadeHorizontal() const {
    return velocidadeHorizontal;
}
void Jogador::setNoChao(bool NC) {
    noChao = NC;
}
bool Jogador::getNochao() {
	return noChao;
}
void Jogador::setVelocidadeVertical(float nvVelocidadeVertical) {
	velocidadeVertical = nvVelocidadeVertical;
}
float Jogador::getVelocidadeVertical() const {
	return velocidadeVertical;
}
float Jogador::getPuloBase() const {
    return puloBase;
}
void Jogador::salvar() {
    if (auto* p_sstream = dynamic_cast<std::ostringstream*>(buffer)) {
        p_sstream->str("");
        p_sstream->clear();
    }
    else {
        return;
    }

    Personagem::salvarDataBuffer();
    *buffer << id_jogador << " " << pontos << " " << impulsoPulo << " " << olhandoDireita << " " << velocidadeBase << " " << puloBase << std::endl;

    std::ofstream arquivoJogador("arquivo_jogador.txt");
    if (arquivoJogador.is_open()) {
        arquivoJogador << buffer;
        arquivoJogador.close();
    }
}



