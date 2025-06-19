#include "espinho.h"
#include "jogador.h"

Espinho::Espinho() : Obstaculo() {
	//A fazer
}
Espinho::~Espinho() {
	//A fazer
}
void Espinho::executar() {
	setId(10);
	//A fazer
}
void Espinho::obstacular(Jogador* p) {
	if (p) {
		//Fazer o jogador ser empurrado e levar dano quanto mais vezes encostar
		std::cout << "Jogador atingido por obstáculo difícil! Jogador empurrado" << std::endl;
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