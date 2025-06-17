#include "obst_medio.h"
#include "jogador.h"

ObstMedio::ObstMedio() : Obstaculo(), largura(0), lentidao(0) {
	danoso = false;
}
ObstMedio::~ObstMedio() {
	
}
void ObstMedio::executar() {
	setId(9);
	retangulo.setSize(sf::Vector2f(64.f, 48.f));
	retangulo.setFillColor(sf::Color::Blue);
	setLentidao(1.f);
}
void ObstMedio::obstacular(Jogador* p) {
	float velocidadeDesejada = p->getVelocidadeBase() - getLentidao();
	float velocidadeFinal = std::max(0.0f, velocidadeDesejada); 
	float puloMenor = p->getPulo() + getLentidao() * 2.f;
	if (puloMenor <= -400.f)
		p->setPulo(puloMenor);
	else
		p->setPulo(-400.f);
	p->setVelocidade(velocidadeFinal);
}
float ObstMedio::getLentidao() const {
	return lentidao;
}
void ObstMedio::setLentidao(float lent) {
	lentidao = lent;
}
void ObstMedio::setId(int novoId) {
	id = novoId;
}
int ObstMedio::getId() const {
	return id;
}
void ObstMedio::setLargura(float novaLargura) {
	largura = novaLargura;
}
float ObstMedio::getLargura() const {
	return largura;
}
void ObstMedio::desenhar() {
	if (pGG) {
		pGG->desenha(retangulo);
	}
}
void ObstMedio::atualizarFisica(float dt) {
    aplicarGravidade(dt, getForcaMitico());

    sf::Vector2f pos = retangulo.getPosition();
    if (pos.y + retangulo.getSize().y > 734.f) {
        pos.y = 734.f - retangulo.getSize().y;
        velocidadeVertical = 0.f;
        retangulo.setPosition(pos);
    }
}