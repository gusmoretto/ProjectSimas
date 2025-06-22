#include "espinho.h"
#include "jogador.h"

Espinho::Espinho() : Obstaculo(), elasticidade(128.f) { danoso = true; }
Espinho::~Espinho() {
}
void Espinho::executar() {
	setId(10);
	retangulo.setSize(sf::Vector2f(60.f, 60.f));
	if (!textura.loadFromFile("cacto.png")) { // Verifique se o nome do arquivo está correto
		std::cerr << "Erro fatal: Nao foi possivel carregar a textura cacto.png" << std::endl;
		return;
	}
	retangulo.setTexture(&textura);
}
void Espinho::obstacular(Jogador* p, int tipoColisao) {
	if (!p) {
		return;
	}

	sf::FloatRect areaJogador = p->getRetangulo().getGlobalBounds();
	sf::FloatRect areaEspinho = this->getRetangulo().getGlobalBounds();

	float impulsoRepulsaoVertical = 450.f;
	float impulsoRepulsaoHorizontal = 600.f;
	float impulsoVerticalCurto = -200.f; // Um pequeno pulo ao ser atingido de lado

	p->setVida(p->getVida() - 10);
	std::cout << "Jogador atingido por espinho! Vida restante: " << p->getVida() << std::endl;

	switch (tipoColisao) {
	case 1: // Colisão por cima
		p->setPosicao(areaJogador.left, areaEspinho.top - areaJogador.height);
		p->setVelocidadeVertical(-impulsoRepulsaoVertical);
		p->setNoChao(true);
		break;

	case 4: // Colisão por baixo
		p->setPosicao(areaJogador.left, areaEspinho.top + areaEspinho.height);
		p->setVelocidadeVertical(impulsoRepulsaoVertical);
		break;

	case 2: // Colisão pela esquerda do espinho (o jogador vem da direita)
		p->setPosicao(areaEspinho.left - areaJogador.width, areaJogador.top);
		p->setVelocidadeHorizontal(-impulsoRepulsaoHorizontal); // Repulsão para a ESQUERDA
		p->setVelocidadeVertical(impulsoVerticalCurto); // Joga o jogador um pouco para cima
		p->setNoChao(false);
		break;

	case 3: // Colisão pela direita do espinho (o jogador vem da esquerda)
		p->setPosicao(areaEspinho.left + areaEspinho.width, areaJogador.top);
		p->setVelocidadeHorizontal(impulsoRepulsaoHorizontal); // Repulsão para a DIREITA
		p->setVelocidadeVertical(impulsoVerticalCurto); // Joga o jogador um pouco para cima
		p->setNoChao(false);
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
void Espinho::salvar(std::ostream& os) {
	os << gravidade << " " << forcaMitico << " " << forcaMiticaAtiva << " "
		<< danoso << " " << gravidadeAtiva << " " << elasticidade << " "
		<< getPosicao().x << " " << getPosicao().y << std::endl;
}