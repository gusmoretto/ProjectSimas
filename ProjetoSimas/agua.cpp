#include "agua.h"
#include "jogador.h"

Agua::Agua() : Obstaculo(), largura(0), lentidao(0) {
	danoso = false;
}
Agua::~Agua() {
	
}
void Agua::executar() {
	setId(9);
	retangulo.setSize(sf::Vector2f(64.f, 48.f));
	retangulo.setFillColor(sf::Color::Blue);
	setLentidao(1.f);
}
void Agua::obstacular(Jogador* p) {
	float velocidadeDesejada = p->getVelocidadeBase() - getLentidao();
	float velocidadeFinal = std::max(0.0f, velocidadeDesejada); 
	float puloMenor = p->getPulo() + getLentidao() * 2.f;
	if (puloMenor <= -400.f)
		p->setPulo(puloMenor);
	else
		p->setPulo(-400.f);
	p->setVelocidade(velocidadeFinal);
}
float Agua::getLentidao() const {
	return lentidao;
}
void Agua::setLentidao(float lent) {
	lentidao = lent;
}
void Agua::setId(int novoId) {
	id = novoId;
}
int Agua::getId() const {
	return id;
}
void Agua::setLargura(float novaLargura) {
	largura = novaLargura;
}
float Agua::getLargura() const {
	return largura;
}
void Agua::desenhar() {
	if (pGG) {
		pGG->desenha(retangulo);
	}
}
void Agua::atualizarFisica(float dt) {
	sf::Vector2f pos = retangulo.getPosition();

	if (gravidadeAtiva) { // Verificação já deve estar aqui
		aplicarGravidade(dt, getForcaMitico());

		if (pos.y + retangulo.getSize().y > 734.f) {
			pos.y = 734.f - retangulo.getSize().y;
			velocidadeVertical = 0.f;
			retangulo.setPosition(pos);
		}
	}
	else if (pos.y + retangulo.getSize().y > 734.f) {
		pos.y = 734.f - retangulo.getSize().y;
		velocidadeVertical = 0.f;
		retangulo.setPosition(pos);
	}
}