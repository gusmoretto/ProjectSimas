#pragma once

template <typename TE>
class Elemento {
private:
    Elemento<TE>* pProx;
    TE* info; 

public:
    Elemento(TE* pInfo = nullptr); 

    ~Elemento();

    void setProx(Elemento<TE>* PE);
    void setInfo(TE* pInfo); 

    Elemento<TE>* getProx() const;
    TE* getInfo() const; 
};

template <typename TE>
Elemento<TE>::Elemento(TE* pInfo) : pProx(nullptr), info(pInfo) {
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
