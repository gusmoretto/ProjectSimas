#include "fase.h"
#include "obst_medio.h"
#include "inim_facil.h"
#include "inim_medio.h"

Fase::Fase() {}
Fase::~Fase() {}

void Fase::criarCenario() {
	pGG->iniciaFundo("fundo.png");
	pGG->iniciaChao("chao.png", 3840.f, 300.f);
}
void Fase::criarPlataformas() {
	
}
void Fase::criarinimFaceis() {

}
void Fase::executar() {
	
}
void Fase::colocarCoordenadas() {
	
}