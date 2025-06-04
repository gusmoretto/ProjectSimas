#pragma once
#include <iostream>
#include <ostream>
#include "ente.h"
using namespace std;

class Entidade: public Ente {
protected:
    int x, y;
    ostream* buffer; 
    float gravidade;
	RectangleShape retangulo;
	Texture textura;
public:
    Entidade();
    virtual ~Entidade();
    virtual void executar() = 0;
    //virtual void salvar() const = 0;
    //void salvarDataBuffer();
    virtual float aplicarGravidade(float deltaTime);
    Vector2f getPosicao() const {
        return retangulo.getPosition();
    };
	void setPosicao(float x, float y) {
		retangulo.setPosition(x, y);
	};
    const RectangleShape getRetangulo() const {
        return retangulo;
    };
};
