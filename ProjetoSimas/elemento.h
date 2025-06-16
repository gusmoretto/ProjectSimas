#pragma once

template <typename TE>
class Elemento {
private:
    Elemento<TE>* pProx;
    TE* info; // Agora armazena um PONTEIRO para TE

public:
    // Construtor: recebe um ponteiro para TE
    Elemento(TE* pInfo = nullptr); // Recebe ponteiro

    // Destrutor: CUIDADO com a propriedade da memória
    ~Elemento();

    // Métodos set
    void setProx(Elemento<TE>* PE);
    void setInfo(TE* pInfo); // Recebe ponteiro

    // Métodos get
    Elemento<TE>* getProx() const;
    TE* getInfo() const; // Retorna ponteiro
};

template <typename TE>
Elemento<TE>::Elemento(TE* pInfo) : pProx(nullptr), info(pInfo) {
    // Para depuração: std::cout << "Elemento criado." << std::endl;
}

template <typename TE>
Elemento<TE>::~Elemento() {
    pProx = nullptr;
}

template <typename TE>
void Elemento<TE>::setProx(Elemento<TE>* PE) {
    pProx = PE;
}

template <typename TE>
void Elemento<TE>::setInfo(TE* pInfo) {
    info = pInfo;
}

template <typename TE>
Elemento<TE>* Elemento<TE>::getProx() const {
    return pProx;
}

template <typename TE>
TE* Elemento<TE>::getInfo() const {
    return info;
}
