#include "obst_medio.h"
#include "jogador.h"

ObstMedio::ObstMedio() : Obstaculo(), largura(0){
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
		p->setVida(p->getVida() - 20); 
		std::cout << "Jogador danificado por obstáculo médio! Vida restante: " << p->getVida() << std::endl;
	}
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