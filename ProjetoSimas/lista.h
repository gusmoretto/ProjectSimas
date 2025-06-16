#pragma once
#include "elemento.h" // Inclua Elemento.h (ou Elemento.hpp)
#include <iostream>   // Para std::cout
using namespace std;

template <typename TL>
class Lista {
private:
    Elemento<TL>* pPrimeiro;
    Elemento<TL>* pUltimo;

public:
    // Declarações
    Lista();
    ~Lista();
    void incluir(TL* p); // Agora recebe um PONTEIRO para TL
    void limpar();
    void percorrer();

    Elemento<TL>* getPrimeiro() const;
    Elemento<TL>* getUltimo() const;
};

template <typename TL>
Lista<TL>::Lista() : pPrimeiro(nullptr), pUltimo(nullptr) {
    // Para depuração: std::cout << "Lista criada." << std::endl;
}

template <typename TL>
Lista<TL>::~Lista() {
    limpar();
    // Para depuração: std::cout << "Lista destruída." << std::endl;
}

template <typename TL>
void Lista<TL>::incluir(TL* p) { // Recebe PONTEIRO
    // Cria um Elemento que armazena o PONTEIRO para TL
    Elemento<TL>* novoElemento = new Elemento<TL>(p);

    if (pPrimeiro == nullptr) { // Lista vazia
        pPrimeiro = novoElemento;
        pUltimo = novoElemento;
    }
    else { // Adiciona no início
        novoElemento->setProx(pPrimeiro);
        pPrimeiro = novoElemento;
    }
}

template <typename TL>
void Lista<TL>::limpar() {
    Elemento<TL>* atual = pPrimeiro;
    Elemento<TL>* proximo = nullptr;

    while (atual != nullptr) {
        proximo = atual->getProx();
        delete atual->getInfo();
        delete atual; 
        atual = proximo;
    }
    pPrimeiro = nullptr;
    pUltimo = nullptr;
}

template <typename TL>
void Lista<TL>::percorrer() {
    Elemento<TL>* atual = pPrimeiro;
    std::cout << "Elementos da lista: ";
    while (atual != nullptr) {
        if (atual->getInfo()) { 
            //cout << *atual->getInfo() << " ";
        }
        atual = atual->getProx();
    }
    std::cout << std::endl;
}

template <typename TL>
Elemento<TL>* Lista<TL>::getPrimeiro() const {
    return pPrimeiro;
}

template <typename TL>
Elemento<TL>* Lista<TL>::getUltimo() const {
    return pUltimo;
}
