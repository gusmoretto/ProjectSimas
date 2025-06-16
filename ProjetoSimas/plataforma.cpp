#include "plataforma.h"

Plataforma::Plataforma(): Obstaculo(), altura(650), velocidadeVertical(0.f) {
	danoso = false;
	gravidadeAtiva = true;
	forcaMitico = 0.f; 
    setId(7);
}
Plataforma::~Plataforma() {
}
void Plataforma::executar() {
    retangulo.setSize(sf::Vector2f(64.f, 64.f));
    if (!textura.loadFromFile("plataforma2.png")) {
        std::cout << "Erro ao carregar plataforma.png" << std::endl;
    }
    retangulo.setTexture(&textura);
}

void Plataforma::obstacular(Jogador* p) {
    sf::FloatRect areaJogador = p->getRetangulo().getGlobalBounds();
    sf::FloatRect areaPlataforma = this->getRetangulo().getGlobalBounds();

    float tolerancia = 10.f; // Ajuste conforme necess�rio

    // Colis�o por cima
    bool colisaoPorCima =
        (areaJogador.top + areaJogador.height > areaPlataforma.top) &&
        (areaJogador.top + areaJogador.height < areaPlataforma.top + tolerancia) &&
        (p->getVelocidadeVertical() >= 0) &&
        (areaJogador.left + areaJogador.width > areaPlataforma.left + 5.f) &&
        (areaJogador.left < areaPlataforma.left + areaPlataforma.width - 5.f);

    if (colisaoPorCima) {
        p->setPosicao(areaJogador.left, areaPlataforma.top - areaJogador.height);
        p->setVelocidadeVertical(0.f);
        p->setNoChao(true);
        return;
    }
    bool colisaoPorBaixo =
        (areaJogador.top < areaPlataforma.top + areaPlataforma.height) && 
        (areaJogador.top > areaPlataforma.top + areaPlataforma.height - tolerancia) && 
        (p->getVelocidadeVertical() < 0) && 
        (areaJogador.left + areaJogador.width > areaPlataforma.left + 5.f) &&
        (areaJogador.left < areaPlataforma.left + areaPlataforma.width - 5.f);

    if (colisaoPorBaixo) {
        p->setPosicao(areaJogador.left, areaPlataforma.top + areaPlataforma.height); 
        p->setVelocidadeVertical(0.f); 
        p->setNoChao(false); 
        return; 
    }

    // Colis�o lateral esquerda
    bool colisaoEsquerda =
        (areaJogador.left + areaJogador.width > areaPlataforma.left) &&
        (areaJogador.left < areaPlataforma.left) &&
        (areaJogador.top < areaPlataforma.top + areaPlataforma.height - tolerancia) &&
        (areaJogador.top + areaJogador.height > areaPlataforma.top + tolerancia);

    if (colisaoEsquerda) {
        p->setPosicao(areaPlataforma.left - areaJogador.width, areaJogador.top);
        return;
    }

    // Colis�o lateral direita
    bool colisaoDireita =
        (areaJogador.left < areaPlataforma.left + areaPlataforma.width) &&
        (areaJogador.left > areaPlataforma.left) &&
        (areaJogador.top < areaPlataforma.top + areaPlataforma.height - tolerancia) &&
        (areaJogador.top + areaJogador.height > areaPlataforma.top + tolerancia);

    if (colisaoDireita) {
        p->setPosicao(areaPlataforma.left + areaPlataforma.width, areaJogador.top);
        return;
    }
}


void Plataforma::desenhar() {
	if (pGG) {
		pGG->desenha(retangulo);
	}
}
int Plataforma::getId() const {
	return id;
}
void Plataforma::setId(int novoId) {
	id = novoId;
}
void Plataforma::setForcaMitico(float forca) {
	forcaMitico = forca;
}
float Plataforma::getForcaMitico() const {
	return forcaMitico;
}
void Plataforma::atualizarFisica(float dt) {
    aplicarGravidade(dt, getForcaMitico());

    // Limite do ch�o (opcional)
    sf::Vector2f pos = retangulo.getPosition();
    if (pos.y + retangulo.getSize().y > 670.f) {
        pos.y = 670.f - retangulo.getSize().y;
        velocidadeVertical = 0.f;
        retangulo.setPosition(pos);
    }
}

