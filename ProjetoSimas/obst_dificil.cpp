#include "obst_dificil.h"
#include "jogador.h"

ObstDificil::ObstDificil() : Obstaculo() {
	//A fazer
}
ObstDificil::~ObstDificil() {
	//A fazer
}
void ObstDificil::executar() {
	setId(10);
	//A fazer
}
void ObstDificil::obstacular(Jogador* p) {
	if (p) {
		//Fazer o jogador ser empurrado e levar dano quanto mais vezes encostar
		std::cout << "Jogador atingido por obstáculo difícil! Jogador empurrado" << std::endl;
	}
}
void ObstDificil::setId(int novoId) {
	id = novoId;
}
int ObstDificil::getId() const {
	return id;
}
void ObstDificil::setElasticidade(bool e){
	elasticidade = e;
}
bool ObstDificil::getElasticidade() const {
	return elasticidade;
}
void ObstDificil::desenhar() {
	if (pGG) {
		pGG->desenha(retangulo);
	}
}
void ObstDificil::atualizarFisica(float dt) {
	if (gravidadeAtiva) { // Verificação já deve estar aqui
		aplicarGravidade(dt, getForcaMitico());

		sf::Vector2f pos = retangulo.getPosition();
		if (pos.y + retangulo.getSize().y > 670.f) {
			pos.y = 670.f - retangulo.getSize().y;
			velocidadeVertical = 0.f;
			retangulo.setPosition(pos);
		}
	}
}