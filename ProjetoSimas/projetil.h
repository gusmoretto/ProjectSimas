#pragma once
#include "personagem.h"

class Projetil: public Personagem {
private:
	const float raio;
	//a fazer TUDO!!!

public:
	Projetil(); 
	~Projetil();
	void update(float deltaTime);
	void executar();
	void setId(int novoId) ;
	int getId() const ;
};
