#pragma once
#include <iostream>
#include <fstream>
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
    float velocidadeVertical = 0.f;
	bool forcaMiticaAtiva = false;
    float forcaMitico;
public:
    Entidade();
    virtual ~Entidade();
    virtual void executar() = 0;
    virtual void salvar() = 0;
    void salvarDataBuffer();
    virtual float aplicarGravidade(float deltaTime, float forcaExtra = 0.f);
    Vector2f getPosicao() const {
        return retangulo.getPosition();
    };
	void setPosicao(float x, float y) {
		retangulo.setPosition(x, y);
	};
    const RectangleShape getRetangulo() const {
        return retangulo;
    };
    virtual void desenhar() = 0;
    virtual void setForcaMitico(float forca) = 0;
    virtual float getForcaMitico() const = 0;
    virtual void setId(int novoId) = 0;
    virtual int getId() const = 0;
};
