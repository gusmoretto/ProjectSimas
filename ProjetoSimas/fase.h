#pragma once
#include "ente.h"
#include "lista_entidades.h"
#include "gerenciador_colisoes.h"
#include "jogador.h"

class Fase : public Ente {
protected:
    ListaEntidades lista_ents;
    Gerenciadores::GerenciadorColisoes GC;
    Jogador* jogador1;
    Jogador* jogador2;

protected:
    void criarPlataformas(const char* caminhoArquivo);
    void criarAranhas(const char* caminhoArquivo);

    virtual void criarInimigos() = 0;
    virtual void criarObstaculos() = 0;

    void criarCenario(const std::string& fundo, const std::string& chao);

public:
    Fase(Jogador* j1, Jogador* j2);
    virtual ~Fase();
    virtual void executar();
    Gerenciadores::GerenciadorColisoes* getGerenciadorColisoes() { return &GC; }
    ListaEntidades* getListaEntidades() { return &lista_ents; }
    void setId(int novoId);
    int getId() const;
};