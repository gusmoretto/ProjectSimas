#include "espinho.h"
#include "jogador.h"

Espinho::Espinho() : Obstaculo(), elasticidade(128.f) { danoso = true; }
Espinho::~Espinho() {
}
void Espinho::executar() {
	setId(10);
	retangulo.setSize(sf::Vector2f(64.f, 64.f));
	if (!textura.loadFromFile("cacto.png")) {
		std::cout << "Erro ao carregar espinho.png" << std::endl;
	}
	retangulo.setTexture(&textura);
}
void Espinho::obstacular(Jogador* p, int tipoColisao) {
	if (!p) {
		return;
	}

	sf::FloatRect areaJogador = p->getRetangulo().getGlobalBounds();
	sf::FloatRect areaEspinho = this->getRetangulo().getGlobalBounds();
	float impulsoRepulsao = 400.f; 

	p->setVida(p->getVida() - 10); 
	std::cout << "Jogador atingido por espinho! Vida restante: " << p->getVida() << std::endl;

	switch (tipoColisao) {
	case 1: 
		p->setPosicao(areaJogador.left, areaEspinho.top - areaJogador.height);
		p->setVelocidadeVertical(-impulsoRepulsao); 
		p->setNoChao(true);
		break;

	case 4: 
		p->setPosicao(areaJogador.left, areaEspinho.top + areaEspinho.height);
		p->setVelocidadeVertical(impulsoRepulsao); 
		break;

	case 2: 
		p->setPosicao(areaEspinho.left + areaEspinho.width, areaJogador.top);
		p->setPosicao(p->getPosicao().x + 5.f, p->getPosicao().y);
		break;

	case 3:
		p->setPosicao(areaEspinho.left - areaJogador.width, areaJogador.top);
		p->setPosicao(p->getPosicao().x - 5.f, p->getPosicao().y);
		break;
	}
}
void Espinho::setId(int novoId) {
	id = novoId;
}
int Espinho::getId() const {
	return id;
}
void Espinho::setElasticidade(bool e){
	elasticidade = e;
}
bool Espinho::getElasticidade() const {
	return elasticidade;
}
void Espinho::desenhar() {
	if (pGG) {
		pGG->desenha(retangulo);
	}
}
void Espinho::atualizarFisica(float dt) {
	sf::Vector2f pos = retangulo.getPosition();
	if (gravidadeAtiva) {
		aplicarGravidade(dt, getForcaMitico());
		if (pos.y + retangulo.getSize().y > 670.f) {
			pos.y = 670.f - retangulo.getSize().y;
			velocidadeVertical = 0.f;
			retangulo.setPosition(pos);
		}
	}
	else {
		if (pos.y + retangulo.getSize().y > 670.f) {
			pos.y = 670.f - retangulo.getSize().y;
			velocidadeVertical = 0.f;
			retangulo.setPosition(pos);
		}
	}
}
void Espinho::salvar() {
	if (auto* p_sstream = dynamic_cast<std::ostringstream*>(buffer)) {
		p_sstream->str("");
		p_sstream->clear();
	}
	else {
		return;
	}

	Obstaculo::salvarDataBuffer();
	*buffer << elasticidade << std::endl;

	std::ofstream arquivoEspinhos("arquivo_espinho.txt", std::ios::app);
	if (arquivoEspinhos.is_open()) {
		arquivoEspinhos << buffer;
		arquivoEspinhos.close();
	}
}