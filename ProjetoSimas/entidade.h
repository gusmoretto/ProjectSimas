#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>
using namespace std;

class Entidade {
protected:
    int x, y;
    ostream* buffer; // Changed to a pointer to ostream
public:
    Entidade();
    virtual ~Entidade();
    virtual void executar() = 0;
    //virtual void salvar() const = 0;
    //void salvarDataBuffer();
};
