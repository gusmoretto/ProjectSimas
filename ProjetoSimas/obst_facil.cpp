#include "obst_facil.h"

ObstFacil::ObstFacil() : Obstaculo(), lentidao(0) {
	//A fazer
}
ObstFacil::~ObstFacil() {
	//A fazer
	lentidao = -1;
}
void ObstFacil::executar() {
	setId(8);
	//A fazer
}
void ObstFacil::obstacular(Jogador* p) {
	if (p) {
		p->setVelocidade(p->getVelocidade() - getLentidao());
		std::cout << "Jogador afetado pela lentidao! Nova velocidade: " << p->getVelocidade() << std::endl;
	}
}
float ObstFacil::getLentidao() const{
	return lentidao;
}
void ObstFacil::setLentidao(float lent) {
	lentidao = lent;
}
void ObstFacil::setId(int novoId) {
	id = novoId;
}
int ObstFacil::getId() const {
	return id;
}