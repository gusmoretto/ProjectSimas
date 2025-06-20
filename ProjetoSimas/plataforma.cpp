#include "plataforma.h"

Plataforma::Plataforma(): Obstaculo(), altura(650), velocidadeVertical(0.f) {
	danoso = false;
	forcaMitico = 0.f; 
    setId(7);
}
Plataforma::~Plataforma() {
}
void Plataforma::executar() {
    retangulo.setSize(sf::Vector2f(64.f, 64.f));
}
void Plataforma::setarTexturaFase(int fase) {
	if (fase == 1) {
		if (!textura.loadFromFile("plataforma2.png")) {
			std::cout << "Erro ao carregar plataforma1.png" << std::endl;
		}
	}
	else if (fase == 2) {
		if (!textura.loadFromFile("plataforma.png")) {
			std::cout << "Erro ao carregar plataforma2.png" << std::endl;
		}
	}
	retangulo.setTexture(&textura);
}

void Plataforma::obstacular(Jogador* p, int tipoColisao) {
    sf::FloatRect areaJogador = p->getRetangulo().getGlobalBounds();
    sf::FloatRect areaPlataforma = this->getRetangulo().getGlobalBounds();

    float tolerancia = 10.f; 

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

    bool colisaoEsquerda =
        (areaJogador.left + areaJogador.width > areaPlataforma.left) &&
        (areaJogador.left < areaPlataforma.left) &&
        (areaJogador.top < areaPlataforma.top + areaPlataforma.height - tolerancia) &&
        (areaJogador.top + areaJogador.height > areaPlataforma.top + tolerancia);

    if (colisaoEsquerda) {
        p->setPosicao(areaPlataforma.left - areaJogador.width, areaJogador.top);
        return;
    }

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
    sf::Vector2f pos = retangulo.getPosition();
    if (gravidadeAtiva) { 
        aplicarGravidade(dt, getForcaMitico());
        if (pos.y + retangulo.getSize().y > 670.f) {
            pos.y = 670.f - retangulo.getSize().y;
            velocidadeVertical = 0.f;
            retangulo.setPosition(pos);
        }
    }
    else if (pos.y + retangulo.getSize().y > 670.f) {
        pos.y = 670.f - retangulo.getSize().y;
        velocidadeVertical = 0.f;
        retangulo.setPosition(pos);
    }
}
void Plataforma::salvar() {
    if (auto* p_sstream = dynamic_cast<std::ostringstream*>(buffer)) {
        p_sstream->str("");
        p_sstream->clear();
    }
    else {
        return;
    }

    Obstaculo::salvarDataBuffer();
    *buffer << altura << " " << velocidadeVertical << std::endl;

    std::ofstream arquivoPlataforma("arquivo_plataforma.txt", std::ios::app);
    if (arquivoPlataforma.is_open()) {
        arquivoPlataforma << buffer;
        arquivoPlataforma.close();
    }
}

