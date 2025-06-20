#pragma once
#include "inimigo.h"
#include "jogador.h"
#include "projetil.h"
#include "gerenciador_colisoes.h"
#include "lista_entidades.h"

class Lancador : public Inimigo {
private:
	int tamanho;
	float tempoAtaque; 
	float intervaloAtaque; 
	std::vector<Projetil*> projeteis;

public:
	Lancador();
	~Lancador();
	void executar();
	void salvar();
	void danificar(Jogador* p);
	void mover();
	int getVida() const;
	int getAtaque() const;
	void setVida(int v);
	void setAtaque(int a);
	void setId(int novoId);
	int getId() const;
	void setVelocidade(float nvVelocidade);
	float getVelocidade();
	void desenhar();
	void setForcaMitico(float forca) {
		forcaMitico = forca;
	};
	float getForcaMitico() const {
		return forcaMitico;
	};
	void atacar(Jogador* jogador1, Jogador* jogador2, float deltaTime, const sf::View& viewAtual, Gerenciadores::GerenciadorColisoes* gerenciadorColisoes, ListaEntidades* pListaEnts);
	void tratarColisaoComJogador(Jogador* jogador, int tipoColisao);
	void setVelocidadeVertical(float nvVelocidadeVertical);
	float getVelocidadeVertical() const;
	void setNoChao(bool NC);
	bool getNochao();
	const std::vector<Projetil*>& getProjeteis() const { return projeteis; }
};
