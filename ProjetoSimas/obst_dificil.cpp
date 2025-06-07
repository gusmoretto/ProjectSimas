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
		//Fazer o jogador ser empurrado
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