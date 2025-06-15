#include "obst_medio.h"
#include "jogador.h"

ObstMedio::ObstMedio() : Obstaculo(), largura(0), lentidao(0) {
	//A fazer
	danoso = true;
}
ObstMedio::~ObstMedio() {
	// A fazer
}
void ObstMedio::executar() {
	setId(9);
	//A fazer
}
void ObstMedio::obstacular(Jogador* p) {
	if (p) {
		p->setVelocidade(p->getVelocidade() - getLentidao());
		std::cout << "Jogador afetado pela lentidao! Nova velocidade: " << p->getVelocidade() << std::endl;
	}
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